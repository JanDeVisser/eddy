/*
 * Copyright (c) 2024, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <cctype>

#include <LibCore/IO.h>

#include <App/Buffer.h>
#include <App/Eddy.h>

namespace Eddy {

using namespace LibCore;

Buffer::Buffer(pWidget const &parent)
    : Widget(parent)
{
    //    widget_register(
    //        buffer,
    //        "lsp-textDocument/semanticTokens/full",
    //        (WidgetCommandHandler) buffer_semantic_tokens_response);
}

Result<pBuffer> Buffer::open(std::string_view const &name)
{
    auto buffer = Widget::make<Buffer>(Eddy::the());
    buffer->name = name;
    buffer->m_mode = Eddy::the()->get_mode_for_buffer(buffer);
    if (auto listener = buffer->m_mode->event_listener(); listener) {
        buffer->add_listener(listener);
    }
    buffer->text = TRY_EVAL(read_file_by_name(name));
    buffer->lines.clear();
    buffer->build_indices();
    return buffer;
}

pBuffer Buffer::new_buffer()
{
    auto buffer = Widget::make<Buffer>(Eddy::the());
    buffer->lines.clear();
    buffer->build_indices();
    //    mode = eddy_get_mode_for_buffer(&eddy, name);
    //    if (mode) {
    //        buffer_add_listener(buffer, mode->event_listener);
    //    }
    return buffer;
}

void Buffer::close()
{
    BufferEvent event;
    event.type = BufferEventType::Close;
    apply(event);
}

/*
 * A line is a sequence of tokens. Last token is EOL (end of line)
 * - m_index_of is index of first char of the line.
 * - m_length includes the EOL
 * - Last line may not have a terminating EOL.
 * - EOF is not added to last line.
 */
bool Buffer::build_indices()
{
    assert(indexed_version <= version);
    if (indexed_version == version && !lines.empty() > 0) {
        return false;
    }
    lines.clear();
    tokens.clear();

    mode()->initialize_source();

    Index  current { 0, 0 };
    size_t lineno { 0 };
    trace(EDIT, "build_indices. version {} indexed_version {} length: {}", version, indexed_version, text.length());
    bool done = false;
    std::stringstream ss;
    do {
        auto const t = mode()->lex();
        switch (t.kind()) {
        case TokenKind::EndOfFile:
            trace(EDIT, "[EOF]");
            done = true;
            break;
        case TokenKind::EndOfLine: {
            assert(t <= text.length());
            current.extend(t);
            tokens.emplace_back(t);
            lines.push_back(current);
            trace(EDIT, "{}[EOL] index: {} length: {} end: {} first {} num {}", ss.view(), current.begin(), current.length(), current.end(), current.first_token(), current.tokens());
	    ss = std::stringstream {};
            ++lineno;
            auto index = current.end();
            current = Index { index, tokens.size() };
        } break;
        default:
	    ss << "[" << TokenKind_name(t.kind()) << "]{" << text.substr(t, t.length()) << "}";
            current.extend(t);
            tokens.emplace_back(t);
            break;
        }
    } while (!done);
    lines.push_back(current);
    trace(EDIT, "=====================");
    indexed_version = version;
    BufferEvent event;
    event.type = BufferEventType::Indexed;
    for (auto &listener : listeners) {
        listener(std::dynamic_pointer_cast<Buffer>(self()), event);
    }
    return true;
}

size_t Buffer::line_for_index(size_t index) const
{
    if (lines.empty()) {
        return 0;
    }
    size_t line_min = 0;
    size_t line_max = lines.size() - 1;
    while (true) {
        auto        lineno = line_min + (line_max - line_min) / 2;
        auto const &line = lines[lineno];
        if ((lineno < lines.size() - 1 && line.contains(index)) || (lineno == lines.size() - 1 && line.begin() <= index)) {
            return lineno;
        }
        if (line.begin() > index) {
            line_max = lineno;
        } else {
            line_min = lineno + 1;
        }
    }
}

Vec<size_t> Buffer::index_to_position(size_t index) const
{
    Vec<size_t> ret {};
    ret.line = line_for_index(index);
    ret.column = index - lines[ret.line].begin();
    return ret;
}

size_t Buffer::position_to_index(Vec<size_t> position) const
{
    Index const &line = lines[position.line];
    return line.begin() + position.column;
}

void Buffer::apply(BufferEvent const &event)
{
    switch (event.type) {
    case BufferEventType::Insert: {
        auto const &insert = event.insert();
        if (insert.empty()) {
            return;
        }

        if (event.position < text.length()) {
            text.insert(event.position, insert);
        } else {
            text.append(insert);
        }
        ++version;
    } break;
    case BufferEventType::Delete: {
        auto const &deletion = event.deletion();
        text.erase(event.position, deletion.length());
        ++version;
    } break;
    case BufferEventType::Replace: {
        auto const &replacement = event.replacement();
        if (replacement.replacement.empty()) {
            return;
        }
        text.erase(event.position, replacement.overwritten.length());
        if (event.position < text.length()) {
            text.insert(event.position, replacement.replacement);
        } else {
            text.append(replacement.replacement);
        }
        ++version;
    } break;
    case BufferEventType::Save: {
        assert(saved_version <= version);
        auto const &filename = event.filename();
        if (filename.has_value()) {
            name = filename.value();
        }
        if (name.empty() || saved_version == version) {
            return;
        }
        MUST(write_file_by_name(name, text));
        saved_version = version;
    } break;
    case BufferEventType::Close: {
        for (auto &listener : listeners) {
            listener(std::dynamic_pointer_cast<Buffer>(self()), event);
        }
        text.clear();
        undo_stack.clear();
        undo_pointer = 0;
        lines.clear();
        tokens.clear();
        version = 0;
        saved_version = 0;
        indexed_version = 0;
        name.clear();
        m_uri.clear();
        return;
    }
    default:
        break;
    }
    for (auto &listener : listeners) {
        listener(std::dynamic_pointer_cast<Buffer>(self()), event);
    }
}

void Buffer::edit(BufferEvent const &event)
{
    apply(event);
    undo_stack.push_back(event);
    undo_pointer = undo_stack.size();
}

void Buffer::undo()
{
    if (undo_pointer <= 0 || undo_pointer >= undo_stack.size()) {
        return;
    }
    auto const &edit = undo_stack[--undo_pointer];
    auto        revert = edit.revert();
    apply(revert);
}

void Buffer::redo()
{
    if (undo_pointer >= undo_stack.size()) {
        return;
    }
    auto &edit = undo_stack[undo_pointer++];
    apply(edit);
}

void Buffer::insert(size_t at, std::string_view const &insert)
{
    if (insert.empty()) {
        return;
    }
    at = clamp(at, 0, text.length());
    EventRange range;
    range.start = range.end = index_to_position(static_cast<int>(at));
    edit(BufferEvent::make_insert(range, at, insert));
}

void Buffer::del(size_t at, size_t count)
{
    at = clamp(at, 0, text.length());
    count = clamp(count, 0, text.length() - at);
    if (count == 0) {
        return;
    }
    EventRange range;
    range.start = index_to_position(static_cast<int>(at));
    range.end = index_to_position(static_cast<int>(at + count));
    auto const &del = text.substr(at, count);
    edit(BufferEvent::make_delete(range, at, del));
}

void Buffer::replace(size_t at, size_t num, std::string_view const &replacement)
{
    at = clamp(at, 0, text.length());
    num = clamp(num, 0, text.length() - at);
    if (num == 0) {
        return;
    }
    std::string_view overwritten = { text.begin() + at, text.begin() + at + num };
    EventRange       range;
    range.start = index_to_position(static_cast<int>(at));
    range.end = index_to_position(static_cast<int>(at + num));
    edit(BufferEvent::make_replacement(range, at, overwritten, replacement));
}

void Buffer::merge_lines(size_t top_line)
{
    if (top_line > lines.size() - 1) {
        return;
    }
    if (top_line < 0) {
        top_line = 0;
    }
    Index &line = lines[top_line];
    replace(line.end(), 1, " ");
}

void Buffer::save()
{
    apply(BufferEvent::make_save());
}

void Buffer::save_as(std::string_view const &new_name)
{
    apply(BufferEvent::make_save_as(new_name));
}

size_t Buffer::word_boundary_left(size_t index) const
{
    index = clamp(index, 0, text.length() - 1);
    if (isalnum(text[index]) || text[index] == '_') {
        while (((int) index) > 0 && (isalnum(text[index]) || text[index] == '_')) {
            --index;
        }
        ++index;
    } else {
        while (((int) index) > 0 && (!isalnum(text[index]) && text[index] != '_')) {
            --index;
        }
        ++index;
    }
    return index;
}

size_t Buffer::word_boundary_right(size_t index) const
{
    index = clamp(index, 0, text.length() - 1);
    size_t max_index = text.length();
    if (isalnum(text[index]) || text[index] == '_') {
        while (index < max_index && (isalnum(text[index]) || text[index] == '_')) {
            ++index;
        }
    } else {
        while (index < max_index && (!isalnum(text[index]) && text[index] != '_')) {
            ++index;
        }
    }
    return index;
}

void Buffer::add_listener(BufferEventListener const &listener)
{
    listeners.emplace_back(listener);
}

std::string const &Buffer::uri()
{
    if (m_uri.empty() && !name.empty()) {
        m_uri = std::format("file://{}/{}", Eddy::the()->project->project_dir, name);
    }
    return m_uri;
}

#if 0
bool lsp_init(Buffer *buffer)
{
    if (!mode || !mode->lsp.handlers.start) {
        return false;
    }
    lsp_initialize(&mode->lsp);
    return true;
}

void lsp_semantic_tokens(Buffer *buffer)
{
    if (!lsp_init(buffer)) {
        return;
    }

    if (sv_empty(name)) {
        return;
    }
    SemanticTokensParams semantic_tokens_params = { 0 };
    semantic_tokens_params.textDocument = (TextDocumentIdentifier) {
        .uri = buffer_uri(buffer),
    };
    OptionalJSONValue semantic_tokens_params_json = SemanticTokensParams_encode(semantic_tokens_params);
    MUST(Int, lsp_message(&mode->lsp, buffer, "textDocument/semanticTokens/full", semantic_tokens_params_json));
}

void buffer_semantic_tokens_response(Buffer *buffer, JSONValue resp)
{
    Response response = response_decode(&resp);
    if (!response_success(&response)) {
        return;
    }
    if (!response.result.has_value) {
        trace(LSP, "No response to textDocument/semanticTokens/full");
        return;
    }
    OptionalSemanticTokens result_maybe = SemanticTokens_decode(response.result);
    if (!result_maybe.has_value) {
        trace(LSP, "Couldn't decode response to textDocument/semanticTokens/full");
        return;
    }
    SemanticTokens result = result_maybe.value;
    size_t         lineno = 0;
    Index         *line = lines.elements + lineno;
    size_t         offset = 0;
    UInt32s        data = result.data;
    size_t         token_ix = 0;
    for (size_t ix = 0; ix < result.data.size; ix += 5) {
        //        trace(LSP, "Semantic token[%zu] = (Δline %d, Δcol %d, length %d type %d %d)", ix, data.elements[ix], data.elements[ix + 1], data.elements[ix + 2], data.elements[ix + 3], data.elements[ix + 4]);
        if (data.elements[ix] > 0) {
            lineno += data.elements[ix];
            if (lineno >= lines.size) {
                // trace(LSP, "Semantic token[%zu] lineno %zu > lines %zu", ix, lineno, lines.size);
                break;
            }
            line = lines.elements + lineno;
            offset = 0;
            token_ix = 0;
        }
        offset += data.elements[ix + 1];
        size_t     length = data.elements[ix + 2];
        StringView text = { line->line.ptr + offset, length };
        //        trace(LSP, "Semantic token[%zu]: line: %zu col: %zu length: %zu %.*s", ix, lineno, offset, length, SV_ARG(text));
        OptionalColours colours = theme_semantic_colours(&eddy.theme, data.elements[ix + 3]);
        if (!colours.has_value) {
            //            trace(LSP, "SemanticTokenType index %d not mapped", data.elements[ix + 3]);
            continue;
        }
        if (log_category_on(LSP)) {
            StringView s = colour_to_rgb(colours.value.fg);
            //            trace(LSP, "Semantic token[%zu] = color '%.*s'", ix, SV_ARG(s));
            sv_free(s);
        }
        for (; token_ix < line->num_tokens; ++token_ix) {
            assert(line->first_token + token_ix < tokens.size);
            DisplayToken *t = tokens.elements + line->first_token + token_ix;
            if (t->index == line->index_of + offset && t->length == length) {
                t->color = colour_to_color(colours.value.fg);
                break;
            }
        }
        if (token_ix == line->num_tokens) {
            info("SemanticTokens OUT OF SYNC");
            break;
        }
    }
}

void lsp_on_open(Buffer *buffer)
{
    if (!lsp_init(buffer)) {
        return;
    }
    if (sv_empty(name)) {
        return;
    }
    DidOpenTextDocumentParams did_open = { 0 };
    did_open.textDocument = (TextDocumentItem) {
        .uri = buffer_uri(buffer),
        .languageId = sv_from("c"),
        .version = 0,
        .text = text.view
    };
    OptionalJSONValue did_open_json = DidOpenTextDocumentParams_encode(did_open);
    lsp_notification(&mode->lsp, "textDocument/didOpen", did_open_json);
}

void lsp_did_save(Buffer *buffer)
{
    if (!lsp_init(buffer)) {
        return;
    }
    if (sv_empty(name)) {
        return;
    }
    DidSaveTextDocumentParams did_save = { 0 };
    did_save.textDocument = (TextDocumentIdentifier) {
        .uri = buffer_uri(buffer),
    };
    did_save.text = OptionalStringView_create(text.view);
    OptionalJSONValue did_save_json = DidSaveTextDocumentParams_encode(did_save);
    lsp_notification(&mode->lsp, "textDocument/didSave", did_save_json);
}

void lsp_did_close(Buffer *buffer)
{
    if (!lsp_init(buffer)) {
        return;
    }
    if (sv_empty(name)) {
        return;
    }
    DidCloseTextDocumentParams did_close = { 0 };
    did_close.textDocument = (TextDocumentIdentifier) {
        .uri = buffer_uri(buffer),
    };
    OptionalJSONValue did_close_json = DidCloseTextDocumentParams_encode(did_close);
    lsp_notification(&mode->lsp, "textDocument/didClose", did_close_json);
}

void lsp_did_change(Buffer *buffer, IntVector2 start, IntVector2 end, StringView text)
{
    if (!lsp_init(buffer)) {
        return;
    }
    if (sv_empty(name)) {
        return;
    }
    DidChangeTextDocumentParams did_change = { 0 };
    did_change.textDocument.uri = buffer_uri(buffer);
    did_change.textDocument.version = version;
    TextDocumentContentChangeEvent contentChange = { 0 };
    contentChange._0.range.start.line = start.line;
    contentChange._0.range.start.character = start.column;
    contentChange._0.range.end.line = end.line;
    contentChange._0.range.end.character = end.column;
    contentChange._0.text = text;
    da_append_TextDocumentContentChangeEvent(&did_change.contentChanges, contentChange);
    OptionalJSONValue did_change_json = DidChangeTextDocumentParams_encode(did_change);
    lsp_notification(&mode->lsp, "textDocument/didChange", did_change_json);
}

#endif

}
