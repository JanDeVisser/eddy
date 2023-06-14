/*
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <core/FileBuffer.h>
#include <Mode/Mode.h>

namespace scratch {

Mode::Mode(Document& doc)
    : m_doc(doc)
{
    open_file = [this](fs::path const& path) -> ErrorOr<std::string, SystemError> {
        auto buffer = TRY(FileBuffer::from_file(path));
        return buffer->buffer();
    };
}

[[nodiscard]] Document const& Mode::document() const
{
    return m_doc;
}

[[nodiscard]] Document& Mode::document()
{
    return m_doc;
}


}
