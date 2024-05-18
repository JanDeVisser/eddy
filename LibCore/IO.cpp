/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <cerrno>
#include <cstddef>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include <LibCore/Error.h>
#include <LibCore/IO.h>

namespace LibCore {

#define BUF_SZ 65536

Socket::Socket(int fd)
    : fd(fd)
{
}

CError make_sockaddr_un(std::string_view const &unix_socket_name, struct sockaddr_un& sock_addr)
{
    sock_addr.sun_family = AF_LOCAL;
    if (unix_socket_name.length() >= sizeof(sock_addr.sun_path)) {
        return LibCError("Local socket name '{:}' too long: {:} >= {:}",
            unix_socket_name, unix_socket_name.length(), sizeof(sock_addr.sun_path));
    }
    memcpy(sock_addr.sun_path, unix_socket_name.data(), unix_socket_name.length());
    sock_addr.sun_path[unix_socket_name.length()] = '\0';
    return {};
}

Result<socket_t> Socket::listen(std::string_view const &unix_socket_name)
{
    int const listen_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        return LibCError();
    }

    struct sockaddr_un sock_addr = { 0 };
    TRY(make_sockaddr_un(unix_socket_name, sock_addr));
    size_t serv_size = offsetof(struct sockaddr_un, sun_path) + unix_socket_name.length() + 1;
    if (bind(listen_fd, (struct sockaddr *) &sock_addr, serv_size) < 0) {
        return LibCError();
    }
    if (::listen(listen_fd, 1) < 0) {
        return LibCError();
    }
    return std::make_shared<Socket>(listen_fd);
}

Result<socket_t> Socket::listen(std::string_view const& ip_address, int port)
{
    fatal("listen(ip_addr, port) not yet implemented");
}

Result<socket_t> connect(std::string_view const &unix_socket_name)
{
    int conn_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (conn_fd < 0) {
        return LibCError();
    }

    struct sockaddr_un sock_addr = { 0 };
    TRY(make_sockaddr_un(unix_socket_name, sock_addr));
    size_t sock_addr_size = offsetof(struct sockaddr_un, sun_path) + unix_socket_name.length() + 1;
    if (connect(conn_fd, (struct sockaddr *) &sock_addr, sock_addr_size) < 0) {
        return LibCError();
    }
    TRY(fd_make_nonblocking(conn_fd));
    return std::make_shared<Socket>(conn_fd);
}

Result<socket_t> connect(std::string_view const &ip_address, int port)
{
    int conn_fd;
    if ((conn_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return LibCError();
    }

    struct sockaddr_in server_address = TRY_EVAL(tcpip_address_resolve(ip_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (connect(conn_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        return LibCError();
    }
    TRY(fd_make_nonblocking(conn_fd));
    return std::make_shared<Socket>(conn_fd);
}

Result<socket_t> Socket::accept()
{
    int conn_fd = ::accept(fd, nullptr, nullptr);
    if (conn_fd < 0) {
        return LibCError();
    }
    TRY(fd_make_nonblocking(conn_fd));
    return std::make_shared<Socket>(conn_fd);
}

Result<size_t> Socket::read_available_bytes()
{
    char   buf[BUF_SZ];
    size_t total = 0;
    while (true) {
        ssize_t bytes_read = ::read(fd, buf, BUF_SZ);
        if (bytes_read < 0) {
            if (errno == EAGAIN) {
                break;
            }
            if (errno != EINTR) {
                return LibCError();
            }
            continue;
        }
        if (bytes_read == 0) {
            break;
        }
        total += bytes_read;
        buffer.append(buf, bytes_read);
        if (bytes_read < BUF_SZ) {
            break;
        }
    }
    return total;
}

Result<size_t> Socket::fill_buffer()
{
    TRY(read_available_bytes());
    if (!buffer.empty()) {
        return buffer.length();
    }

    struct pollfd poll_fd = { 0 };
    poll_fd.fd = fd;
    poll_fd.events = POLLIN;

    while (true) {
        if (poll(&poll_fd, 1, -1) == -1) {
            if (errno == EINTR) {
                continue;
            }
            return LibCError();
        }
        if (poll_fd.revents & POLLIN) {
            break;
        }
        if (poll_fd.revents & POLLHUP) {
            return LibCError("Socket connection closed");
        }
    }
    TRY(read_available_bytes());
    assert(!buffer.empty());
    return buffer.length();
}

Result<std::string> Socket::read(size_t count)
{
    std::string out = {};

    size_t total = 0;
    trace(SOCKET, "socket_read(%zu)", count);
    do {
        TRY(fill_buffer());
        if (!count && !buffer.empty()) {
            trace(SOCKET, "socket_read(%zu) => NULL", count);
            return out;
        }
        size_t available = buffer.length();
        size_t remaining = count - total;
        if (available <= remaining) {
            if (out.empty()) {
                out = std::move(buffer);
                buffer = {};
            } else {
                out.append(buffer);
                buffer.clear();
            }
            total += available;
        } else {
            if (out.empty()) {
                out = std::move(buffer);
                buffer = out.substr(remaining, available - remaining);
                out.resize(remaining);
            } else {
                out.append(buffer.substr(0, remaining));
                buffer.erase(0, remaining);
            }
            total = count;
        }
        trace(SOCKET, "socket_read({}): read chunk of {} total {}", count, available, total);
    } while (total < count);
    trace(SOCKET, "socket_read({}) => {}}", count, out.length());
    return out;
}

Result<std::string> Socket::readln()
{
    std::string out {};
    while (true) {
        TRY(fill_buffer());
        trace(SOCKET, "socket_readln: {} bytes available", buffer.length());
        for (size_t ix = 0; ix < buffer.length(); ++ix) {
            char ch = buffer[ix];
            switch (ch) {
            case '\r':
                break;
            case '\n':
                if (ix < buffer.length() - 1) {
                    buffer.erase(0, ix);
                } else {
                    buffer.clear();
                }
                trace(SOCKET, "socket_readln: {} bytes consumed", ix + 1);
                return out;
            default:
                out += ch;
                break;
            }
        }
        trace(SOCKET, "socket_readln: buffer depleted");
        buffer.clear();
    }
}

Result<size_t> Socket::write(std::string_view const& buf, size_t num)
{
    ssize_t total = 0;
    assert(buf.length() <= num);
    trace(SOCKET, "socket_write({})", num);
    while (total < num) {
        ssize_t written = ::write(fd, buf.data() + total, num - total);
        if (written < 0) {
            if (errno == EAGAIN) {
                trace(SOCKET, "Socket::write(%zu) - EAGAIN (retrying)", num);
                continue;
            }
            auto err = LibCError();
            trace(SOCKET, "Socket::write({}) - error {}", err.to_string());
            return err;
        }
        if (written == 0) {
            trace(SOCKET, "Socket::write({}) - incomplete write", num);
            return LibCError("Incomplete write to socket: {} < {}", written, num);
        }
        trace(SOCKET, "socket_write: chunk {}", written);
        total += written;
    }
    trace(SOCKET, "socket_write: {}", total);
    return total;
}

Result<size_t> Socket::writeln(std::string_view const& buf)
{
    TRY(write(buffer, buffer.length()));
    char eol = '\n';
    TRY(write(&eol, 1));
    return buf.length() + 1;
}

CError Socket::close()
{
    if (auto res = ::close(fd); res < 0) {
        return LibCError();
    }
    return {};
}

CError fd_make_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return LibCError();
    }
    flags = flags | O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        return LibCError();
    }
    return {};
}

Result<struct sockaddr_in> tcpip_address_resolve(std::string_view const &ip_address)
{
    struct addrinfo hints, *res, *res0;
    int             error;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    std::string address { ip_address };
    if ((error = getaddrinfo(address.c_str(), NULL, &hints, &res0)) != 0) {
        return LibCError(std::format("Error resolving IP address '{:}': {:}",
            address, gai_strerror(error)));
    }
    if (!res0) {
        return LibCError(std::format("Error resolving IP address '{:}': {:}",
            address, gai_strerror(error)));
    }
    struct sockaddr_in addr;
    for (res = res0; res; res = res->ai_next) {
        if (res->ai_family == AF_INET && res->ai_socktype == SOCK_STREAM) {
            assert(res->ai_addrlen == sizeof(struct sockaddr_in));
            memcpy(&addr, res->ai_addr, sizeof(struct sockaddr_in));
            freeaddrinfo(res0);
            return addr;
        }
    }
    freeaddrinfo(res0);
    return LibCError("Could not resolve address '{:}' to an IP address", address);
}

Result<std::string> read_file_by_name(std::string_view const& file_name)
{
    std::string fname { file_name };
    int fd = open(fname.c_str(), O_RDONLY);
    if (fd < 0) {
        return LibCError();
    }
    auto ret = read_file(fd);
    close(fd);
    return ret;
}

Result<std::string> read_file_at(int dir_fd, std::string_view const& file_name)
{
    std::string fname { file_name };
    int  fd = openat(dir_fd, fname.c_str(), O_RDONLY);
    if (fd < 0) {
        return LibCError();
    }
    auto ret = read_file(fd);
    close(fd);
    return ret;
}

Result<std::string> read_file(int fd)
{
    struct stat sb;
    if (fstat(fd, &sb) < 0) {
        return LibCError();
    }
    std::string ret {};
    size_t sz = sb.st_size;
    ret.resize(sz+1);
    if (auto err = ::read(fd, ret.data(), sz); err < 0) {
        return LibCError();
    }
    return ret;
}

Result<ssize_t> write_file_by_name(std::string_view const& file_name, std::string_view const& contents)
{
    std::string fname { file_name };
    int  fd = open(fname.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        return LibCError();
    }
    auto ret = write_file(fd, contents);
    close(fd);
    return ret;
}

Result<ssize_t> write_file_at(int dir_fd, std::string_view const& file_name, std::string_view const& contents)
{
    std::string fname { file_name };
    int  fd = openat(dir_fd, fname.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        return LibCError();
    }
    auto ret = write_file(fd, contents);
    close(fd);
    return ret;
}

Result<ssize_t> write_file(int fd, std::string_view const& contents)
{
    ssize_t total { ::write(fd, contents.data(), contents.length()) };
    if (total < 0) {
        return LibCError();
    }
    return total;
}

}
