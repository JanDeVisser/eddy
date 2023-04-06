/**
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * THIS IS GENERATED CODE. DO NOT MODIFY.
 */

#pragma once

#include <map>
#include <optional>
#include <variant>
#include <vector>

#include <LSP/Message.h>

namespace scratch::lsp {

enum class SemanticTokenTypes {
    Namespace,
    Type,
    Class,
    Enum,
    Interface,
    Struct,
    Typeparameter,
    Parameter,
    Variable,
    Property,
    Enummember,
    Event,
    Function,
    Method,
    Macro,
    Keyword,
    Modifier,
    Comment,
    String,
    Number,
    Regexp,
    Operator,
    Decorator,
};

std::string_view string_view(SemanticTokenTypes value)
{
    switch (value) {
    case SemanticTokenTypes::Namespace: "namespace"sv;
    case SemanticTokenTypes::Type: "type"sv;
    case SemanticTokenTypes::Class: "class"sv;
    case SemanticTokenTypes::Enum: "enum"sv;
    case SemanticTokenTypes::Interface: "interface"sv;
    case SemanticTokenTypes::Struct: "struct"sv;
    case SemanticTokenTypes::Typeparameter: "typeParameter"sv;
    case SemanticTokenTypes::Parameter: "parameter"sv;
    case SemanticTokenTypes::Variable: "variable"sv;
    case SemanticTokenTypes::Property: "property"sv;
    case SemanticTokenTypes::Enummember: "enumMember"sv;
    case SemanticTokenTypes::Event: "event"sv;
    case SemanticTokenTypes::Function: "function"sv;
    case SemanticTokenTypes::Method: "method"sv;
    case SemanticTokenTypes::Macro: "macro"sv;
    case SemanticTokenTypes::Keyword: "keyword"sv;
    case SemanticTokenTypes::Modifier: "modifier"sv;
    case SemanticTokenTypes::Comment: "comment"sv;
    case SemanticTokenTypes::String: "string"sv;
    case SemanticTokenTypes::Number: "number"sv;
    case SemanticTokenTypes::Regexp: "regexp"sv;
    case SemanticTokenTypes::Operator: "operator"sv;
    case SemanticTokenTypes::Decorator: "decorator"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(SemanticTokenTypes const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokenTypes& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "namespace") target = SemanticTokenTypes::Namespace;
    if (value.to_string() == "type") target = SemanticTokenTypes::Type;
    if (value.to_string() == "class") target = SemanticTokenTypes::Class;
    if (value.to_string() == "enum") target = SemanticTokenTypes::Enum;
    if (value.to_string() == "interface") target = SemanticTokenTypes::Interface;
    if (value.to_string() == "struct") target = SemanticTokenTypes::Struct;
    if (value.to_string() == "typeParameter") target = SemanticTokenTypes::Typeparameter;
    if (value.to_string() == "parameter") target = SemanticTokenTypes::Parameter;
    if (value.to_string() == "variable") target = SemanticTokenTypes::Variable;
    if (value.to_string() == "property") target = SemanticTokenTypes::Property;
    if (value.to_string() == "enumMember") target = SemanticTokenTypes::Enummember;
    if (value.to_string() == "event") target = SemanticTokenTypes::Event;
    if (value.to_string() == "function") target = SemanticTokenTypes::Function;
    if (value.to_string() == "method") target = SemanticTokenTypes::Method;
    if (value.to_string() == "macro") target = SemanticTokenTypes::Macro;
    if (value.to_string() == "keyword") target = SemanticTokenTypes::Keyword;
    if (value.to_string() == "modifier") target = SemanticTokenTypes::Modifier;
    if (value.to_string() == "comment") target = SemanticTokenTypes::Comment;
    if (value.to_string() == "string") target = SemanticTokenTypes::String;
    if (value.to_string() == "number") target = SemanticTokenTypes::Number;
    if (value.to_string() == "regexp") target = SemanticTokenTypes::Regexp;
    if (value.to_string() == "operator") target = SemanticTokenTypes::Operator;
    if (value.to_string() == "decorator") target = SemanticTokenTypes::Decorator;
    return {};
}

enum class SemanticTokenModifiers {
    Declaration,
    Definition,
    Readonly,
    Static,
    Deprecated,
    Abstract,
    Async,
    Modification,
    Documentation,
    Defaultlibrary,
};

std::string_view string_view(SemanticTokenModifiers value)
{
    switch (value) {
    case SemanticTokenModifiers::Declaration: "declaration"sv;
    case SemanticTokenModifiers::Definition: "definition"sv;
    case SemanticTokenModifiers::Readonly: "readonly"sv;
    case SemanticTokenModifiers::Static: "static"sv;
    case SemanticTokenModifiers::Deprecated: "deprecated"sv;
    case SemanticTokenModifiers::Abstract: "abstract"sv;
    case SemanticTokenModifiers::Async: "async"sv;
    case SemanticTokenModifiers::Modification: "modification"sv;
    case SemanticTokenModifiers::Documentation: "documentation"sv;
    case SemanticTokenModifiers::Defaultlibrary: "defaultLibrary"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(SemanticTokenModifiers const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokenModifiers& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "declaration") target = SemanticTokenModifiers::Declaration;
    if (value.to_string() == "definition") target = SemanticTokenModifiers::Definition;
    if (value.to_string() == "readonly") target = SemanticTokenModifiers::Readonly;
    if (value.to_string() == "static") target = SemanticTokenModifiers::Static;
    if (value.to_string() == "deprecated") target = SemanticTokenModifiers::Deprecated;
    if (value.to_string() == "abstract") target = SemanticTokenModifiers::Abstract;
    if (value.to_string() == "async") target = SemanticTokenModifiers::Async;
    if (value.to_string() == "modification") target = SemanticTokenModifiers::Modification;
    if (value.to_string() == "documentation") target = SemanticTokenModifiers::Documentation;
    if (value.to_string() == "defaultLibrary") target = SemanticTokenModifiers::Defaultlibrary;
    return {};
}

enum class DocumentDiagnosticReportKind {
    Full,
    Unchanged,
};

std::string_view string_view(DocumentDiagnosticReportKind value)
{
    switch (value) {
    case DocumentDiagnosticReportKind::Full: "full"sv;
    case DocumentDiagnosticReportKind::Unchanged: "unchanged"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(DocumentDiagnosticReportKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentDiagnosticReportKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "full") target = DocumentDiagnosticReportKind::Full;
    if (value.to_string() == "unchanged") target = DocumentDiagnosticReportKind::Unchanged;
    return {};
}

enum class ErrorCodes {
    Parseerror = -32700,
    Invalidrequest = -32600,
    Methodnotfound = -32601,
    Invalidparams = -32602,
    Internalerror = -32603,
    Servernotinitialized = -32002,
    Unknownerrorcode = -32001,
};

template<>
inline JSONValue to_json(ErrorCodes const& obj)
{
    return { static_cast<integer>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ErrorCodes& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<ErrorCodes>(*(value.to_int<integer>()));
    return {};
}

enum class LSPErrorCodes {
    Requestfailed = -32803,
    Servercancelled = -32802,
    Contentmodified = -32801,
    Requestcancelled = -32800,
};

template<>
inline JSONValue to_json(LSPErrorCodes const& obj)
{
    return { static_cast<integer>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LSPErrorCodes& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<LSPErrorCodes>(*(value.to_int<integer>()));
    return {};
}

enum class FoldingRangeKind {
    Comment,
    Imports,
    Region,
};

std::string_view string_view(FoldingRangeKind value)
{
    switch (value) {
    case FoldingRangeKind::Comment: "comment"sv;
    case FoldingRangeKind::Imports: "imports"sv;
    case FoldingRangeKind::Region: "region"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(FoldingRangeKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRangeKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "comment") target = FoldingRangeKind::Comment;
    if (value.to_string() == "imports") target = FoldingRangeKind::Imports;
    if (value.to_string() == "region") target = FoldingRangeKind::Region;
    return {};
}

enum class SymbolKind {
    File = 1,
    Module = 2,
    Namespace = 3,
    Package = 4,
    Class = 5,
    Method = 6,
    Property = 7,
    Field = 8,
    Constructor = 9,
    Enum = 10,
    Interface = 11,
    Function = 12,
    Variable = 13,
    Constant = 14,
    String = 15,
    Number = 16,
    Boolean = 17,
    Array = 18,
    Object = 19,
    Key = 20,
    Null = 21,
    Enummember = 22,
    Struct = 23,
    Event = 24,
    Operator = 25,
    Typeparameter = 26,
};

template<>
inline JSONValue to_json(SymbolKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SymbolKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<SymbolKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class SymbolTag {
    Deprecated = 1,
};

template<>
inline JSONValue to_json(SymbolTag const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SymbolTag& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<SymbolTag>(*(value.to_int<uinteger>()));
    return {};
}

enum class UniquenessLevel {
    Document,
    Project,
    Group,
    Scheme,
    Global,
};

std::string_view string_view(UniquenessLevel value)
{
    switch (value) {
    case UniquenessLevel::Document: "document"sv;
    case UniquenessLevel::Project: "project"sv;
    case UniquenessLevel::Group: "group"sv;
    case UniquenessLevel::Scheme: "scheme"sv;
    case UniquenessLevel::Global: "global"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(UniquenessLevel const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, UniquenessLevel& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "document") target = UniquenessLevel::Document;
    if (value.to_string() == "project") target = UniquenessLevel::Project;
    if (value.to_string() == "group") target = UniquenessLevel::Group;
    if (value.to_string() == "scheme") target = UniquenessLevel::Scheme;
    if (value.to_string() == "global") target = UniquenessLevel::Global;
    return {};
}

enum class MonikerKind {
    Import,
    Export,
    Local,
};

std::string_view string_view(MonikerKind value)
{
    switch (value) {
    case MonikerKind::Import: "import"sv;
    case MonikerKind::Export: "export"sv;
    case MonikerKind::Local: "local"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(MonikerKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MonikerKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "import") target = MonikerKind::Import;
    if (value.to_string() == "export") target = MonikerKind::Export;
    if (value.to_string() == "local") target = MonikerKind::Local;
    return {};
}

enum class InlayHintKind {
    Type = 1,
    Parameter = 2,
};

template<>
inline JSONValue to_json(InlayHintKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<InlayHintKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class MessageType {
    Error = 1,
    Warning = 2,
    Info = 3,
    Log = 4,
};

template<>
inline JSONValue to_json(MessageType const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MessageType& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<MessageType>(*(value.to_int<uinteger>()));
    return {};
}

enum class TextDocumentSyncKind {
    None = 0,
    Full = 1,
    Incremental = 2,
};

template<>
inline JSONValue to_json(TextDocumentSyncKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentSyncKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<TextDocumentSyncKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class TextDocumentSaveReason {
    Manual = 1,
    Afterdelay = 2,
    Focusout = 3,
};

template<>
inline JSONValue to_json(TextDocumentSaveReason const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentSaveReason& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<TextDocumentSaveReason>(*(value.to_int<uinteger>()));
    return {};
}

enum class CompletionItemKind {
    Text = 1,
    Method = 2,
    Function = 3,
    Constructor = 4,
    Field = 5,
    Variable = 6,
    Class = 7,
    Interface = 8,
    Module = 9,
    Property = 10,
    Unit = 11,
    Value = 12,
    Enum = 13,
    Keyword = 14,
    Snippet = 15,
    Color = 16,
    File = 17,
    Reference = 18,
    Folder = 19,
    Enummember = 20,
    Constant = 21,
    Struct = 22,
    Event = 23,
    Operator = 24,
    Typeparameter = 25,
};

template<>
inline JSONValue to_json(CompletionItemKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionItemKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<CompletionItemKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class CompletionItemTag {
    Deprecated = 1,
};

template<>
inline JSONValue to_json(CompletionItemTag const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionItemTag& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<CompletionItemTag>(*(value.to_int<uinteger>()));
    return {};
}

enum class InsertTextFormat {
    Plaintext = 1,
    Snippet = 2,
};

template<>
inline JSONValue to_json(InsertTextFormat const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InsertTextFormat& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<InsertTextFormat>(*(value.to_int<uinteger>()));
    return {};
}

enum class InsertTextMode {
    Asis = 1,
    Adjustindentation = 2,
};

template<>
inline JSONValue to_json(InsertTextMode const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InsertTextMode& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<InsertTextMode>(*(value.to_int<uinteger>()));
    return {};
}

enum class DocumentHighlightKind {
    Text = 1,
    Read = 2,
    Write = 3,
};

template<>
inline JSONValue to_json(DocumentHighlightKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlightKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<DocumentHighlightKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class CodeActionKind {
    Empty,
    Quickfix,
    Refactor,
    Refactorextract,
    Refactorinline,
    Refactorrewrite,
    Source,
    Sourceorganizeimports,
    Sourcefixall,
};

std::string_view string_view(CodeActionKind value)
{
    switch (value) {
    case CodeActionKind::Empty: ""sv;
    case CodeActionKind::Quickfix: "quickfix"sv;
    case CodeActionKind::Refactor: "refactor"sv;
    case CodeActionKind::Refactorextract: "refactor.extract"sv;
    case CodeActionKind::Refactorinline: "refactor.inline"sv;
    case CodeActionKind::Refactorrewrite: "refactor.rewrite"sv;
    case CodeActionKind::Source: "source"sv;
    case CodeActionKind::Sourceorganizeimports: "source.organizeImports"sv;
    case CodeActionKind::Sourcefixall: "source.fixAll"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(CodeActionKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "") target = CodeActionKind::Empty;
    if (value.to_string() == "quickfix") target = CodeActionKind::Quickfix;
    if (value.to_string() == "refactor") target = CodeActionKind::Refactor;
    if (value.to_string() == "refactor.extract") target = CodeActionKind::Refactorextract;
    if (value.to_string() == "refactor.inline") target = CodeActionKind::Refactorinline;
    if (value.to_string() == "refactor.rewrite") target = CodeActionKind::Refactorrewrite;
    if (value.to_string() == "source") target = CodeActionKind::Source;
    if (value.to_string() == "source.organizeImports") target = CodeActionKind::Sourceorganizeimports;
    if (value.to_string() == "source.fixAll") target = CodeActionKind::Sourcefixall;
    return {};
}

enum class TraceValues {
    Off,
    Messages,
    Verbose,
};

std::string_view string_view(TraceValues value)
{
    switch (value) {
    case TraceValues::Off: "off"sv;
    case TraceValues::Messages: "messages"sv;
    case TraceValues::Verbose: "verbose"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(TraceValues const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TraceValues& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "off") target = TraceValues::Off;
    if (value.to_string() == "messages") target = TraceValues::Messages;
    if (value.to_string() == "verbose") target = TraceValues::Verbose;
    return {};
}

enum class MarkupKind {
    Plaintext,
    Markdown,
};

std::string_view string_view(MarkupKind value)
{
    switch (value) {
    case MarkupKind::Plaintext: "plaintext"sv;
    case MarkupKind::Markdown: "markdown"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(MarkupKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MarkupKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "plaintext") target = MarkupKind::Plaintext;
    if (value.to_string() == "markdown") target = MarkupKind::Markdown;
    return {};
}

enum class PositionEncodingKind {
    Utf8,
    Utf16,
    Utf32,
};

std::string_view string_view(PositionEncodingKind value)
{
    switch (value) {
    case PositionEncodingKind::Utf8: "utf-8"sv;
    case PositionEncodingKind::Utf16: "utf-16"sv;
    case PositionEncodingKind::Utf32: "utf-32"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(PositionEncodingKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PositionEncodingKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "utf-8") target = PositionEncodingKind::Utf8;
    if (value.to_string() == "utf-16") target = PositionEncodingKind::Utf16;
    if (value.to_string() == "utf-32") target = PositionEncodingKind::Utf32;
    return {};
}

enum class FileChangeType {
    Created = 1,
    Changed = 2,
    Deleted = 3,
};

template<>
inline JSONValue to_json(FileChangeType const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileChangeType& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<FileChangeType>(*(value.to_int<uinteger>()));
    return {};
}

enum class WatchKind {
    Create = 1,
    Change = 2,
    Delete = 4,
};

template<>
inline JSONValue to_json(WatchKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WatchKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<WatchKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class DiagnosticSeverity {
    Error = 1,
    Warning = 2,
    Information = 3,
    Hint = 4,
};

template<>
inline JSONValue to_json(DiagnosticSeverity const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticSeverity& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<DiagnosticSeverity>(*(value.to_int<uinteger>()));
    return {};
}

enum class DiagnosticTag {
    Unnecessary = 1,
    Deprecated = 2,
};

template<>
inline JSONValue to_json(DiagnosticTag const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticTag& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<DiagnosticTag>(*(value.to_int<uinteger>()));
    return {};
}

enum class CompletionTriggerKind {
    Invoked = 1,
    Triggercharacter = 2,
    Triggerforincompletecompletions = 3,
};

template<>
inline JSONValue to_json(CompletionTriggerKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionTriggerKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<CompletionTriggerKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class SignatureHelpTriggerKind {
    Invoked = 1,
    Triggercharacter = 2,
    Contentchange = 3,
};

template<>
inline JSONValue to_json(SignatureHelpTriggerKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpTriggerKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<SignatureHelpTriggerKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class CodeActionTriggerKind {
    Invoked = 1,
    Automatic = 2,
};

template<>
inline JSONValue to_json(CodeActionTriggerKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionTriggerKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<CodeActionTriggerKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class FileOperationPatternKind {
    File,
    Folder,
};

std::string_view string_view(FileOperationPatternKind value)
{
    switch (value) {
    case FileOperationPatternKind::File: "file"sv;
    case FileOperationPatternKind::Folder: "folder"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(FileOperationPatternKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationPatternKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "file") target = FileOperationPatternKind::File;
    if (value.to_string() == "folder") target = FileOperationPatternKind::Folder;
    return {};
}

enum class NotebookCellKind {
    Markup = 1,
    Code = 2,
};

template<>
inline JSONValue to_json(NotebookCellKind const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookCellKind& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<NotebookCellKind>(*(value.to_int<uinteger>()));
    return {};
}

enum class ResourceOperationKind {
    Create,
    Rename,
    Delete,
};

std::string_view string_view(ResourceOperationKind value)
{
    switch (value) {
    case ResourceOperationKind::Create: "create"sv;
    case ResourceOperationKind::Rename: "rename"sv;
    case ResourceOperationKind::Delete: "delete"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(ResourceOperationKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ResourceOperationKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "create") target = ResourceOperationKind::Create;
    if (value.to_string() == "rename") target = ResourceOperationKind::Rename;
    if (value.to_string() == "delete") target = ResourceOperationKind::Delete;
    return {};
}

enum class FailureHandlingKind {
    Abort,
    Transactional,
    Textonlytransactional,
    Undo,
};

std::string_view string_view(FailureHandlingKind value)
{
    switch (value) {
    case FailureHandlingKind::Abort: "abort"sv;
    case FailureHandlingKind::Transactional: "transactional"sv;
    case FailureHandlingKind::Textonlytransactional: "textOnlyTransactional"sv;
    case FailureHandlingKind::Undo: "undo"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(FailureHandlingKind const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FailureHandlingKind& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "abort") target = FailureHandlingKind::Abort;
    if (value.to_string() == "transactional") target = FailureHandlingKind::Transactional;
    if (value.to_string() == "textOnlyTransactional") target = FailureHandlingKind::Textonlytransactional;
    if (value.to_string() == "undo") target = FailureHandlingKind::Undo;
    return {};
}

enum class PrepareSupportDefaultBehavior {
    Identifier = 1,
};

template<>
inline JSONValue to_json(PrepareSupportDefaultBehavior const& obj)
{
    return { static_cast<uinteger>(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PrepareSupportDefaultBehavior& target)
{
    if (!value.is_integer())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    target = static_cast<PrepareSupportDefaultBehavior>(*(value.to_int<uinteger>()));
    return {};
}

enum class TokenFormat {
    Relative,
};

std::string_view string_view(TokenFormat value)
{
    switch (value) {
    case TokenFormat::Relative: "relative"sv;
    default: fatal("Unreachable");
    }
}

template<>
inline JSONValue to_json(TokenFormat const& obj)
{
    return { string_view(obj) };
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TokenFormat& target)
{
    if (!value.is_string())
         return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "" };
    if (value.to_string() == "relative") target = TokenFormat::Relative;
    return {};
}



struct Position {
    uinteger line { 0 };
    uinteger character { 0 };
};

template<>
inline JSONValue to_json(Position const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "line", obj.line);
    set(ret, "character", obj.character);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Position& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Position" };

    TRY_RETURN(decode(value, "line", target.line));
    TRY_RETURN(decode(value, "character", target.character));
    return {};
}

struct Range {
    Position start ;
    Position end ;
};

template<>
inline JSONValue to_json(Range const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "start", obj.start);
    set(ret, "end", obj.end);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Range& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Range" };

    TRY_RETURN(decode(value, "start", target.start));
    TRY_RETURN(decode(value, "end", target.end));
    return {};
}

struct Location {
    DocumentUri uri ;
    Range range ;
};

template<>
inline JSONValue to_json(Location const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Location& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Location" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

using Definition = std::variant<Location, std::vector<Location>>;
struct LocationLink {
    std::optional<Range> originSelectionRange  {};
    DocumentUri targetUri ;
    Range targetRange ;
    Range targetSelectionRange ;
};

template<>
inline JSONValue to_json(LocationLink const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "originSelectionRange", obj.originSelectionRange);
    set(ret, "targetUri", obj.targetUri);
    set(ret, "targetRange", obj.targetRange);
    set(ret, "targetSelectionRange", obj.targetSelectionRange);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LocationLink& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LocationLink" };

    TRY_RETURN(decode(value, "originSelectionRange", target.originSelectionRange));
    TRY_RETURN(decode(value, "targetUri", target.targetUri));
    TRY_RETURN(decode(value, "targetRange", target.targetRange));
    TRY_RETURN(decode(value, "targetSelectionRange", target.targetSelectionRange));
    return {};
}

using DefinitionLink = LocationLink;
using Declaration = std::variant<Location, std::vector<Location>>;
using DeclarationLink = LocationLink;
struct InlineValueText {
    Range range ;
    string text ;
};

template<>
inline JSONValue to_json(InlineValueText const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "text", obj.text);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueText& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueText" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "text", target.text));
    return {};
}

struct InlineValueVariableLookup {
    Range range ;
    std::optional<string> variableName  {};
    boolean caseSensitiveLookup { false };
};

template<>
inline JSONValue to_json(InlineValueVariableLookup const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "variableName", obj.variableName);
    set(ret, "caseSensitiveLookup", obj.caseSensitiveLookup);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueVariableLookup& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueVariableLookup" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "variableName", target.variableName));
    TRY_RETURN(decode(value, "caseSensitiveLookup", target.caseSensitiveLookup));
    return {};
}

struct InlineValueEvaluatableExpression {
    Range range ;
    std::optional<string> expression  {};
};

template<>
inline JSONValue to_json(InlineValueEvaluatableExpression const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "expression", obj.expression);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueEvaluatableExpression& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueEvaluatableExpression" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "expression", target.expression));
    return {};
}

using InlineValue = std::variant<InlineValueText, InlineValueVariableLookup, InlineValueEvaluatableExpression>;
struct CodeDescription {
    URI href ;
};

template<>
inline JSONValue to_json(CodeDescription const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "href", obj.href);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeDescription& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeDescription" };

    TRY_RETURN(decode(value, "href", target.href));
    return {};
}

struct DiagnosticRelatedInformation {
    Location location ;
    string message ;
};

template<>
inline JSONValue to_json(DiagnosticRelatedInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "location", obj.location);
    set(ret, "message", obj.message);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticRelatedInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticRelatedInformation" };

    TRY_RETURN(decode(value, "location", target.location));
    TRY_RETURN(decode(value, "message", target.message));
    return {};
}

struct Diagnostic {
    Range range ;
    std::optional<DiagnosticSeverity> severity  {};
    std::optional<std::variant<integer, string>> code  {};
    std::optional<CodeDescription> codeDescription  {};
    std::optional<string> source  {};
    string message ;
    std::optional<std::vector<DiagnosticTag>> tags  {};
    std::optional<std::vector<DiagnosticRelatedInformation>> relatedInformation  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(Diagnostic const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "severity", obj.severity);
    set(ret, "code", obj.code);
    set(ret, "codeDescription", obj.codeDescription);
    set(ret, "source", obj.source);
    set(ret, "message", obj.message);
    set(ret, "tags", obj.tags);
    set(ret, "relatedInformation", obj.relatedInformation);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Diagnostic& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Diagnostic" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "severity", target.severity));
    TRY_RETURN(decode(value, "code", target.code));
    TRY_RETURN(decode(value, "codeDescription", target.codeDescription));
    TRY_RETURN(decode(value, "source", target.source));
    TRY_RETURN(decode(value, "message", target.message));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "relatedInformation", target.relatedInformation));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct FullDocumentDiagnosticReport {
    std::string kind  { "full" };
    std::optional<string> resultId  {};
    std::vector<Diagnostic> items  {};
};

template<>
inline JSONValue to_json(FullDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "resultId", obj.resultId);
    set(ret, "items", obj.items);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FullDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FullDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "items", target.items));
    return {};
}

struct UnchangedDocumentDiagnosticReport {
    std::string kind  { "unchanged" };
    string resultId ;
};

template<>
inline JSONValue to_json(UnchangedDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "resultId", obj.resultId);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, UnchangedDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "UnchangedDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    return {};
}

struct RelatedFullDocumentDiagnosticReport : public FullDocumentDiagnosticReport {
    std::optional<std::map<DocumentUri, std::variant<FullDocumentDiagnosticReport, UnchangedDocumentDiagnosticReport>>> relatedDocuments  {};
};

template<>
inline JSONValue to_json(RelatedFullDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<FullDocumentDiagnosticReport>(obj));
    set(ret, "relatedDocuments", obj.relatedDocuments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RelatedFullDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RelatedFullDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "items", target.items));
    TRY_RETURN(decode(value, "relatedDocuments", target.relatedDocuments));
    return {};
}

struct RelatedUnchangedDocumentDiagnosticReport : public UnchangedDocumentDiagnosticReport {
    std::optional<std::map<DocumentUri, std::variant<FullDocumentDiagnosticReport, UnchangedDocumentDiagnosticReport>>> relatedDocuments  {};
};

template<>
inline JSONValue to_json(RelatedUnchangedDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<UnchangedDocumentDiagnosticReport>(obj));
    set(ret, "relatedDocuments", obj.relatedDocuments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RelatedUnchangedDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RelatedUnchangedDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "relatedDocuments", target.relatedDocuments));
    return {};
}

using DocumentDiagnosticReport = std::variant<RelatedFullDocumentDiagnosticReport, RelatedUnchangedDocumentDiagnosticReport>;
struct anon_0 {
    Range range ;
    string placeholder ;
};

template<>
inline JSONValue to_json(anon_0 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "placeholder", obj.placeholder);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_0& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_0" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "placeholder", target.placeholder));
    return {};
}

struct anon_1 {
    boolean defaultBehavior { false };
};

template<>
inline JSONValue to_json(anon_1 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "defaultBehavior", obj.defaultBehavior);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_1& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_1" };

    TRY_RETURN(decode(value, "defaultBehavior", target.defaultBehavior));
    return {};
}

using PrepareRenameResult = std::variant<Range, anon_0, anon_1>;
struct anon_2 {
    string language ;
    std::optional<string> scheme  {};
    std::optional<string> pattern  {};
};

template<>
inline JSONValue to_json(anon_2 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_2& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_2" };

    TRY_RETURN(decode(value, "language", target.language));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

struct anon_3 {
    std::optional<string> language  {};
    string scheme ;
    std::optional<string> pattern  {};
};

template<>
inline JSONValue to_json(anon_3 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_3& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_3" };

    TRY_RETURN(decode(value, "language", target.language));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

struct anon_4 {
    std::optional<string> language  {};
    std::optional<string> scheme  {};
    string pattern ;
};

template<>
inline JSONValue to_json(anon_4 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_4& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_4" };

    TRY_RETURN(decode(value, "language", target.language));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

using TextDocumentFilter = std::variant<anon_2, anon_3, anon_4>;
struct anon_5 {
    string notebookType ;
    std::optional<string> scheme  {};
    std::optional<string> pattern  {};
};

template<>
inline JSONValue to_json(anon_5 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookType", obj.notebookType);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_5& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_5" };

    TRY_RETURN(decode(value, "notebookType", target.notebookType));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

struct anon_6 {
    std::optional<string> notebookType  {};
    string scheme ;
    std::optional<string> pattern  {};
};

template<>
inline JSONValue to_json(anon_6 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookType", obj.notebookType);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_6& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_6" };

    TRY_RETURN(decode(value, "notebookType", target.notebookType));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

struct anon_7 {
    std::optional<string> notebookType  {};
    std::optional<string> scheme  {};
    string pattern ;
};

template<>
inline JSONValue to_json(anon_7 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookType", obj.notebookType);
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_7& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_7" };

    TRY_RETURN(decode(value, "notebookType", target.notebookType));
    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

using NotebookDocumentFilter = std::variant<anon_5, anon_6, anon_7>;
struct NotebookCellTextDocumentFilter {
    std::variant<string, NotebookDocumentFilter> notebook  {};
    std::optional<string> language  {};
};

template<>
inline JSONValue to_json(NotebookCellTextDocumentFilter const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebook", obj.notebook);
    set(ret, "language", obj.language);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookCellTextDocumentFilter& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookCellTextDocumentFilter" };

    TRY_RETURN(decode(value, "notebook", target.notebook));
    TRY_RETURN(decode(value, "language", target.language));
    return {};
}

using DocumentFilter = std::variant<TextDocumentFilter, NotebookCellTextDocumentFilter>;
using DocumentSelector = std::vector<DocumentFilter>;
using ProgressToken = std::variant<integer, string>;
using ChangeAnnotationIdentifier = string;
struct WorkspaceFullDocumentDiagnosticReport : public FullDocumentDiagnosticReport {
    DocumentUri uri ;
    std::variant<integer, null> version  {};
};

template<>
inline JSONValue to_json(WorkspaceFullDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<FullDocumentDiagnosticReport>(obj));
    set(ret, "uri", obj.uri);
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceFullDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceFullDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "items", target.items));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct WorkspaceUnchangedDocumentDiagnosticReport : public UnchangedDocumentDiagnosticReport {
    DocumentUri uri ;
    std::variant<integer, null> version  {};
};

template<>
inline JSONValue to_json(WorkspaceUnchangedDocumentDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<UnchangedDocumentDiagnosticReport>(obj));
    set(ret, "uri", obj.uri);
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceUnchangedDocumentDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceUnchangedDocumentDiagnosticReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

using WorkspaceDocumentDiagnosticReport = std::variant<WorkspaceFullDocumentDiagnosticReport, WorkspaceUnchangedDocumentDiagnosticReport>;
struct anon_8 {
    Range range ;
    std::optional<uinteger> rangeLength  {};
    string text ;
};

template<>
inline JSONValue to_json(anon_8 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "rangeLength", obj.rangeLength);
    set(ret, "text", obj.text);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_8& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_8" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "rangeLength", target.rangeLength));
    TRY_RETURN(decode(value, "text", target.text));
    return {};
}

struct anon_9 {
    string text ;
};

template<>
inline JSONValue to_json(anon_9 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "text", obj.text);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_9& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_9" };

    TRY_RETURN(decode(value, "text", target.text));
    return {};
}

using TextDocumentContentChangeEvent = std::variant<anon_8, anon_9>;
struct anon_10 {
    string language ;
    string value ;
};

template<>
inline JSONValue to_json(anon_10 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    set(ret, "value", obj.value);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_10& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_10" };

    TRY_RETURN(decode(value, "language", target.language));
    TRY_RETURN(decode(value, "value", target.value));
    return {};
}

using MarkedString = std::variant<string, anon_10>;
using Pattern = string;
struct WorkspaceFolder {
    URI uri ;
    string name ;
};

template<>
inline JSONValue to_json(WorkspaceFolder const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "name", obj.name);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceFolder& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceFolder" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "name", target.name));
    return {};
}

struct RelativePattern {
    std::variant<WorkspaceFolder, URI> baseUri  {};
    Pattern pattern ;
};

template<>
inline JSONValue to_json(RelativePattern const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "baseUri", obj.baseUri);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RelativePattern& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RelativePattern" };

    TRY_RETURN(decode(value, "baseUri", target.baseUri));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

using GlobPattern = std::variant<Pattern, RelativePattern>;

struct TextDocumentIdentifier {
    DocumentUri uri ;
};

template<>
inline JSONValue to_json(TextDocumentIdentifier const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentIdentifier& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentIdentifier" };

    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct TextDocumentPositionParams {
    TextDocumentIdentifier textDocument ;
    Position position ;
};

template<>
inline JSONValue to_json(TextDocumentPositionParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "position", obj.position);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentPositionParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentPositionParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    return {};
}

struct WorkDoneProgressParams {
    std::optional<ProgressToken> workDoneToken  {};
};

template<>
inline JSONValue to_json(WorkDoneProgressParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workDoneToken", obj.workDoneToken);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct PartialResultParams {
    std::optional<ProgressToken> partialResultToken  {};
};

template<>
inline JSONValue to_json(PartialResultParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "partialResultToken", obj.partialResultToken);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PartialResultParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "PartialResultParams" };

    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct ImplementationParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(ImplementationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ImplementationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ImplementationParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct TextDocumentRegistrationOptions {
    std::variant<DocumentSelector, null> documentSelector  {};
};

template<>
inline JSONValue to_json(TextDocumentRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "documentSelector", obj.documentSelector);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    return {};
}

struct WorkDoneProgressOptions {
    std::optional<boolean> workDoneProgress  {};
};

template<>
inline JSONValue to_json(WorkDoneProgressOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workDoneProgress", obj.workDoneProgress);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct ImplementationOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(ImplementationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ImplementationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ImplementationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct StaticRegistrationOptions {
    std::optional<string> id  {};
};

template<>
inline JSONValue to_json(StaticRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "id", obj.id);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, StaticRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "StaticRegistrationOptions" };

    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct ImplementationRegistrationOptions : public TextDocumentRegistrationOptions, public ImplementationOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(ImplementationRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<ImplementationOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ImplementationRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ImplementationRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct TypeDefinitionParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(TypeDefinitionParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeDefinitionParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeDefinitionParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct TypeDefinitionOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(TypeDefinitionOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeDefinitionOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeDefinitionOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct TypeDefinitionRegistrationOptions : public TextDocumentRegistrationOptions, public TypeDefinitionOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(TypeDefinitionRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<TypeDefinitionOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeDefinitionRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeDefinitionRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct WorkspaceFoldersChangeEvent {
    std::vector<WorkspaceFolder> added  {};
    std::vector<WorkspaceFolder> removed  {};
};

template<>
inline JSONValue to_json(WorkspaceFoldersChangeEvent const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "added", obj.added);
    set(ret, "removed", obj.removed);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceFoldersChangeEvent& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceFoldersChangeEvent" };

    TRY_RETURN(decode(value, "added", target.added));
    TRY_RETURN(decode(value, "removed", target.removed));
    return {};
}

struct DidChangeWorkspaceFoldersParams {
    WorkspaceFoldersChangeEvent event ;
};

template<>
inline JSONValue to_json(DidChangeWorkspaceFoldersParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "event", obj.event);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeWorkspaceFoldersParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeWorkspaceFoldersParams" };

    TRY_RETURN(decode(value, "event", target.event));
    return {};
}

struct ConfigurationItem {
    std::optional<string> scopeUri  {};
    std::optional<string> section  {};
};

template<>
inline JSONValue to_json(ConfigurationItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "scopeUri", obj.scopeUri);
    set(ret, "section", obj.section);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ConfigurationItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ConfigurationItem" };

    TRY_RETURN(decode(value, "scopeUri", target.scopeUri));
    TRY_RETURN(decode(value, "section", target.section));
    return {};
}

struct ConfigurationParams {
    std::vector<ConfigurationItem> items  {};
};

template<>
inline JSONValue to_json(ConfigurationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "items", obj.items);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ConfigurationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ConfigurationParams" };

    TRY_RETURN(decode(value, "items", target.items));
    return {};
}

struct DocumentColorParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(DocumentColorParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentColorParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentColorParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct Color {
    decimal red ;
    decimal green ;
    decimal blue ;
    decimal alpha ;
};

template<>
inline JSONValue to_json(Color const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "red", obj.red);
    set(ret, "green", obj.green);
    set(ret, "blue", obj.blue);
    set(ret, "alpha", obj.alpha);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Color& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Color" };

    TRY_RETURN(decode(value, "red", target.red));
    TRY_RETURN(decode(value, "green", target.green));
    TRY_RETURN(decode(value, "blue", target.blue));
    TRY_RETURN(decode(value, "alpha", target.alpha));
    return {};
}

struct ColorInformation {
    Range range ;
    Color color ;
};

template<>
inline JSONValue to_json(ColorInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "color", obj.color);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ColorInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ColorInformation" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "color", target.color));
    return {};
}

struct DocumentColorOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DocumentColorOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentColorOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentColorOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentColorRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentColorOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(DocumentColorRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentColorOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentColorRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentColorRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct ColorPresentationParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    Color color ;
    Range range ;
};

template<>
inline JSONValue to_json(ColorPresentationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "color", obj.color);
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ColorPresentationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ColorPresentationParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "color", target.color));
    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

struct TextEdit {
    Range range ;
    string newText ;
};

template<>
inline JSONValue to_json(TextEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "newText", obj.newText);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextEdit" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "newText", target.newText));
    return {};
}

struct ColorPresentation {
    string label ;
    std::optional<TextEdit> textEdit  {};
    std::optional<std::vector<TextEdit>> additionalTextEdits  {};
};

template<>
inline JSONValue to_json(ColorPresentation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "textEdit", obj.textEdit);
    set(ret, "additionalTextEdits", obj.additionalTextEdits);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ColorPresentation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ColorPresentation" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "textEdit", target.textEdit));
    TRY_RETURN(decode(value, "additionalTextEdits", target.additionalTextEdits));
    return {};
}

struct FoldingRangeParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(FoldingRangeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRangeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FoldingRangeParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct FoldingRange {
    uinteger startLine { 0 };
    std::optional<uinteger> startCharacter  {};
    uinteger endLine { 0 };
    std::optional<uinteger> endCharacter  {};
    std::optional<FoldingRangeKind> kind  {};
    std::optional<string> collapsedText  {};
};

template<>
inline JSONValue to_json(FoldingRange const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "startLine", obj.startLine);
    set(ret, "startCharacter", obj.startCharacter);
    set(ret, "endLine", obj.endLine);
    set(ret, "endCharacter", obj.endCharacter);
    set(ret, "kind", obj.kind);
    set(ret, "collapsedText", obj.collapsedText);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRange& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FoldingRange" };

    TRY_RETURN(decode(value, "startLine", target.startLine));
    TRY_RETURN(decode(value, "startCharacter", target.startCharacter));
    TRY_RETURN(decode(value, "endLine", target.endLine));
    TRY_RETURN(decode(value, "endCharacter", target.endCharacter));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "collapsedText", target.collapsedText));
    return {};
}

struct FoldingRangeOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(FoldingRangeOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRangeOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FoldingRangeOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct FoldingRangeRegistrationOptions : public TextDocumentRegistrationOptions, public FoldingRangeOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(FoldingRangeRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<FoldingRangeOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRangeRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FoldingRangeRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct DeclarationParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(DeclarationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeclarationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeclarationParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct DeclarationOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DeclarationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeclarationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeclarationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DeclarationRegistrationOptions : public DeclarationOptions, public TextDocumentRegistrationOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(DeclarationRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<DeclarationOptions>(obj));
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeclarationRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeclarationRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct SelectionRangeParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    std::vector<Position> positions  {};
};

template<>
inline JSONValue to_json(SelectionRangeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "positions", obj.positions);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SelectionRangeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SelectionRangeParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "positions", target.positions));
    return {};
}

struct SelectionRange {
    Range range ;
};

template<>
inline JSONValue to_json(SelectionRange const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SelectionRange& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SelectionRange" };

    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

struct SelectionRangeOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(SelectionRangeOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SelectionRangeOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SelectionRangeOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct SelectionRangeRegistrationOptions : public SelectionRangeOptions, public TextDocumentRegistrationOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(SelectionRangeRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<SelectionRangeOptions>(obj));
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SelectionRangeRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SelectionRangeRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct WorkDoneProgressCreateParams {
    ProgressToken token ;
};

template<>
inline JSONValue to_json(WorkDoneProgressCreateParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "token", obj.token);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressCreateParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressCreateParams" };

    TRY_RETURN(decode(value, "token", target.token));
    return {};
}

struct WorkDoneProgressCancelParams {
    ProgressToken token ;
};

template<>
inline JSONValue to_json(WorkDoneProgressCancelParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "token", obj.token);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressCancelParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressCancelParams" };

    TRY_RETURN(decode(value, "token", target.token));
    return {};
}

struct CallHierarchyPrepareParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
};

template<>
inline JSONValue to_json(CallHierarchyPrepareParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyPrepareParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyPrepareParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct CallHierarchyItem {
    string name ;
    SymbolKind kind ;
    std::optional<std::vector<SymbolTag>> tags  {};
    std::optional<string> detail  {};
    DocumentUri uri ;
    Range range ;
    Range selectionRange ;
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(CallHierarchyItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "kind", obj.kind);
    set(ret, "tags", obj.tags);
    set(ret, "detail", obj.detail);
    set(ret, "uri", obj.uri);
    set(ret, "range", obj.range);
    set(ret, "selectionRange", obj.selectionRange);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyItem" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "detail", target.detail));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "selectionRange", target.selectionRange));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct CallHierarchyOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(CallHierarchyOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct CallHierarchyRegistrationOptions : public TextDocumentRegistrationOptions, public CallHierarchyOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(CallHierarchyRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<CallHierarchyOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct CallHierarchyIncomingCallsParams : public WorkDoneProgressParams, public PartialResultParams {
    CallHierarchyItem item ;
};

template<>
inline JSONValue to_json(CallHierarchyIncomingCallsParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "item", obj.item);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyIncomingCallsParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyIncomingCallsParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "item", target.item));
    return {};
}

struct CallHierarchyIncomingCall {
    CallHierarchyItem from ;
    std::vector<Range> fromRanges  {};
};

template<>
inline JSONValue to_json(CallHierarchyIncomingCall const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "from", obj.from);
    set(ret, "fromRanges", obj.fromRanges);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyIncomingCall& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyIncomingCall" };

    TRY_RETURN(decode(value, "from", target.from));
    TRY_RETURN(decode(value, "fromRanges", target.fromRanges));
    return {};
}

struct CallHierarchyOutgoingCallsParams : public WorkDoneProgressParams, public PartialResultParams {
    CallHierarchyItem item ;
};

template<>
inline JSONValue to_json(CallHierarchyOutgoingCallsParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "item", obj.item);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyOutgoingCallsParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyOutgoingCallsParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "item", target.item));
    return {};
}

struct CallHierarchyOutgoingCall {
    CallHierarchyItem to ;
    std::vector<Range> fromRanges  {};
};

template<>
inline JSONValue to_json(CallHierarchyOutgoingCall const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "to", obj.to);
    set(ret, "fromRanges", obj.fromRanges);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyOutgoingCall& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyOutgoingCall" };

    TRY_RETURN(decode(value, "to", target.to));
    TRY_RETURN(decode(value, "fromRanges", target.fromRanges));
    return {};
}

struct SemanticTokensParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(SemanticTokensParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct SemanticTokens {
    std::optional<string> resultId  {};
    std::vector<uinteger> data  {};
};

template<>
inline JSONValue to_json(SemanticTokens const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "resultId", obj.resultId);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokens& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokens" };

    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct SemanticTokensPartialResult {
    std::vector<uinteger> data  {};
};

template<>
inline JSONValue to_json(SemanticTokensPartialResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensPartialResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensPartialResult" };

    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct SemanticTokensLegend {
    std::vector<string> tokenTypes  {};
    std::vector<string> tokenModifiers  {};
};

template<>
inline JSONValue to_json(SemanticTokensLegend const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "tokenTypes", obj.tokenTypes);
    set(ret, "tokenModifiers", obj.tokenModifiers);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensLegend& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensLegend" };

    TRY_RETURN(decode(value, "tokenTypes", target.tokenTypes));
    TRY_RETURN(decode(value, "tokenModifiers", target.tokenModifiers));
    return {};
}

struct anon_11 {
};

template<>
inline JSONValue to_json(anon_11 const& obj)
{
    JSONValue ret = JSONValue::object();
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_11& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_11" };

    return {};
}

struct anon_12 {
    std::optional<boolean> delta  {};
};

template<>
inline JSONValue to_json(anon_12 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "delta", obj.delta);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_12& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_12" };

    TRY_RETURN(decode(value, "delta", target.delta));
    return {};
}

struct SemanticTokensOptions : public WorkDoneProgressOptions {
    SemanticTokensLegend legend ;
    std::optional<std::variant<boolean, anon_11>> range  {};
    std::optional<std::variant<boolean, anon_12>> full  {};
};

template<>
inline JSONValue to_json(SemanticTokensOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "legend", obj.legend);
    set(ret, "range", obj.range);
    set(ret, "full", obj.full);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "legend", target.legend));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "full", target.full));
    return {};
}

struct SemanticTokensRegistrationOptions : public TextDocumentRegistrationOptions, public SemanticTokensOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(SemanticTokensRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<SemanticTokensOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "legend", target.legend));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "full", target.full));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct SemanticTokensDeltaParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    string previousResultId ;
};

template<>
inline JSONValue to_json(SemanticTokensDeltaParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "previousResultId", obj.previousResultId);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensDeltaParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensDeltaParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "previousResultId", target.previousResultId));
    return {};
}

struct SemanticTokensEdit {
    uinteger start { 0 };
    uinteger deleteCount { 0 };
    std::optional<std::vector<uinteger>> data  {};
};

template<>
inline JSONValue to_json(SemanticTokensEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "start", obj.start);
    set(ret, "deleteCount", obj.deleteCount);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensEdit" };

    TRY_RETURN(decode(value, "start", target.start));
    TRY_RETURN(decode(value, "deleteCount", target.deleteCount));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct SemanticTokensDelta {
    std::optional<string> resultId  {};
    std::vector<SemanticTokensEdit> edits  {};
};

template<>
inline JSONValue to_json(SemanticTokensDelta const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "resultId", obj.resultId);
    set(ret, "edits", obj.edits);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensDelta& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensDelta" };

    TRY_RETURN(decode(value, "resultId", target.resultId));
    TRY_RETURN(decode(value, "edits", target.edits));
    return {};
}

struct SemanticTokensDeltaPartialResult {
    std::vector<SemanticTokensEdit> edits  {};
};

template<>
inline JSONValue to_json(SemanticTokensDeltaPartialResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "edits", obj.edits);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensDeltaPartialResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensDeltaPartialResult" };

    TRY_RETURN(decode(value, "edits", target.edits));
    return {};
}

struct SemanticTokensRangeParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    Range range ;
};

template<>
inline JSONValue to_json(SemanticTokensRangeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensRangeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensRangeParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

struct ShowDocumentParams {
    URI uri ;
    std::optional<boolean> external  {};
    std::optional<boolean> takeFocus  {};
    std::optional<Range> selection  {};
};

template<>
inline JSONValue to_json(ShowDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "external", obj.external);
    set(ret, "takeFocus", obj.takeFocus);
    set(ret, "selection", obj.selection);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowDocumentParams" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "external", target.external));
    TRY_RETURN(decode(value, "takeFocus", target.takeFocus));
    TRY_RETURN(decode(value, "selection", target.selection));
    return {};
}

struct ShowDocumentResult {
    boolean success { false };
};

template<>
inline JSONValue to_json(ShowDocumentResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "success", obj.success);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowDocumentResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowDocumentResult" };

    TRY_RETURN(decode(value, "success", target.success));
    return {};
}

struct LinkedEditingRangeParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
};

template<>
inline JSONValue to_json(LinkedEditingRangeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LinkedEditingRangeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LinkedEditingRangeParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct LinkedEditingRanges {
    std::vector<Range> ranges  {};
    std::optional<string> wordPattern  {};
};

template<>
inline JSONValue to_json(LinkedEditingRanges const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "ranges", obj.ranges);
    set(ret, "wordPattern", obj.wordPattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LinkedEditingRanges& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LinkedEditingRanges" };

    TRY_RETURN(decode(value, "ranges", target.ranges));
    TRY_RETURN(decode(value, "wordPattern", target.wordPattern));
    return {};
}

struct LinkedEditingRangeOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(LinkedEditingRangeOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LinkedEditingRangeOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LinkedEditingRangeOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct LinkedEditingRangeRegistrationOptions : public TextDocumentRegistrationOptions, public LinkedEditingRangeOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(LinkedEditingRangeRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<LinkedEditingRangeOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LinkedEditingRangeRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LinkedEditingRangeRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct FileCreate {
    string uri ;
};

template<>
inline JSONValue to_json(FileCreate const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileCreate& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileCreate" };

    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct CreateFilesParams {
    std::vector<FileCreate> files  {};
};

template<>
inline JSONValue to_json(CreateFilesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "files", obj.files);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CreateFilesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CreateFilesParams" };

    TRY_RETURN(decode(value, "files", target.files));
    return {};
}

struct OptionalVersionedTextDocumentIdentifier : public TextDocumentIdentifier {
    std::variant<integer, null> version  {};
};

template<>
inline JSONValue to_json(OptionalVersionedTextDocumentIdentifier const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentIdentifier>(obj));
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, OptionalVersionedTextDocumentIdentifier& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "OptionalVersionedTextDocumentIdentifier" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct AnnotatedTextEdit : public TextEdit {
    ChangeAnnotationIdentifier annotationId ;
};

template<>
inline JSONValue to_json(AnnotatedTextEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextEdit>(obj));
    set(ret, "annotationId", obj.annotationId);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, AnnotatedTextEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "AnnotatedTextEdit" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "newText", target.newText));
    TRY_RETURN(decode(value, "annotationId", target.annotationId));
    return {};
}

struct TextDocumentEdit {
    OptionalVersionedTextDocumentIdentifier textDocument ;
    std::vector<std::variant<TextEdit, AnnotatedTextEdit>> edits  {};
};

template<>
inline JSONValue to_json(TextDocumentEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "edits", obj.edits);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentEdit" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "edits", target.edits));
    return {};
}

struct ResourceOperation {
    string kind ;
    std::optional<ChangeAnnotationIdentifier> annotationId  {};
};

template<>
inline JSONValue to_json(ResourceOperation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "annotationId", obj.annotationId);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ResourceOperation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ResourceOperation" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "annotationId", target.annotationId));
    return {};
}

struct CreateFileOptions {
    std::optional<boolean> overwrite  {};
    std::optional<boolean> ignoreIfExists  {};
};

template<>
inline JSONValue to_json(CreateFileOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "overwrite", obj.overwrite);
    set(ret, "ignoreIfExists", obj.ignoreIfExists);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CreateFileOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CreateFileOptions" };

    TRY_RETURN(decode(value, "overwrite", target.overwrite));
    TRY_RETURN(decode(value, "ignoreIfExists", target.ignoreIfExists));
    return {};
}

struct CreateFile : public ResourceOperation {
    std::string kind  { "create" };
    DocumentUri uri ;
    std::optional<CreateFileOptions> options  {};
};

template<>
inline JSONValue to_json(CreateFile const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<ResourceOperation>(obj));
    set(ret, "kind", obj.kind);
    set(ret, "uri", obj.uri);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CreateFile& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CreateFile" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "annotationId", target.annotationId));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct RenameFileOptions {
    std::optional<boolean> overwrite  {};
    std::optional<boolean> ignoreIfExists  {};
};

template<>
inline JSONValue to_json(RenameFileOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "overwrite", obj.overwrite);
    set(ret, "ignoreIfExists", obj.ignoreIfExists);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameFileOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameFileOptions" };

    TRY_RETURN(decode(value, "overwrite", target.overwrite));
    TRY_RETURN(decode(value, "ignoreIfExists", target.ignoreIfExists));
    return {};
}

struct RenameFile : public ResourceOperation {
    std::string kind  { "rename" };
    DocumentUri oldUri ;
    DocumentUri newUri ;
    std::optional<RenameFileOptions> options  {};
};

template<>
inline JSONValue to_json(RenameFile const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<ResourceOperation>(obj));
    set(ret, "kind", obj.kind);
    set(ret, "oldUri", obj.oldUri);
    set(ret, "newUri", obj.newUri);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameFile& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameFile" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "annotationId", target.annotationId));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "oldUri", target.oldUri));
    TRY_RETURN(decode(value, "newUri", target.newUri));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct DeleteFileOptions {
    std::optional<boolean> recursive  {};
    std::optional<boolean> ignoreIfNotExists  {};
};

template<>
inline JSONValue to_json(DeleteFileOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "recursive", obj.recursive);
    set(ret, "ignoreIfNotExists", obj.ignoreIfNotExists);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeleteFileOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeleteFileOptions" };

    TRY_RETURN(decode(value, "recursive", target.recursive));
    TRY_RETURN(decode(value, "ignoreIfNotExists", target.ignoreIfNotExists));
    return {};
}

struct DeleteFile : public ResourceOperation {
    std::string kind  { "delete" };
    DocumentUri uri ;
    std::optional<DeleteFileOptions> options  {};
};

template<>
inline JSONValue to_json(DeleteFile const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<ResourceOperation>(obj));
    set(ret, "kind", obj.kind);
    set(ret, "uri", obj.uri);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeleteFile& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeleteFile" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "annotationId", target.annotationId));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct ChangeAnnotation {
    string label ;
    std::optional<boolean> needsConfirmation  {};
    std::optional<string> description  {};
};

template<>
inline JSONValue to_json(ChangeAnnotation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "needsConfirmation", obj.needsConfirmation);
    set(ret, "description", obj.description);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ChangeAnnotation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ChangeAnnotation" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "needsConfirmation", target.needsConfirmation));
    TRY_RETURN(decode(value, "description", target.description));
    return {};
}

struct WorkspaceEdit {
    std::optional<std::map<DocumentUri, std::vector<TextEdit>>> changes  {};
    std::optional<std::vector<std::variant<TextDocumentEdit, CreateFile, RenameFile, DeleteFile>>> documentChanges  {};
    std::optional<std::map<ChangeAnnotationIdentifier, ChangeAnnotation>> changeAnnotations  {};
};

template<>
inline JSONValue to_json(WorkspaceEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "changes", obj.changes);
    set(ret, "documentChanges", obj.documentChanges);
    set(ret, "changeAnnotations", obj.changeAnnotations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceEdit" };

    TRY_RETURN(decode(value, "changes", target.changes));
    TRY_RETURN(decode(value, "documentChanges", target.documentChanges));
    TRY_RETURN(decode(value, "changeAnnotations", target.changeAnnotations));
    return {};
}

struct FileOperationPatternOptions {
    std::optional<boolean> ignoreCase  {};
};

template<>
inline JSONValue to_json(FileOperationPatternOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "ignoreCase", obj.ignoreCase);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationPatternOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationPatternOptions" };

    TRY_RETURN(decode(value, "ignoreCase", target.ignoreCase));
    return {};
}

struct FileOperationPattern {
    string glob ;
    std::optional<FileOperationPatternKind> matches  {};
    std::optional<FileOperationPatternOptions> options  {};
};

template<>
inline JSONValue to_json(FileOperationPattern const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "glob", obj.glob);
    set(ret, "matches", obj.matches);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationPattern& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationPattern" };

    TRY_RETURN(decode(value, "glob", target.glob));
    TRY_RETURN(decode(value, "matches", target.matches));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct FileOperationFilter {
    std::optional<string> scheme  {};
    FileOperationPattern pattern ;
};

template<>
inline JSONValue to_json(FileOperationFilter const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "scheme", obj.scheme);
    set(ret, "pattern", obj.pattern);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationFilter& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationFilter" };

    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "pattern", target.pattern));
    return {};
}

struct FileOperationRegistrationOptions {
    std::vector<FileOperationFilter> filters  {};
};

template<>
inline JSONValue to_json(FileOperationRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "filters", obj.filters);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationRegistrationOptions" };

    TRY_RETURN(decode(value, "filters", target.filters));
    return {};
}

struct FileRename {
    string oldUri ;
    string newUri ;
};

template<>
inline JSONValue to_json(FileRename const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "oldUri", obj.oldUri);
    set(ret, "newUri", obj.newUri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileRename& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileRename" };

    TRY_RETURN(decode(value, "oldUri", target.oldUri));
    TRY_RETURN(decode(value, "newUri", target.newUri));
    return {};
}

struct RenameFilesParams {
    std::vector<FileRename> files  {};
};

template<>
inline JSONValue to_json(RenameFilesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "files", obj.files);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameFilesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameFilesParams" };

    TRY_RETURN(decode(value, "files", target.files));
    return {};
}

struct FileDelete {
    string uri ;
};

template<>
inline JSONValue to_json(FileDelete const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileDelete& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileDelete" };

    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct DeleteFilesParams {
    std::vector<FileDelete> files  {};
};

template<>
inline JSONValue to_json(DeleteFilesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "files", obj.files);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeleteFilesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeleteFilesParams" };

    TRY_RETURN(decode(value, "files", target.files));
    return {};
}

struct MonikerParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(MonikerParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MonikerParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MonikerParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct Moniker {
    string scheme ;
    string identifier ;
    UniquenessLevel unique ;
    std::optional<MonikerKind> kind  {};
};

template<>
inline JSONValue to_json(Moniker const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "scheme", obj.scheme);
    set(ret, "identifier", obj.identifier);
    set(ret, "unique", obj.unique);
    set(ret, "kind", obj.kind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Moniker& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Moniker" };

    TRY_RETURN(decode(value, "scheme", target.scheme));
    TRY_RETURN(decode(value, "identifier", target.identifier));
    TRY_RETURN(decode(value, "unique", target.unique));
    TRY_RETURN(decode(value, "kind", target.kind));
    return {};
}

struct MonikerOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(MonikerOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MonikerOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MonikerOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct MonikerRegistrationOptions : public TextDocumentRegistrationOptions, public MonikerOptions {
};

template<>
inline JSONValue to_json(MonikerRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<MonikerOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MonikerRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MonikerRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct TypeHierarchyPrepareParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
};

template<>
inline JSONValue to_json(TypeHierarchyPrepareParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchyPrepareParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchyPrepareParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct TypeHierarchyItem {
    string name ;
    SymbolKind kind ;
    std::optional<std::vector<SymbolTag>> tags  {};
    std::optional<string> detail  {};
    DocumentUri uri ;
    Range range ;
    Range selectionRange ;
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(TypeHierarchyItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "kind", obj.kind);
    set(ret, "tags", obj.tags);
    set(ret, "detail", obj.detail);
    set(ret, "uri", obj.uri);
    set(ret, "range", obj.range);
    set(ret, "selectionRange", obj.selectionRange);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchyItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchyItem" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "detail", target.detail));
    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "selectionRange", target.selectionRange));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct TypeHierarchyOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(TypeHierarchyOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchyOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchyOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct TypeHierarchyRegistrationOptions : public TextDocumentRegistrationOptions, public TypeHierarchyOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(TypeHierarchyRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<TypeHierarchyOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchyRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchyRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct TypeHierarchySupertypesParams : public WorkDoneProgressParams, public PartialResultParams {
    TypeHierarchyItem item ;
};

template<>
inline JSONValue to_json(TypeHierarchySupertypesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "item", obj.item);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchySupertypesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchySupertypesParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "item", target.item));
    return {};
}

struct TypeHierarchySubtypesParams : public WorkDoneProgressParams, public PartialResultParams {
    TypeHierarchyItem item ;
};

template<>
inline JSONValue to_json(TypeHierarchySubtypesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "item", obj.item);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchySubtypesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchySubtypesParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "item", target.item));
    return {};
}

struct InlineValueContext {
    integer frameId { 0 };
    Range stoppedLocation ;
};

template<>
inline JSONValue to_json(InlineValueContext const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "frameId", obj.frameId);
    set(ret, "stoppedLocation", obj.stoppedLocation);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueContext& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueContext" };

    TRY_RETURN(decode(value, "frameId", target.frameId));
    TRY_RETURN(decode(value, "stoppedLocation", target.stoppedLocation));
    return {};
}

struct InlineValueParams : public WorkDoneProgressParams {
    TextDocumentIdentifier textDocument ;
    Range range ;
    InlineValueContext context ;
};

template<>
inline JSONValue to_json(InlineValueParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "range", obj.range);
    set(ret, "context", obj.context);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "context", target.context));
    return {};
}

struct InlineValueOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(InlineValueOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct InlineValueRegistrationOptions : public InlineValueOptions, public TextDocumentRegistrationOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(InlineValueRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<InlineValueOptions>(obj));
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct InlayHintParams : public WorkDoneProgressParams {
    TextDocumentIdentifier textDocument ;
    Range range ;
};

template<>
inline JSONValue to_json(InlayHintParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

struct MarkupContent {
    MarkupKind kind ;
    string value ;
};

template<>
inline JSONValue to_json(MarkupContent const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "value", obj.value);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MarkupContent& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MarkupContent" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "value", target.value));
    return {};
}

struct Command {
    string title ;
    string command ;
    std::optional<std::vector<LSPAny>> arguments  {};
};

template<>
inline JSONValue to_json(Command const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "title", obj.title);
    set(ret, "command", obj.command);
    set(ret, "arguments", obj.arguments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Command& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Command" };

    TRY_RETURN(decode(value, "title", target.title));
    TRY_RETURN(decode(value, "command", target.command));
    TRY_RETURN(decode(value, "arguments", target.arguments));
    return {};
}

struct InlayHintLabelPart {
    string value ;
    std::optional<std::variant<string, MarkupContent>> tooltip  {};
    std::optional<Location> location  {};
    std::optional<Command> command  {};
};

template<>
inline JSONValue to_json(InlayHintLabelPart const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "value", obj.value);
    set(ret, "tooltip", obj.tooltip);
    set(ret, "location", obj.location);
    set(ret, "command", obj.command);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintLabelPart& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintLabelPart" };

    TRY_RETURN(decode(value, "value", target.value));
    TRY_RETURN(decode(value, "tooltip", target.tooltip));
    TRY_RETURN(decode(value, "location", target.location));
    TRY_RETURN(decode(value, "command", target.command));
    return {};
}

struct InlayHint {
    Position position ;
    std::variant<string, std::vector<InlayHintLabelPart>> label  {};
    std::optional<InlayHintKind> kind  {};
    std::optional<std::vector<TextEdit>> textEdits  {};
    std::optional<std::variant<string, MarkupContent>> tooltip  {};
    std::optional<boolean> paddingLeft  {};
    std::optional<boolean> paddingRight  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(InlayHint const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "position", obj.position);
    set(ret, "label", obj.label);
    set(ret, "kind", obj.kind);
    set(ret, "textEdits", obj.textEdits);
    set(ret, "tooltip", obj.tooltip);
    set(ret, "paddingLeft", obj.paddingLeft);
    set(ret, "paddingRight", obj.paddingRight);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHint& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHint" };

    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "textEdits", target.textEdits));
    TRY_RETURN(decode(value, "tooltip", target.tooltip));
    TRY_RETURN(decode(value, "paddingLeft", target.paddingLeft));
    TRY_RETURN(decode(value, "paddingRight", target.paddingRight));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct InlayHintOptions : public WorkDoneProgressOptions {
    std::optional<boolean> resolveProvider  {};
};

template<>
inline JSONValue to_json(InlayHintOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "resolveProvider", obj.resolveProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct InlayHintRegistrationOptions : public InlayHintOptions, public TextDocumentRegistrationOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(InlayHintRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<InlayHintOptions>(obj));
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct DocumentDiagnosticParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    std::optional<string> identifier  {};
    std::optional<string> previousResultId  {};
};

template<>
inline JSONValue to_json(DocumentDiagnosticParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "identifier", obj.identifier);
    set(ret, "previousResultId", obj.previousResultId);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentDiagnosticParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentDiagnosticParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "identifier", target.identifier));
    TRY_RETURN(decode(value, "previousResultId", target.previousResultId));
    return {};
}

struct DocumentDiagnosticReportPartialResult {
    std::map<DocumentUri, std::variant<FullDocumentDiagnosticReport, UnchangedDocumentDiagnosticReport>> relatedDocuments  {};
};

template<>
inline JSONValue to_json(DocumentDiagnosticReportPartialResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "relatedDocuments", obj.relatedDocuments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentDiagnosticReportPartialResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentDiagnosticReportPartialResult" };

    TRY_RETURN(decode(value, "relatedDocuments", target.relatedDocuments));
    return {};
}

struct DiagnosticServerCancellationData {
    boolean retriggerRequest { false };
};

template<>
inline JSONValue to_json(DiagnosticServerCancellationData const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "retriggerRequest", obj.retriggerRequest);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticServerCancellationData& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticServerCancellationData" };

    TRY_RETURN(decode(value, "retriggerRequest", target.retriggerRequest));
    return {};
}

struct DiagnosticOptions : public WorkDoneProgressOptions {
    std::optional<string> identifier  {};
    boolean interFileDependencies { false };
    boolean workspaceDiagnostics { false };
};

template<>
inline JSONValue to_json(DiagnosticOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "identifier", obj.identifier);
    set(ret, "interFileDependencies", obj.interFileDependencies);
    set(ret, "workspaceDiagnostics", obj.workspaceDiagnostics);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "identifier", target.identifier));
    TRY_RETURN(decode(value, "interFileDependencies", target.interFileDependencies));
    TRY_RETURN(decode(value, "workspaceDiagnostics", target.workspaceDiagnostics));
    return {};
}

struct DiagnosticRegistrationOptions : public TextDocumentRegistrationOptions, public DiagnosticOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(DiagnosticRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DiagnosticOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "identifier", target.identifier));
    TRY_RETURN(decode(value, "interFileDependencies", target.interFileDependencies));
    TRY_RETURN(decode(value, "workspaceDiagnostics", target.workspaceDiagnostics));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct PreviousResultId {
    DocumentUri uri ;
    string value ;
};

template<>
inline JSONValue to_json(PreviousResultId const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "value", obj.value);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PreviousResultId& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "PreviousResultId" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "value", target.value));
    return {};
}

struct WorkspaceDiagnosticParams : public WorkDoneProgressParams, public PartialResultParams {
    std::optional<string> identifier  {};
    std::vector<PreviousResultId> previousResultIds  {};
};

template<>
inline JSONValue to_json(WorkspaceDiagnosticParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "identifier", obj.identifier);
    set(ret, "previousResultIds", obj.previousResultIds);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceDiagnosticParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceDiagnosticParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "identifier", target.identifier));
    TRY_RETURN(decode(value, "previousResultIds", target.previousResultIds));
    return {};
}

struct WorkspaceDiagnosticReport {
    std::vector<WorkspaceDocumentDiagnosticReport> items  {};
};

template<>
inline JSONValue to_json(WorkspaceDiagnosticReport const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "items", obj.items);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceDiagnosticReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceDiagnosticReport" };

    TRY_RETURN(decode(value, "items", target.items));
    return {};
}

struct WorkspaceDiagnosticReportPartialResult {
    std::vector<WorkspaceDocumentDiagnosticReport> items  {};
};

template<>
inline JSONValue to_json(WorkspaceDiagnosticReportPartialResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "items", obj.items);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceDiagnosticReportPartialResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceDiagnosticReportPartialResult" };

    TRY_RETURN(decode(value, "items", target.items));
    return {};
}

struct ExecutionSummary {
    uinteger executionOrder { 0 };
    std::optional<boolean> success  {};
};

template<>
inline JSONValue to_json(ExecutionSummary const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "executionOrder", obj.executionOrder);
    set(ret, "success", obj.success);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ExecutionSummary& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ExecutionSummary" };

    TRY_RETURN(decode(value, "executionOrder", target.executionOrder));
    TRY_RETURN(decode(value, "success", target.success));
    return {};
}

struct NotebookCell {
    NotebookCellKind kind ;
    DocumentUri document ;
    std::optional<LSPObject> metadata  {};
    std::optional<ExecutionSummary> executionSummary  {};
};

template<>
inline JSONValue to_json(NotebookCell const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "document", obj.document);
    set(ret, "metadata", obj.metadata);
    set(ret, "executionSummary", obj.executionSummary);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookCell& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookCell" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "document", target.document));
    TRY_RETURN(decode(value, "metadata", target.metadata));
    TRY_RETURN(decode(value, "executionSummary", target.executionSummary));
    return {};
}

struct NotebookDocument {
    URI uri ;
    string notebookType ;
    integer version { 0 };
    std::optional<LSPObject> metadata  {};
    std::vector<NotebookCell> cells  {};
};

template<>
inline JSONValue to_json(NotebookDocument const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "notebookType", obj.notebookType);
    set(ret, "version", obj.version);
    set(ret, "metadata", obj.metadata);
    set(ret, "cells", obj.cells);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocument& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocument" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "notebookType", target.notebookType));
    TRY_RETURN(decode(value, "version", target.version));
    TRY_RETURN(decode(value, "metadata", target.metadata));
    TRY_RETURN(decode(value, "cells", target.cells));
    return {};
}

struct TextDocumentItem {
    DocumentUri uri ;
    string languageId ;
    integer version { 0 };
    string text ;
};

template<>
inline JSONValue to_json(TextDocumentItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "languageId", obj.languageId);
    set(ret, "version", obj.version);
    set(ret, "text", obj.text);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentItem" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "languageId", target.languageId));
    TRY_RETURN(decode(value, "version", target.version));
    TRY_RETURN(decode(value, "text", target.text));
    return {};
}

struct DidOpenNotebookDocumentParams {
    NotebookDocument notebookDocument ;
    std::vector<TextDocumentItem> cellTextDocuments  {};
};

template<>
inline JSONValue to_json(DidOpenNotebookDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookDocument", obj.notebookDocument);
    set(ret, "cellTextDocuments", obj.cellTextDocuments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidOpenNotebookDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidOpenNotebookDocumentParams" };

    TRY_RETURN(decode(value, "notebookDocument", target.notebookDocument));
    TRY_RETURN(decode(value, "cellTextDocuments", target.cellTextDocuments));
    return {};
}

struct VersionedNotebookDocumentIdentifier {
    integer version { 0 };
    URI uri ;
};

template<>
inline JSONValue to_json(VersionedNotebookDocumentIdentifier const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "version", obj.version);
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, VersionedNotebookDocumentIdentifier& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "VersionedNotebookDocumentIdentifier" };

    TRY_RETURN(decode(value, "version", target.version));
    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct NotebookCellArrayChange {
    uinteger start { 0 };
    uinteger deleteCount { 0 };
    std::optional<std::vector<NotebookCell>> cells  {};
};

template<>
inline JSONValue to_json(NotebookCellArrayChange const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "start", obj.start);
    set(ret, "deleteCount", obj.deleteCount);
    set(ret, "cells", obj.cells);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookCellArrayChange& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookCellArrayChange" };

    TRY_RETURN(decode(value, "start", target.start));
    TRY_RETURN(decode(value, "deleteCount", target.deleteCount));
    TRY_RETURN(decode(value, "cells", target.cells));
    return {};
}

struct anon_14 {
    NotebookCellArrayChange array ;
    std::optional<std::vector<TextDocumentItem>> didOpen  {};
    std::optional<std::vector<TextDocumentIdentifier>> didClose  {};
};

template<>
inline JSONValue to_json(anon_14 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "array", obj.array);
    set(ret, "didOpen", obj.didOpen);
    set(ret, "didClose", obj.didClose);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_14& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_14" };

    TRY_RETURN(decode(value, "array", target.array));
    TRY_RETURN(decode(value, "didOpen", target.didOpen));
    TRY_RETURN(decode(value, "didClose", target.didClose));
    return {};
}

struct VersionedTextDocumentIdentifier : public TextDocumentIdentifier {
    integer version { 0 };
};

template<>
inline JSONValue to_json(VersionedTextDocumentIdentifier const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentIdentifier>(obj));
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, VersionedTextDocumentIdentifier& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "VersionedTextDocumentIdentifier" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct anon_15 {
    VersionedTextDocumentIdentifier document ;
    std::vector<TextDocumentContentChangeEvent> changes  {};
};

template<>
inline JSONValue to_json(anon_15 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "document", obj.document);
    set(ret, "changes", obj.changes);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_15& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_15" };

    TRY_RETURN(decode(value, "document", target.document));
    TRY_RETURN(decode(value, "changes", target.changes));
    return {};
}

struct anon_16 {
    NotebookCellArrayChange array ;
    std::optional<std::vector<TextDocumentItem>> didOpen  {};
    std::optional<std::vector<TextDocumentIdentifier>> didClose  {};
};

template<>
inline JSONValue to_json(anon_16 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "array", obj.array);
    set(ret, "didOpen", obj.didOpen);
    set(ret, "didClose", obj.didClose);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_16& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_16" };

    TRY_RETURN(decode(value, "array", target.array));
    TRY_RETURN(decode(value, "didOpen", target.didOpen));
    TRY_RETURN(decode(value, "didClose", target.didClose));
    return {};
}

struct anon_17 {
    VersionedTextDocumentIdentifier document ;
    std::vector<TextDocumentContentChangeEvent> changes  {};
};

template<>
inline JSONValue to_json(anon_17 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "document", obj.document);
    set(ret, "changes", obj.changes);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_17& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_17" };

    TRY_RETURN(decode(value, "document", target.document));
    TRY_RETURN(decode(value, "changes", target.changes));
    return {};
}

struct anon_13 {
    std::optional<anon_16> structure  {};
    std::optional<std::vector<NotebookCell>> data  {};
    std::optional<std::vector<anon_17>> textContent  {};
};

template<>
inline JSONValue to_json(anon_13 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "structure", obj.structure);
    set(ret, "data", obj.data);
    set(ret, "textContent", obj.textContent);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_13& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_13" };

    TRY_RETURN(decode(value, "structure", target.structure));
    TRY_RETURN(decode(value, "data", target.data));
    TRY_RETURN(decode(value, "textContent", target.textContent));
    return {};
}

struct NotebookDocumentChangeEvent {
    std::optional<LSPObject> metadata  {};
    std::optional<anon_13> cells  {};
};

template<>
inline JSONValue to_json(NotebookDocumentChangeEvent const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "metadata", obj.metadata);
    set(ret, "cells", obj.cells);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentChangeEvent& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentChangeEvent" };

    TRY_RETURN(decode(value, "metadata", target.metadata));
    TRY_RETURN(decode(value, "cells", target.cells));
    return {};
}

struct DidChangeNotebookDocumentParams {
    VersionedNotebookDocumentIdentifier notebookDocument ;
    NotebookDocumentChangeEvent change ;
};

template<>
inline JSONValue to_json(DidChangeNotebookDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookDocument", obj.notebookDocument);
    set(ret, "change", obj.change);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeNotebookDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeNotebookDocumentParams" };

    TRY_RETURN(decode(value, "notebookDocument", target.notebookDocument));
    TRY_RETURN(decode(value, "change", target.change));
    return {};
}

struct NotebookDocumentIdentifier {
    URI uri ;
};

template<>
inline JSONValue to_json(NotebookDocumentIdentifier const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentIdentifier& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentIdentifier" };

    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct DidSaveNotebookDocumentParams {
    NotebookDocumentIdentifier notebookDocument ;
};

template<>
inline JSONValue to_json(DidSaveNotebookDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookDocument", obj.notebookDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidSaveNotebookDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidSaveNotebookDocumentParams" };

    TRY_RETURN(decode(value, "notebookDocument", target.notebookDocument));
    return {};
}

struct DidCloseNotebookDocumentParams {
    NotebookDocumentIdentifier notebookDocument ;
    std::vector<TextDocumentIdentifier> cellTextDocuments  {};
};

template<>
inline JSONValue to_json(DidCloseNotebookDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookDocument", obj.notebookDocument);
    set(ret, "cellTextDocuments", obj.cellTextDocuments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidCloseNotebookDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidCloseNotebookDocumentParams" };

    TRY_RETURN(decode(value, "notebookDocument", target.notebookDocument));
    TRY_RETURN(decode(value, "cellTextDocuments", target.cellTextDocuments));
    return {};
}

struct Registration {
    string id ;
    string method ;
    std::optional<LSPAny> registerOptions  {};
};

template<>
inline JSONValue to_json(Registration const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "id", obj.id);
    set(ret, "method", obj.method);
    set(ret, "registerOptions", obj.registerOptions);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Registration& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Registration" };

    TRY_RETURN(decode(value, "id", target.id));
    TRY_RETURN(decode(value, "method", target.method));
    TRY_RETURN(decode(value, "registerOptions", target.registerOptions));
    return {};
}

struct RegistrationParams {
    std::vector<Registration> registrations  {};
};

template<>
inline JSONValue to_json(RegistrationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "registrations", obj.registrations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RegistrationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RegistrationParams" };

    TRY_RETURN(decode(value, "registrations", target.registrations));
    return {};
}

struct Unregistration {
    string id ;
    string method ;
};

template<>
inline JSONValue to_json(Unregistration const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "id", obj.id);
    set(ret, "method", obj.method);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Unregistration& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Unregistration" };

    TRY_RETURN(decode(value, "id", target.id));
    TRY_RETURN(decode(value, "method", target.method));
    return {};
}

struct UnregistrationParams {
    std::vector<Unregistration> unregisterations  {};
};

template<>
inline JSONValue to_json(UnregistrationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "unregisterations", obj.unregisterations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, UnregistrationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "UnregistrationParams" };

    TRY_RETURN(decode(value, "unregisterations", target.unregisterations));
    return {};
}

struct anon_18 {
    string name ;
    std::optional<string> version  {};
};

template<>
inline JSONValue to_json(anon_18 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_18& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_18" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct anon_19 {
    std::optional<boolean> groupsOnLabel  {};
};

template<>
inline JSONValue to_json(anon_19 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "groupsOnLabel", obj.groupsOnLabel);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_19& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_19" };

    TRY_RETURN(decode(value, "groupsOnLabel", target.groupsOnLabel));
    return {};
}

struct WorkspaceEditClientCapabilities {
    std::optional<boolean> documentChanges  {};
    std::optional<std::vector<ResourceOperationKind>> resourceOperations  {};
    std::optional<FailureHandlingKind> failureHandling  {};
    std::optional<boolean> normalizesLineEndings  {};
    std::optional<anon_19> changeAnnotationSupport  {};
};

template<>
inline JSONValue to_json(WorkspaceEditClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "documentChanges", obj.documentChanges);
    set(ret, "resourceOperations", obj.resourceOperations);
    set(ret, "failureHandling", obj.failureHandling);
    set(ret, "normalizesLineEndings", obj.normalizesLineEndings);
    set(ret, "changeAnnotationSupport", obj.changeAnnotationSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceEditClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceEditClientCapabilities" };

    TRY_RETURN(decode(value, "documentChanges", target.documentChanges));
    TRY_RETURN(decode(value, "resourceOperations", target.resourceOperations));
    TRY_RETURN(decode(value, "failureHandling", target.failureHandling));
    TRY_RETURN(decode(value, "normalizesLineEndings", target.normalizesLineEndings));
    TRY_RETURN(decode(value, "changeAnnotationSupport", target.changeAnnotationSupport));
    return {};
}

struct DidChangeConfigurationClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DidChangeConfigurationClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeConfigurationClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeConfigurationClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DidChangeWatchedFilesClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> relativePatternSupport  {};
};

template<>
inline JSONValue to_json(DidChangeWatchedFilesClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "relativePatternSupport", obj.relativePatternSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeWatchedFilesClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeWatchedFilesClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "relativePatternSupport", target.relativePatternSupport));
    return {};
}

struct anon_20 {
    std::optional<std::vector<SymbolKind>> valueSet  {};
};

template<>
inline JSONValue to_json(anon_20 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_20& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_20" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_21 {
    std::vector<SymbolTag> valueSet  {};
};

template<>
inline JSONValue to_json(anon_21 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_21& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_21" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_22 {
    std::vector<string> properties  {};
};

template<>
inline JSONValue to_json(anon_22 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "properties", obj.properties);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_22& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_22" };

    TRY_RETURN(decode(value, "properties", target.properties));
    return {};
}

struct WorkspaceSymbolClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_20> symbolKind  {};
    std::optional<anon_21> tagSupport  {};
    std::optional<anon_22> resolveSupport  {};
};

template<>
inline JSONValue to_json(WorkspaceSymbolClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "symbolKind", obj.symbolKind);
    set(ret, "tagSupport", obj.tagSupport);
    set(ret, "resolveSupport", obj.resolveSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceSymbolClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceSymbolClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "symbolKind", target.symbolKind));
    TRY_RETURN(decode(value, "tagSupport", target.tagSupport));
    TRY_RETURN(decode(value, "resolveSupport", target.resolveSupport));
    return {};
}

struct ExecuteCommandClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(ExecuteCommandClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ExecuteCommandClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ExecuteCommandClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct SemanticTokensWorkspaceClientCapabilities {
    std::optional<boolean> refreshSupport  {};
};

template<>
inline JSONValue to_json(SemanticTokensWorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "refreshSupport", obj.refreshSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensWorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensWorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "refreshSupport", target.refreshSupport));
    return {};
}

struct CodeLensWorkspaceClientCapabilities {
    std::optional<boolean> refreshSupport  {};
};

template<>
inline JSONValue to_json(CodeLensWorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "refreshSupport", obj.refreshSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLensWorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLensWorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "refreshSupport", target.refreshSupport));
    return {};
}

struct FileOperationClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> didCreate  {};
    std::optional<boolean> willCreate  {};
    std::optional<boolean> didRename  {};
    std::optional<boolean> willRename  {};
    std::optional<boolean> didDelete  {};
    std::optional<boolean> willDelete  {};
};

template<>
inline JSONValue to_json(FileOperationClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "didCreate", obj.didCreate);
    set(ret, "willCreate", obj.willCreate);
    set(ret, "didRename", obj.didRename);
    set(ret, "willRename", obj.willRename);
    set(ret, "didDelete", obj.didDelete);
    set(ret, "willDelete", obj.willDelete);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "didCreate", target.didCreate));
    TRY_RETURN(decode(value, "willCreate", target.willCreate));
    TRY_RETURN(decode(value, "didRename", target.didRename));
    TRY_RETURN(decode(value, "willRename", target.willRename));
    TRY_RETURN(decode(value, "didDelete", target.didDelete));
    TRY_RETURN(decode(value, "willDelete", target.willDelete));
    return {};
}

struct InlineValueWorkspaceClientCapabilities {
    std::optional<boolean> refreshSupport  {};
};

template<>
inline JSONValue to_json(InlineValueWorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "refreshSupport", obj.refreshSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueWorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueWorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "refreshSupport", target.refreshSupport));
    return {};
}

struct InlayHintWorkspaceClientCapabilities {
    std::optional<boolean> refreshSupport  {};
};

template<>
inline JSONValue to_json(InlayHintWorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "refreshSupport", obj.refreshSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintWorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintWorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "refreshSupport", target.refreshSupport));
    return {};
}

struct DiagnosticWorkspaceClientCapabilities {
    std::optional<boolean> refreshSupport  {};
};

template<>
inline JSONValue to_json(DiagnosticWorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "refreshSupport", obj.refreshSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticWorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticWorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "refreshSupport", target.refreshSupport));
    return {};
}

struct WorkspaceClientCapabilities {
    std::optional<boolean> applyEdit  {};
    std::optional<WorkspaceEditClientCapabilities> workspaceEdit  {};
    std::optional<DidChangeConfigurationClientCapabilities> didChangeConfiguration  {};
    std::optional<DidChangeWatchedFilesClientCapabilities> didChangeWatchedFiles  {};
    std::optional<WorkspaceSymbolClientCapabilities> symbol  {};
    std::optional<ExecuteCommandClientCapabilities> executeCommand  {};
    std::optional<boolean> workspaceFolders  {};
    std::optional<boolean> configuration  {};
    std::optional<SemanticTokensWorkspaceClientCapabilities> semanticTokens  {};
    std::optional<CodeLensWorkspaceClientCapabilities> codeLens  {};
    std::optional<FileOperationClientCapabilities> fileOperations  {};
    std::optional<InlineValueWorkspaceClientCapabilities> inlineValue  {};
    std::optional<InlayHintWorkspaceClientCapabilities> inlayHint  {};
    std::optional<DiagnosticWorkspaceClientCapabilities> diagnostics  {};
};

template<>
inline JSONValue to_json(WorkspaceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "applyEdit", obj.applyEdit);
    set(ret, "workspaceEdit", obj.workspaceEdit);
    set(ret, "didChangeConfiguration", obj.didChangeConfiguration);
    set(ret, "didChangeWatchedFiles", obj.didChangeWatchedFiles);
    set(ret, "symbol", obj.symbol);
    set(ret, "executeCommand", obj.executeCommand);
    set(ret, "workspaceFolders", obj.workspaceFolders);
    set(ret, "configuration", obj.configuration);
    set(ret, "semanticTokens", obj.semanticTokens);
    set(ret, "codeLens", obj.codeLens);
    set(ret, "fileOperations", obj.fileOperations);
    set(ret, "inlineValue", obj.inlineValue);
    set(ret, "inlayHint", obj.inlayHint);
    set(ret, "diagnostics", obj.diagnostics);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceClientCapabilities" };

    TRY_RETURN(decode(value, "applyEdit", target.applyEdit));
    TRY_RETURN(decode(value, "workspaceEdit", target.workspaceEdit));
    TRY_RETURN(decode(value, "didChangeConfiguration", target.didChangeConfiguration));
    TRY_RETURN(decode(value, "didChangeWatchedFiles", target.didChangeWatchedFiles));
    TRY_RETURN(decode(value, "symbol", target.symbol));
    TRY_RETURN(decode(value, "executeCommand", target.executeCommand));
    TRY_RETURN(decode(value, "workspaceFolders", target.workspaceFolders));
    TRY_RETURN(decode(value, "configuration", target.configuration));
    TRY_RETURN(decode(value, "semanticTokens", target.semanticTokens));
    TRY_RETURN(decode(value, "codeLens", target.codeLens));
    TRY_RETURN(decode(value, "fileOperations", target.fileOperations));
    TRY_RETURN(decode(value, "inlineValue", target.inlineValue));
    TRY_RETURN(decode(value, "inlayHint", target.inlayHint));
    TRY_RETURN(decode(value, "diagnostics", target.diagnostics));
    return {};
}

struct TextDocumentSyncClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> willSave  {};
    std::optional<boolean> willSaveWaitUntil  {};
    std::optional<boolean> didSave  {};
};

template<>
inline JSONValue to_json(TextDocumentSyncClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "willSave", obj.willSave);
    set(ret, "willSaveWaitUntil", obj.willSaveWaitUntil);
    set(ret, "didSave", obj.didSave);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentSyncClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentSyncClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "willSave", target.willSave));
    TRY_RETURN(decode(value, "willSaveWaitUntil", target.willSaveWaitUntil));
    TRY_RETURN(decode(value, "didSave", target.didSave));
    return {};
}

struct anon_24 {
    std::vector<CompletionItemTag> valueSet  {};
};

template<>
inline JSONValue to_json(anon_24 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_24& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_24" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_25 {
    std::vector<string> properties  {};
};

template<>
inline JSONValue to_json(anon_25 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "properties", obj.properties);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_25& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_25" };

    TRY_RETURN(decode(value, "properties", target.properties));
    return {};
}

struct anon_26 {
    std::vector<InsertTextMode> valueSet  {};
};

template<>
inline JSONValue to_json(anon_26 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_26& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_26" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_27 {
    std::vector<CompletionItemTag> valueSet  {};
};

template<>
inline JSONValue to_json(anon_27 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_27& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_27" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_28 {
    std::vector<string> properties  {};
};

template<>
inline JSONValue to_json(anon_28 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "properties", obj.properties);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_28& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_28" };

    TRY_RETURN(decode(value, "properties", target.properties));
    return {};
}

struct anon_29 {
    std::vector<InsertTextMode> valueSet  {};
};

template<>
inline JSONValue to_json(anon_29 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_29& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_29" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_23 {
    std::optional<boolean> snippetSupport  {};
    std::optional<boolean> commitCharactersSupport  {};
    std::optional<std::vector<MarkupKind>> documentationFormat  {};
    std::optional<boolean> deprecatedSupport  {};
    std::optional<boolean> preselectSupport  {};
    std::optional<anon_27> tagSupport  {};
    std::optional<boolean> insertReplaceSupport  {};
    std::optional<anon_28> resolveSupport  {};
    std::optional<anon_29> insertTextModeSupport  {};
    std::optional<boolean> labelDetailsSupport  {};
};

template<>
inline JSONValue to_json(anon_23 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "snippetSupport", obj.snippetSupport);
    set(ret, "commitCharactersSupport", obj.commitCharactersSupport);
    set(ret, "documentationFormat", obj.documentationFormat);
    set(ret, "deprecatedSupport", obj.deprecatedSupport);
    set(ret, "preselectSupport", obj.preselectSupport);
    set(ret, "tagSupport", obj.tagSupport);
    set(ret, "insertReplaceSupport", obj.insertReplaceSupport);
    set(ret, "resolveSupport", obj.resolveSupport);
    set(ret, "insertTextModeSupport", obj.insertTextModeSupport);
    set(ret, "labelDetailsSupport", obj.labelDetailsSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_23& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_23" };

    TRY_RETURN(decode(value, "snippetSupport", target.snippetSupport));
    TRY_RETURN(decode(value, "commitCharactersSupport", target.commitCharactersSupport));
    TRY_RETURN(decode(value, "documentationFormat", target.documentationFormat));
    TRY_RETURN(decode(value, "deprecatedSupport", target.deprecatedSupport));
    TRY_RETURN(decode(value, "preselectSupport", target.preselectSupport));
    TRY_RETURN(decode(value, "tagSupport", target.tagSupport));
    TRY_RETURN(decode(value, "insertReplaceSupport", target.insertReplaceSupport));
    TRY_RETURN(decode(value, "resolveSupport", target.resolveSupport));
    TRY_RETURN(decode(value, "insertTextModeSupport", target.insertTextModeSupport));
    TRY_RETURN(decode(value, "labelDetailsSupport", target.labelDetailsSupport));
    return {};
}

struct anon_30 {
    std::optional<std::vector<CompletionItemKind>> valueSet  {};
};

template<>
inline JSONValue to_json(anon_30 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_30& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_30" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_31 {
    std::optional<std::vector<string>> itemDefaults  {};
};

template<>
inline JSONValue to_json(anon_31 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "itemDefaults", obj.itemDefaults);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_31& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_31" };

    TRY_RETURN(decode(value, "itemDefaults", target.itemDefaults));
    return {};
}

struct CompletionClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_23> completionItem  {};
    std::optional<anon_30> completionItemKind  {};
    std::optional<InsertTextMode> insertTextMode  {};
    std::optional<boolean> contextSupport  {};
    std::optional<anon_31> completionList  {};
};

template<>
inline JSONValue to_json(CompletionClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "completionItem", obj.completionItem);
    set(ret, "completionItemKind", obj.completionItemKind);
    set(ret, "insertTextMode", obj.insertTextMode);
    set(ret, "contextSupport", obj.contextSupport);
    set(ret, "completionList", obj.completionList);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "completionItem", target.completionItem));
    TRY_RETURN(decode(value, "completionItemKind", target.completionItemKind));
    TRY_RETURN(decode(value, "insertTextMode", target.insertTextMode));
    TRY_RETURN(decode(value, "contextSupport", target.contextSupport));
    TRY_RETURN(decode(value, "completionList", target.completionList));
    return {};
}

struct HoverClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<std::vector<MarkupKind>> contentFormat  {};
};

template<>
inline JSONValue to_json(HoverClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "contentFormat", obj.contentFormat);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, HoverClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "HoverClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "contentFormat", target.contentFormat));
    return {};
}

struct anon_33 {
    std::optional<boolean> labelOffsetSupport  {};
};

template<>
inline JSONValue to_json(anon_33 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "labelOffsetSupport", obj.labelOffsetSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_33& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_33" };

    TRY_RETURN(decode(value, "labelOffsetSupport", target.labelOffsetSupport));
    return {};
}

struct anon_34 {
    std::optional<boolean> labelOffsetSupport  {};
};

template<>
inline JSONValue to_json(anon_34 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "labelOffsetSupport", obj.labelOffsetSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_34& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_34" };

    TRY_RETURN(decode(value, "labelOffsetSupport", target.labelOffsetSupport));
    return {};
}

struct anon_32 {
    std::optional<std::vector<MarkupKind>> documentationFormat  {};
    std::optional<anon_34> parameterInformation  {};
    std::optional<boolean> activeParameterSupport  {};
};

template<>
inline JSONValue to_json(anon_32 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "documentationFormat", obj.documentationFormat);
    set(ret, "parameterInformation", obj.parameterInformation);
    set(ret, "activeParameterSupport", obj.activeParameterSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_32& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_32" };

    TRY_RETURN(decode(value, "documentationFormat", target.documentationFormat));
    TRY_RETURN(decode(value, "parameterInformation", target.parameterInformation));
    TRY_RETURN(decode(value, "activeParameterSupport", target.activeParameterSupport));
    return {};
}

struct SignatureHelpClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_32> signatureInformation  {};
    std::optional<boolean> contextSupport  {};
};

template<>
inline JSONValue to_json(SignatureHelpClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "signatureInformation", obj.signatureInformation);
    set(ret, "contextSupport", obj.contextSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelpClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "signatureInformation", target.signatureInformation));
    TRY_RETURN(decode(value, "contextSupport", target.contextSupport));
    return {};
}

struct DeclarationClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> linkSupport  {};
};

template<>
inline JSONValue to_json(DeclarationClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "linkSupport", obj.linkSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DeclarationClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DeclarationClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "linkSupport", target.linkSupport));
    return {};
}

struct DefinitionClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> linkSupport  {};
};

template<>
inline JSONValue to_json(DefinitionClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "linkSupport", obj.linkSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DefinitionClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DefinitionClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "linkSupport", target.linkSupport));
    return {};
}

struct TypeDefinitionClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> linkSupport  {};
};

template<>
inline JSONValue to_json(TypeDefinitionClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "linkSupport", obj.linkSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeDefinitionClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeDefinitionClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "linkSupport", target.linkSupport));
    return {};
}

struct ImplementationClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> linkSupport  {};
};

template<>
inline JSONValue to_json(ImplementationClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "linkSupport", obj.linkSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ImplementationClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ImplementationClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "linkSupport", target.linkSupport));
    return {};
}

struct ReferenceClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(ReferenceClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ReferenceClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ReferenceClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DocumentHighlightClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DocumentHighlightClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlightClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentHighlightClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct anon_35 {
    std::optional<std::vector<SymbolKind>> valueSet  {};
};

template<>
inline JSONValue to_json(anon_35 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_35& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_35" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_36 {
    std::vector<SymbolTag> valueSet  {};
};

template<>
inline JSONValue to_json(anon_36 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_36& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_36" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct DocumentSymbolClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_35> symbolKind  {};
    std::optional<boolean> hierarchicalDocumentSymbolSupport  {};
    std::optional<anon_36> tagSupport  {};
    std::optional<boolean> labelSupport  {};
};

template<>
inline JSONValue to_json(DocumentSymbolClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "symbolKind", obj.symbolKind);
    set(ret, "hierarchicalDocumentSymbolSupport", obj.hierarchicalDocumentSymbolSupport);
    set(ret, "tagSupport", obj.tagSupport);
    set(ret, "labelSupport", obj.labelSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentSymbolClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentSymbolClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "symbolKind", target.symbolKind));
    TRY_RETURN(decode(value, "hierarchicalDocumentSymbolSupport", target.hierarchicalDocumentSymbolSupport));
    TRY_RETURN(decode(value, "tagSupport", target.tagSupport));
    TRY_RETURN(decode(value, "labelSupport", target.labelSupport));
    return {};
}

struct anon_38 {
    std::vector<CodeActionKind> valueSet  {};
};

template<>
inline JSONValue to_json(anon_38 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_38& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_38" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_39 {
    std::vector<CodeActionKind> valueSet  {};
};

template<>
inline JSONValue to_json(anon_39 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_39& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_39" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_37 {
    anon_39 codeActionKind ;
};

template<>
inline JSONValue to_json(anon_37 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "codeActionKind", obj.codeActionKind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_37& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_37" };

    TRY_RETURN(decode(value, "codeActionKind", target.codeActionKind));
    return {};
}

struct anon_40 {
    std::vector<string> properties  {};
};

template<>
inline JSONValue to_json(anon_40 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "properties", obj.properties);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_40& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_40" };

    TRY_RETURN(decode(value, "properties", target.properties));
    return {};
}

struct CodeActionClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_37> codeActionLiteralSupport  {};
    std::optional<boolean> isPreferredSupport  {};
    std::optional<boolean> disabledSupport  {};
    std::optional<boolean> dataSupport  {};
    std::optional<anon_40> resolveSupport  {};
    std::optional<boolean> honorsChangeAnnotations  {};
};

template<>
inline JSONValue to_json(CodeActionClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "codeActionLiteralSupport", obj.codeActionLiteralSupport);
    set(ret, "isPreferredSupport", obj.isPreferredSupport);
    set(ret, "disabledSupport", obj.disabledSupport);
    set(ret, "dataSupport", obj.dataSupport);
    set(ret, "resolveSupport", obj.resolveSupport);
    set(ret, "honorsChangeAnnotations", obj.honorsChangeAnnotations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeActionClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "codeActionLiteralSupport", target.codeActionLiteralSupport));
    TRY_RETURN(decode(value, "isPreferredSupport", target.isPreferredSupport));
    TRY_RETURN(decode(value, "disabledSupport", target.disabledSupport));
    TRY_RETURN(decode(value, "dataSupport", target.dataSupport));
    TRY_RETURN(decode(value, "resolveSupport", target.resolveSupport));
    TRY_RETURN(decode(value, "honorsChangeAnnotations", target.honorsChangeAnnotations));
    return {};
}

struct CodeLensClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(CodeLensClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLensClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLensClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DocumentLinkClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> tooltipSupport  {};
};

template<>
inline JSONValue to_json(DocumentLinkClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "tooltipSupport", obj.tooltipSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentLinkClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentLinkClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "tooltipSupport", target.tooltipSupport));
    return {};
}

struct DocumentColorClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DocumentColorClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentColorClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentColorClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DocumentFormattingClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DocumentFormattingClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentFormattingClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentFormattingClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DocumentRangeFormattingClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DocumentRangeFormattingClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentRangeFormattingClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentRangeFormattingClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct DocumentOnTypeFormattingClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(DocumentOnTypeFormattingClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentOnTypeFormattingClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentOnTypeFormattingClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct RenameClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> prepareSupport  {};
    std::optional<PrepareSupportDefaultBehavior> prepareSupportDefaultBehavior  {};
    std::optional<boolean> honorsChangeAnnotations  {};
};

template<>
inline JSONValue to_json(RenameClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "prepareSupport", obj.prepareSupport);
    set(ret, "prepareSupportDefaultBehavior", obj.prepareSupportDefaultBehavior);
    set(ret, "honorsChangeAnnotations", obj.honorsChangeAnnotations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "prepareSupport", target.prepareSupport));
    TRY_RETURN(decode(value, "prepareSupportDefaultBehavior", target.prepareSupportDefaultBehavior));
    TRY_RETURN(decode(value, "honorsChangeAnnotations", target.honorsChangeAnnotations));
    return {};
}

struct anon_41 {
    std::optional<std::vector<FoldingRangeKind>> valueSet  {};
};

template<>
inline JSONValue to_json(anon_41 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_41& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_41" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct anon_42 {
    std::optional<boolean> collapsedText  {};
};

template<>
inline JSONValue to_json(anon_42 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "collapsedText", obj.collapsedText);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_42& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_42" };

    TRY_RETURN(decode(value, "collapsedText", target.collapsedText));
    return {};
}

struct FoldingRangeClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<uinteger> rangeLimit  {};
    std::optional<boolean> lineFoldingOnly  {};
    std::optional<anon_41> foldingRangeKind  {};
    std::optional<anon_42> foldingRange  {};
};

template<>
inline JSONValue to_json(FoldingRangeClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "rangeLimit", obj.rangeLimit);
    set(ret, "lineFoldingOnly", obj.lineFoldingOnly);
    set(ret, "foldingRangeKind", obj.foldingRangeKind);
    set(ret, "foldingRange", obj.foldingRange);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FoldingRangeClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FoldingRangeClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "rangeLimit", target.rangeLimit));
    TRY_RETURN(decode(value, "lineFoldingOnly", target.lineFoldingOnly));
    TRY_RETURN(decode(value, "foldingRangeKind", target.foldingRangeKind));
    TRY_RETURN(decode(value, "foldingRange", target.foldingRange));
    return {};
}

struct SelectionRangeClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(SelectionRangeClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SelectionRangeClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SelectionRangeClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct anon_43 {
    std::vector<DiagnosticTag> valueSet  {};
};

template<>
inline JSONValue to_json(anon_43 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "valueSet", obj.valueSet);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_43& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_43" };

    TRY_RETURN(decode(value, "valueSet", target.valueSet));
    return {};
}

struct PublishDiagnosticsClientCapabilities {
    std::optional<boolean> relatedInformation  {};
    std::optional<anon_43> tagSupport  {};
    std::optional<boolean> versionSupport  {};
    std::optional<boolean> codeDescriptionSupport  {};
    std::optional<boolean> dataSupport  {};
};

template<>
inline JSONValue to_json(PublishDiagnosticsClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "relatedInformation", obj.relatedInformation);
    set(ret, "tagSupport", obj.tagSupport);
    set(ret, "versionSupport", obj.versionSupport);
    set(ret, "codeDescriptionSupport", obj.codeDescriptionSupport);
    set(ret, "dataSupport", obj.dataSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PublishDiagnosticsClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "PublishDiagnosticsClientCapabilities" };

    TRY_RETURN(decode(value, "relatedInformation", target.relatedInformation));
    TRY_RETURN(decode(value, "tagSupport", target.tagSupport));
    TRY_RETURN(decode(value, "versionSupport", target.versionSupport));
    TRY_RETURN(decode(value, "codeDescriptionSupport", target.codeDescriptionSupport));
    TRY_RETURN(decode(value, "dataSupport", target.dataSupport));
    return {};
}

struct CallHierarchyClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(CallHierarchyClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CallHierarchyClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CallHierarchyClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct anon_45 {
};

template<>
inline JSONValue to_json(anon_45 const& obj)
{
    JSONValue ret = JSONValue::object();
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_45& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_45" };

    return {};
}

struct anon_46 {
    std::optional<boolean> delta  {};
};

template<>
inline JSONValue to_json(anon_46 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "delta", obj.delta);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_46& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_46" };

    TRY_RETURN(decode(value, "delta", target.delta));
    return {};
}

struct anon_47 {
};

template<>
inline JSONValue to_json(anon_47 const& obj)
{
    JSONValue ret = JSONValue::object();
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_47& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_47" };

    return {};
}

struct anon_48 {
    std::optional<boolean> delta  {};
};

template<>
inline JSONValue to_json(anon_48 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "delta", obj.delta);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_48& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_48" };

    TRY_RETURN(decode(value, "delta", target.delta));
    return {};
}

struct anon_44 {
    std::optional<std::variant<boolean, anon_47>> range  {};
    std::optional<std::variant<boolean, anon_48>> full  {};
};

template<>
inline JSONValue to_json(anon_44 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "full", obj.full);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_44& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_44" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "full", target.full));
    return {};
}

struct SemanticTokensClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    anon_44 requests ;
    std::vector<string> tokenTypes  {};
    std::vector<string> tokenModifiers  {};
    std::vector<TokenFormat> formats  {};
    std::optional<boolean> overlappingTokenSupport  {};
    std::optional<boolean> multilineTokenSupport  {};
    std::optional<boolean> serverCancelSupport  {};
    std::optional<boolean> augmentsSyntaxTokens  {};
};

template<>
inline JSONValue to_json(SemanticTokensClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "requests", obj.requests);
    set(ret, "tokenTypes", obj.tokenTypes);
    set(ret, "tokenModifiers", obj.tokenModifiers);
    set(ret, "formats", obj.formats);
    set(ret, "overlappingTokenSupport", obj.overlappingTokenSupport);
    set(ret, "multilineTokenSupport", obj.multilineTokenSupport);
    set(ret, "serverCancelSupport", obj.serverCancelSupport);
    set(ret, "augmentsSyntaxTokens", obj.augmentsSyntaxTokens);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SemanticTokensClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SemanticTokensClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "requests", target.requests));
    TRY_RETURN(decode(value, "tokenTypes", target.tokenTypes));
    TRY_RETURN(decode(value, "tokenModifiers", target.tokenModifiers));
    TRY_RETURN(decode(value, "formats", target.formats));
    TRY_RETURN(decode(value, "overlappingTokenSupport", target.overlappingTokenSupport));
    TRY_RETURN(decode(value, "multilineTokenSupport", target.multilineTokenSupport));
    TRY_RETURN(decode(value, "serverCancelSupport", target.serverCancelSupport));
    TRY_RETURN(decode(value, "augmentsSyntaxTokens", target.augmentsSyntaxTokens));
    return {};
}

struct LinkedEditingRangeClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(LinkedEditingRangeClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LinkedEditingRangeClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LinkedEditingRangeClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct MonikerClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(MonikerClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MonikerClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MonikerClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct TypeHierarchyClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(TypeHierarchyClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TypeHierarchyClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TypeHierarchyClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct InlineValueClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
};

template<>
inline JSONValue to_json(InlineValueClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlineValueClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlineValueClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    return {};
}

struct anon_49 {
    std::vector<string> properties  {};
};

template<>
inline JSONValue to_json(anon_49 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "properties", obj.properties);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_49& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_49" };

    TRY_RETURN(decode(value, "properties", target.properties));
    return {};
}

struct InlayHintClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<anon_49> resolveSupport  {};
};

template<>
inline JSONValue to_json(InlayHintClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "resolveSupport", obj.resolveSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InlayHintClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InlayHintClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "resolveSupport", target.resolveSupport));
    return {};
}

struct DiagnosticClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> relatedDocumentSupport  {};
};

template<>
inline JSONValue to_json(DiagnosticClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "relatedDocumentSupport", obj.relatedDocumentSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DiagnosticClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DiagnosticClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "relatedDocumentSupport", target.relatedDocumentSupport));
    return {};
}

struct TextDocumentClientCapabilities {
    std::optional<TextDocumentSyncClientCapabilities> synchronization  {};
    std::optional<CompletionClientCapabilities> completion  {};
    std::optional<HoverClientCapabilities> hover  {};
    std::optional<SignatureHelpClientCapabilities> signatureHelp  {};
    std::optional<DeclarationClientCapabilities> declaration  {};
    std::optional<DefinitionClientCapabilities> definition  {};
    std::optional<TypeDefinitionClientCapabilities> typeDefinition  {};
    std::optional<ImplementationClientCapabilities> implementation  {};
    std::optional<ReferenceClientCapabilities> references  {};
    std::optional<DocumentHighlightClientCapabilities> documentHighlight  {};
    std::optional<DocumentSymbolClientCapabilities> documentSymbol  {};
    std::optional<CodeActionClientCapabilities> codeAction  {};
    std::optional<CodeLensClientCapabilities> codeLens  {};
    std::optional<DocumentLinkClientCapabilities> documentLink  {};
    std::optional<DocumentColorClientCapabilities> colorProvider  {};
    std::optional<DocumentFormattingClientCapabilities> formatting  {};
    std::optional<DocumentRangeFormattingClientCapabilities> rangeFormatting  {};
    std::optional<DocumentOnTypeFormattingClientCapabilities> onTypeFormatting  {};
    std::optional<RenameClientCapabilities> rename  {};
    std::optional<FoldingRangeClientCapabilities> foldingRange  {};
    std::optional<SelectionRangeClientCapabilities> selectionRange  {};
    std::optional<PublishDiagnosticsClientCapabilities> publishDiagnostics  {};
    std::optional<CallHierarchyClientCapabilities> callHierarchy  {};
    std::optional<SemanticTokensClientCapabilities> semanticTokens  {};
    std::optional<LinkedEditingRangeClientCapabilities> linkedEditingRange  {};
    std::optional<MonikerClientCapabilities> moniker  {};
    std::optional<TypeHierarchyClientCapabilities> typeHierarchy  {};
    std::optional<InlineValueClientCapabilities> inlineValue  {};
    std::optional<InlayHintClientCapabilities> inlayHint  {};
    std::optional<DiagnosticClientCapabilities> diagnostic  {};
};

template<>
inline JSONValue to_json(TextDocumentClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "synchronization", obj.synchronization);
    set(ret, "completion", obj.completion);
    set(ret, "hover", obj.hover);
    set(ret, "signatureHelp", obj.signatureHelp);
    set(ret, "declaration", obj.declaration);
    set(ret, "definition", obj.definition);
    set(ret, "typeDefinition", obj.typeDefinition);
    set(ret, "implementation", obj.implementation);
    set(ret, "references", obj.references);
    set(ret, "documentHighlight", obj.documentHighlight);
    set(ret, "documentSymbol", obj.documentSymbol);
    set(ret, "codeAction", obj.codeAction);
    set(ret, "codeLens", obj.codeLens);
    set(ret, "documentLink", obj.documentLink);
    set(ret, "colorProvider", obj.colorProvider);
    set(ret, "formatting", obj.formatting);
    set(ret, "rangeFormatting", obj.rangeFormatting);
    set(ret, "onTypeFormatting", obj.onTypeFormatting);
    set(ret, "rename", obj.rename);
    set(ret, "foldingRange", obj.foldingRange);
    set(ret, "selectionRange", obj.selectionRange);
    set(ret, "publishDiagnostics", obj.publishDiagnostics);
    set(ret, "callHierarchy", obj.callHierarchy);
    set(ret, "semanticTokens", obj.semanticTokens);
    set(ret, "linkedEditingRange", obj.linkedEditingRange);
    set(ret, "moniker", obj.moniker);
    set(ret, "typeHierarchy", obj.typeHierarchy);
    set(ret, "inlineValue", obj.inlineValue);
    set(ret, "inlayHint", obj.inlayHint);
    set(ret, "diagnostic", obj.diagnostic);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentClientCapabilities" };

    TRY_RETURN(decode(value, "synchronization", target.synchronization));
    TRY_RETURN(decode(value, "completion", target.completion));
    TRY_RETURN(decode(value, "hover", target.hover));
    TRY_RETURN(decode(value, "signatureHelp", target.signatureHelp));
    TRY_RETURN(decode(value, "declaration", target.declaration));
    TRY_RETURN(decode(value, "definition", target.definition));
    TRY_RETURN(decode(value, "typeDefinition", target.typeDefinition));
    TRY_RETURN(decode(value, "implementation", target.implementation));
    TRY_RETURN(decode(value, "references", target.references));
    TRY_RETURN(decode(value, "documentHighlight", target.documentHighlight));
    TRY_RETURN(decode(value, "documentSymbol", target.documentSymbol));
    TRY_RETURN(decode(value, "codeAction", target.codeAction));
    TRY_RETURN(decode(value, "codeLens", target.codeLens));
    TRY_RETURN(decode(value, "documentLink", target.documentLink));
    TRY_RETURN(decode(value, "colorProvider", target.colorProvider));
    TRY_RETURN(decode(value, "formatting", target.formatting));
    TRY_RETURN(decode(value, "rangeFormatting", target.rangeFormatting));
    TRY_RETURN(decode(value, "onTypeFormatting", target.onTypeFormatting));
    TRY_RETURN(decode(value, "rename", target.rename));
    TRY_RETURN(decode(value, "foldingRange", target.foldingRange));
    TRY_RETURN(decode(value, "selectionRange", target.selectionRange));
    TRY_RETURN(decode(value, "publishDiagnostics", target.publishDiagnostics));
    TRY_RETURN(decode(value, "callHierarchy", target.callHierarchy));
    TRY_RETURN(decode(value, "semanticTokens", target.semanticTokens));
    TRY_RETURN(decode(value, "linkedEditingRange", target.linkedEditingRange));
    TRY_RETURN(decode(value, "moniker", target.moniker));
    TRY_RETURN(decode(value, "typeHierarchy", target.typeHierarchy));
    TRY_RETURN(decode(value, "inlineValue", target.inlineValue));
    TRY_RETURN(decode(value, "inlayHint", target.inlayHint));
    TRY_RETURN(decode(value, "diagnostic", target.diagnostic));
    return {};
}

struct NotebookDocumentSyncClientCapabilities {
    std::optional<boolean> dynamicRegistration  {};
    std::optional<boolean> executionSummarySupport  {};
};

template<>
inline JSONValue to_json(NotebookDocumentSyncClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "dynamicRegistration", obj.dynamicRegistration);
    set(ret, "executionSummarySupport", obj.executionSummarySupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentSyncClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentSyncClientCapabilities" };

    TRY_RETURN(decode(value, "dynamicRegistration", target.dynamicRegistration));
    TRY_RETURN(decode(value, "executionSummarySupport", target.executionSummarySupport));
    return {};
}

struct NotebookDocumentClientCapabilities {
    NotebookDocumentSyncClientCapabilities synchronization ;
};

template<>
inline JSONValue to_json(NotebookDocumentClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "synchronization", obj.synchronization);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentClientCapabilities" };

    TRY_RETURN(decode(value, "synchronization", target.synchronization));
    return {};
}

struct anon_50 {
    std::optional<boolean> additionalPropertiesSupport  {};
};

template<>
inline JSONValue to_json(anon_50 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "additionalPropertiesSupport", obj.additionalPropertiesSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_50& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_50" };

    TRY_RETURN(decode(value, "additionalPropertiesSupport", target.additionalPropertiesSupport));
    return {};
}

struct ShowMessageRequestClientCapabilities {
    std::optional<anon_50> messageActionItem  {};
};

template<>
inline JSONValue to_json(ShowMessageRequestClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "messageActionItem", obj.messageActionItem);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowMessageRequestClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowMessageRequestClientCapabilities" };

    TRY_RETURN(decode(value, "messageActionItem", target.messageActionItem));
    return {};
}

struct ShowDocumentClientCapabilities {
    boolean support { false };
};

template<>
inline JSONValue to_json(ShowDocumentClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "support", obj.support);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowDocumentClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowDocumentClientCapabilities" };

    TRY_RETURN(decode(value, "support", target.support));
    return {};
}

struct WindowClientCapabilities {
    std::optional<boolean> workDoneProgress  {};
    std::optional<ShowMessageRequestClientCapabilities> showMessage  {};
    std::optional<ShowDocumentClientCapabilities> showDocument  {};
};

template<>
inline JSONValue to_json(WindowClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workDoneProgress", obj.workDoneProgress);
    set(ret, "showMessage", obj.showMessage);
    set(ret, "showDocument", obj.showDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WindowClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WindowClientCapabilities" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "showMessage", target.showMessage));
    TRY_RETURN(decode(value, "showDocument", target.showDocument));
    return {};
}

struct anon_51 {
    boolean cancel { false };
    std::vector<string> retryOnContentModified  {};
};

template<>
inline JSONValue to_json(anon_51 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "cancel", obj.cancel);
    set(ret, "retryOnContentModified", obj.retryOnContentModified);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_51& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_51" };

    TRY_RETURN(decode(value, "cancel", target.cancel));
    TRY_RETURN(decode(value, "retryOnContentModified", target.retryOnContentModified));
    return {};
}

struct RegularExpressionsClientCapabilities {
    string engine ;
    std::optional<string> version  {};
};

template<>
inline JSONValue to_json(RegularExpressionsClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "engine", obj.engine);
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RegularExpressionsClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RegularExpressionsClientCapabilities" };

    TRY_RETURN(decode(value, "engine", target.engine));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct MarkdownClientCapabilities {
    string parser ;
    std::optional<string> version  {};
    std::optional<std::vector<string>> allowedTags  {};
};

template<>
inline JSONValue to_json(MarkdownClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "parser", obj.parser);
    set(ret, "version", obj.version);
    set(ret, "allowedTags", obj.allowedTags);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MarkdownClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MarkdownClientCapabilities" };

    TRY_RETURN(decode(value, "parser", target.parser));
    TRY_RETURN(decode(value, "version", target.version));
    TRY_RETURN(decode(value, "allowedTags", target.allowedTags));
    return {};
}

struct GeneralClientCapabilities {
    std::optional<anon_51> staleRequestSupport  {};
    std::optional<RegularExpressionsClientCapabilities> regularExpressions  {};
    std::optional<MarkdownClientCapabilities> markdown  {};
    std::optional<std::vector<PositionEncodingKind>> positionEncodings  {};
};

template<>
inline JSONValue to_json(GeneralClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "staleRequestSupport", obj.staleRequestSupport);
    set(ret, "regularExpressions", obj.regularExpressions);
    set(ret, "markdown", obj.markdown);
    set(ret, "positionEncodings", obj.positionEncodings);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, GeneralClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "GeneralClientCapabilities" };

    TRY_RETURN(decode(value, "staleRequestSupport", target.staleRequestSupport));
    TRY_RETURN(decode(value, "regularExpressions", target.regularExpressions));
    TRY_RETURN(decode(value, "markdown", target.markdown));
    TRY_RETURN(decode(value, "positionEncodings", target.positionEncodings));
    return {};
}

struct ClientCapabilities {
    std::optional<WorkspaceClientCapabilities> workspace  {};
    std::optional<TextDocumentClientCapabilities> textDocument  {};
    std::optional<NotebookDocumentClientCapabilities> notebookDocument  {};
    std::optional<WindowClientCapabilities> window  {};
    std::optional<GeneralClientCapabilities> general  {};
    std::optional<LSPAny> experimental  {};
};

template<>
inline JSONValue to_json(ClientCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workspace", obj.workspace);
    set(ret, "textDocument", obj.textDocument);
    set(ret, "notebookDocument", obj.notebookDocument);
    set(ret, "window", obj.window);
    set(ret, "general", obj.general);
    set(ret, "experimental", obj.experimental);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ClientCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ClientCapabilities" };

    TRY_RETURN(decode(value, "workspace", target.workspace));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "notebookDocument", target.notebookDocument));
    TRY_RETURN(decode(value, "window", target.window));
    TRY_RETURN(decode(value, "general", target.general));
    TRY_RETURN(decode(value, "experimental", target.experimental));
    return {};
}

struct _InitializeParams : public WorkDoneProgressParams {
    std::variant<integer, null> processId  {};
    std::optional<anon_18> clientInfo  {};
    std::optional<string> locale  {};
    std::optional<std::variant<string, null>> rootPath  {};
    std::variant<DocumentUri, null> rootUri  {};
    ClientCapabilities capabilities ;
    std::optional<LSPAny> initializationOptions  {};
    std::optional<TraceValues> trace  {};
};

template<>
inline JSONValue to_json(_InitializeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "processId", obj.processId);
    set(ret, "clientInfo", obj.clientInfo);
    set(ret, "locale", obj.locale);
    set(ret, "rootPath", obj.rootPath);
    set(ret, "rootUri", obj.rootUri);
    set(ret, "capabilities", obj.capabilities);
    set(ret, "initializationOptions", obj.initializationOptions);
    set(ret, "trace", obj.trace);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, _InitializeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "_InitializeParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "processId", target.processId));
    TRY_RETURN(decode(value, "clientInfo", target.clientInfo));
    TRY_RETURN(decode(value, "locale", target.locale));
    TRY_RETURN(decode(value, "rootPath", target.rootPath));
    TRY_RETURN(decode(value, "rootUri", target.rootUri));
    TRY_RETURN(decode(value, "capabilities", target.capabilities));
    TRY_RETURN(decode(value, "initializationOptions", target.initializationOptions));
    TRY_RETURN(decode(value, "trace", target.trace));
    return {};
}

struct WorkspaceFoldersInitializeParams {
    std::optional<std::variant<std::vector<WorkspaceFolder>, null>> workspaceFolders  {};
};

template<>
inline JSONValue to_json(WorkspaceFoldersInitializeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workspaceFolders", obj.workspaceFolders);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceFoldersInitializeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceFoldersInitializeParams" };

    TRY_RETURN(decode(value, "workspaceFolders", target.workspaceFolders));
    return {};
}

struct InitializeParams : public _InitializeParams, public WorkspaceFoldersInitializeParams {
};

template<>
inline JSONValue to_json(InitializeParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<_InitializeParams>(obj));
    ret.merge(to_json<WorkspaceFoldersInitializeParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InitializeParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InitializeParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "processId", target.processId));
    TRY_RETURN(decode(value, "clientInfo", target.clientInfo));
    TRY_RETURN(decode(value, "locale", target.locale));
    TRY_RETURN(decode(value, "rootPath", target.rootPath));
    TRY_RETURN(decode(value, "rootUri", target.rootUri));
    TRY_RETURN(decode(value, "capabilities", target.capabilities));
    TRY_RETURN(decode(value, "initializationOptions", target.initializationOptions));
    TRY_RETURN(decode(value, "trace", target.trace));
    TRY_RETURN(decode(value, "workspaceFolders", target.workspaceFolders));
    return {};
}

struct SaveOptions {
    std::optional<boolean> includeText  {};
};

template<>
inline JSONValue to_json(SaveOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "includeText", obj.includeText);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SaveOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SaveOptions" };

    TRY_RETURN(decode(value, "includeText", target.includeText));
    return {};
}

struct TextDocumentSyncOptions {
    std::optional<boolean> openClose  {};
    std::optional<TextDocumentSyncKind> change  {};
    std::optional<boolean> willSave  {};
    std::optional<boolean> willSaveWaitUntil  {};
    std::optional<std::variant<boolean, SaveOptions>> save  {};
};

template<>
inline JSONValue to_json(TextDocumentSyncOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "openClose", obj.openClose);
    set(ret, "change", obj.change);
    set(ret, "willSave", obj.willSave);
    set(ret, "willSaveWaitUntil", obj.willSaveWaitUntil);
    set(ret, "save", obj.save);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentSyncOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentSyncOptions" };

    TRY_RETURN(decode(value, "openClose", target.openClose));
    TRY_RETURN(decode(value, "change", target.change));
    TRY_RETURN(decode(value, "willSave", target.willSave));
    TRY_RETURN(decode(value, "willSaveWaitUntil", target.willSaveWaitUntil));
    TRY_RETURN(decode(value, "save", target.save));
    return {};
}

struct anon_53 {
    string language ;
};

template<>
inline JSONValue to_json(anon_53 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_53& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_53" };

    TRY_RETURN(decode(value, "language", target.language));
    return {};
}

struct anon_54 {
    string language ;
};

template<>
inline JSONValue to_json(anon_54 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_54& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_54" };

    TRY_RETURN(decode(value, "language", target.language));
    return {};
}

struct anon_52 {
    std::variant<string, NotebookDocumentFilter> notebook  {};
    std::optional<std::vector<anon_54>> cells  {};
};

template<>
inline JSONValue to_json(anon_52 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebook", obj.notebook);
    set(ret, "cells", obj.cells);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_52& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_52" };

    TRY_RETURN(decode(value, "notebook", target.notebook));
    TRY_RETURN(decode(value, "cells", target.cells));
    return {};
}

struct anon_56 {
    string language ;
};

template<>
inline JSONValue to_json(anon_56 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_56& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_56" };

    TRY_RETURN(decode(value, "language", target.language));
    return {};
}

struct anon_57 {
    string language ;
};

template<>
inline JSONValue to_json(anon_57 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "language", obj.language);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_57& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_57" };

    TRY_RETURN(decode(value, "language", target.language));
    return {};
}

struct anon_55 {
    std::optional<std::variant<string, NotebookDocumentFilter>> notebook  {};
    std::vector<anon_57> cells  {};
};

template<>
inline JSONValue to_json(anon_55 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebook", obj.notebook);
    set(ret, "cells", obj.cells);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_55& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_55" };

    TRY_RETURN(decode(value, "notebook", target.notebook));
    TRY_RETURN(decode(value, "cells", target.cells));
    return {};
}

struct NotebookDocumentSyncOptions {
    std::vector<std::variant<anon_52, anon_55>> notebookSelector  {};
    std::optional<boolean> save  {};
};

template<>
inline JSONValue to_json(NotebookDocumentSyncOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "notebookSelector", obj.notebookSelector);
    set(ret, "save", obj.save);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentSyncOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentSyncOptions" };

    TRY_RETURN(decode(value, "notebookSelector", target.notebookSelector));
    TRY_RETURN(decode(value, "save", target.save));
    return {};
}

struct NotebookDocumentSyncRegistrationOptions : public NotebookDocumentSyncOptions, public StaticRegistrationOptions {
};

template<>
inline JSONValue to_json(NotebookDocumentSyncRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<NotebookDocumentSyncOptions>(obj));
    ret.merge(to_json<StaticRegistrationOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, NotebookDocumentSyncRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "NotebookDocumentSyncRegistrationOptions" };

    TRY_RETURN(decode(value, "notebookSelector", target.notebookSelector));
    TRY_RETURN(decode(value, "save", target.save));
    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct anon_58 {
    std::optional<boolean> labelDetailsSupport  {};
};

template<>
inline JSONValue to_json(anon_58 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "labelDetailsSupport", obj.labelDetailsSupport);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_58& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_58" };

    TRY_RETURN(decode(value, "labelDetailsSupport", target.labelDetailsSupport));
    return {};
}

struct CompletionOptions : public WorkDoneProgressOptions {
    std::optional<std::vector<string>> triggerCharacters  {};
    std::optional<std::vector<string>> allCommitCharacters  {};
    std::optional<boolean> resolveProvider  {};
    std::optional<anon_58> completionItem  {};
};

template<>
inline JSONValue to_json(CompletionOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "triggerCharacters", obj.triggerCharacters);
    set(ret, "allCommitCharacters", obj.allCommitCharacters);
    set(ret, "resolveProvider", obj.resolveProvider);
    set(ret, "completionItem", obj.completionItem);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "triggerCharacters", target.triggerCharacters));
    TRY_RETURN(decode(value, "allCommitCharacters", target.allCommitCharacters));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    TRY_RETURN(decode(value, "completionItem", target.completionItem));
    return {};
}

struct HoverOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(HoverOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, HoverOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "HoverOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct SignatureHelpOptions : public WorkDoneProgressOptions {
    std::optional<std::vector<string>> triggerCharacters  {};
    std::optional<std::vector<string>> retriggerCharacters  {};
};

template<>
inline JSONValue to_json(SignatureHelpOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "triggerCharacters", obj.triggerCharacters);
    set(ret, "retriggerCharacters", obj.retriggerCharacters);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelpOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "triggerCharacters", target.triggerCharacters));
    TRY_RETURN(decode(value, "retriggerCharacters", target.retriggerCharacters));
    return {};
}

struct DefinitionOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DefinitionOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DefinitionOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DefinitionOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct ReferenceOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(ReferenceOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ReferenceOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ReferenceOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentHighlightOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DocumentHighlightOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlightOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentHighlightOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentSymbolOptions : public WorkDoneProgressOptions {
    std::optional<string> label  {};
};

template<>
inline JSONValue to_json(DocumentSymbolOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "label", obj.label);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentSymbolOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentSymbolOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "label", target.label));
    return {};
}

struct CodeActionOptions : public WorkDoneProgressOptions {
    std::optional<std::vector<CodeActionKind>> codeActionKinds  {};
    std::optional<boolean> resolveProvider  {};
};

template<>
inline JSONValue to_json(CodeActionOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "codeActionKinds", obj.codeActionKinds);
    set(ret, "resolveProvider", obj.resolveProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeActionOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "codeActionKinds", target.codeActionKinds));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct CodeLensOptions : public WorkDoneProgressOptions {
    std::optional<boolean> resolveProvider  {};
};

template<>
inline JSONValue to_json(CodeLensOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "resolveProvider", obj.resolveProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLensOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLensOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct DocumentLinkOptions : public WorkDoneProgressOptions {
    std::optional<boolean> resolveProvider  {};
};

template<>
inline JSONValue to_json(DocumentLinkOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "resolveProvider", obj.resolveProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentLinkOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentLinkOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct WorkspaceSymbolOptions : public WorkDoneProgressOptions {
    std::optional<boolean> resolveProvider  {};
};

template<>
inline JSONValue to_json(WorkspaceSymbolOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "resolveProvider", obj.resolveProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceSymbolOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceSymbolOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct DocumentFormattingOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DocumentFormattingOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentFormattingOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentFormattingOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentRangeFormattingOptions : public WorkDoneProgressOptions {
};

template<>
inline JSONValue to_json(DocumentRangeFormattingOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentRangeFormattingOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentRangeFormattingOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentOnTypeFormattingOptions {
    string firstTriggerCharacter ;
    std::optional<std::vector<string>> moreTriggerCharacter  {};
};

template<>
inline JSONValue to_json(DocumentOnTypeFormattingOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "firstTriggerCharacter", obj.firstTriggerCharacter);
    set(ret, "moreTriggerCharacter", obj.moreTriggerCharacter);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentOnTypeFormattingOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentOnTypeFormattingOptions" };

    TRY_RETURN(decode(value, "firstTriggerCharacter", target.firstTriggerCharacter));
    TRY_RETURN(decode(value, "moreTriggerCharacter", target.moreTriggerCharacter));
    return {};
}

struct RenameOptions : public WorkDoneProgressOptions {
    std::optional<boolean> prepareProvider  {};
};

template<>
inline JSONValue to_json(RenameOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "prepareProvider", obj.prepareProvider);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "prepareProvider", target.prepareProvider));
    return {};
}

struct ExecuteCommandOptions : public WorkDoneProgressOptions {
    std::vector<string> commands  {};
};

template<>
inline JSONValue to_json(ExecuteCommandOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressOptions>(obj));
    set(ret, "commands", obj.commands);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ExecuteCommandOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ExecuteCommandOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "commands", target.commands));
    return {};
}

struct WorkspaceFoldersServerCapabilities {
    std::optional<boolean> supported  {};
    std::optional<std::variant<string, boolean>> changeNotifications  {};
};

template<>
inline JSONValue to_json(WorkspaceFoldersServerCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "supported", obj.supported);
    set(ret, "changeNotifications", obj.changeNotifications);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceFoldersServerCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceFoldersServerCapabilities" };

    TRY_RETURN(decode(value, "supported", target.supported));
    TRY_RETURN(decode(value, "changeNotifications", target.changeNotifications));
    return {};
}

struct FileOperationOptions {
    std::optional<FileOperationRegistrationOptions> didCreate  {};
    std::optional<FileOperationRegistrationOptions> willCreate  {};
    std::optional<FileOperationRegistrationOptions> didRename  {};
    std::optional<FileOperationRegistrationOptions> willRename  {};
    std::optional<FileOperationRegistrationOptions> didDelete  {};
    std::optional<FileOperationRegistrationOptions> willDelete  {};
};

template<>
inline JSONValue to_json(FileOperationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "didCreate", obj.didCreate);
    set(ret, "willCreate", obj.willCreate);
    set(ret, "didRename", obj.didRename);
    set(ret, "willRename", obj.willRename);
    set(ret, "didDelete", obj.didDelete);
    set(ret, "willDelete", obj.willDelete);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileOperationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileOperationOptions" };

    TRY_RETURN(decode(value, "didCreate", target.didCreate));
    TRY_RETURN(decode(value, "willCreate", target.willCreate));
    TRY_RETURN(decode(value, "didRename", target.didRename));
    TRY_RETURN(decode(value, "willRename", target.willRename));
    TRY_RETURN(decode(value, "didDelete", target.didDelete));
    TRY_RETURN(decode(value, "willDelete", target.willDelete));
    return {};
}

struct anon_59 {
    std::optional<WorkspaceFoldersServerCapabilities> workspaceFolders  {};
    std::optional<FileOperationOptions> fileOperations  {};
};

template<>
inline JSONValue to_json(anon_59 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "workspaceFolders", obj.workspaceFolders);
    set(ret, "fileOperations", obj.fileOperations);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_59& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_59" };

    TRY_RETURN(decode(value, "workspaceFolders", target.workspaceFolders));
    TRY_RETURN(decode(value, "fileOperations", target.fileOperations));
    return {};
}

struct ServerCapabilities {
    std::optional<PositionEncodingKind> positionEncoding  {};
    std::optional<std::variant<TextDocumentSyncOptions, TextDocumentSyncKind>> textDocumentSync  {};
    std::optional<std::variant<NotebookDocumentSyncOptions, NotebookDocumentSyncRegistrationOptions>> notebookDocumentSync  {};
    std::optional<CompletionOptions> completionProvider  {};
    std::optional<std::variant<boolean, HoverOptions>> hoverProvider  {};
    std::optional<SignatureHelpOptions> signatureHelpProvider  {};
    std::optional<std::variant<boolean, DeclarationOptions, DeclarationRegistrationOptions>> declarationProvider  {};
    std::optional<std::variant<boolean, DefinitionOptions>> definitionProvider  {};
    std::optional<std::variant<boolean, TypeDefinitionOptions, TypeDefinitionRegistrationOptions>> typeDefinitionProvider  {};
    std::optional<std::variant<boolean, ImplementationOptions, ImplementationRegistrationOptions>> implementationProvider  {};
    std::optional<std::variant<boolean, ReferenceOptions>> referencesProvider  {};
    std::optional<std::variant<boolean, DocumentHighlightOptions>> documentHighlightProvider  {};
    std::optional<std::variant<boolean, DocumentSymbolOptions>> documentSymbolProvider  {};
    std::optional<std::variant<boolean, CodeActionOptions>> codeActionProvider  {};
    std::optional<CodeLensOptions> codeLensProvider  {};
    std::optional<DocumentLinkOptions> documentLinkProvider  {};
    std::optional<std::variant<boolean, DocumentColorOptions, DocumentColorRegistrationOptions>> colorProvider  {};
    std::optional<std::variant<boolean, WorkspaceSymbolOptions>> workspaceSymbolProvider  {};
    std::optional<std::variant<boolean, DocumentFormattingOptions>> documentFormattingProvider  {};
    std::optional<std::variant<boolean, DocumentRangeFormattingOptions>> documentRangeFormattingProvider  {};
    std::optional<DocumentOnTypeFormattingOptions> documentOnTypeFormattingProvider  {};
    std::optional<std::variant<boolean, RenameOptions>> renameProvider  {};
    std::optional<std::variant<boolean, FoldingRangeOptions, FoldingRangeRegistrationOptions>> foldingRangeProvider  {};
    std::optional<std::variant<boolean, SelectionRangeOptions, SelectionRangeRegistrationOptions>> selectionRangeProvider  {};
    std::optional<ExecuteCommandOptions> executeCommandProvider  {};
    std::optional<std::variant<boolean, CallHierarchyOptions, CallHierarchyRegistrationOptions>> callHierarchyProvider  {};
    std::optional<std::variant<boolean, LinkedEditingRangeOptions, LinkedEditingRangeRegistrationOptions>> linkedEditingRangeProvider  {};
    std::optional<std::variant<SemanticTokensOptions, SemanticTokensRegistrationOptions>> semanticTokensProvider  {};
    std::optional<std::variant<boolean, MonikerOptions, MonikerRegistrationOptions>> monikerProvider  {};
    std::optional<std::variant<boolean, TypeHierarchyOptions, TypeHierarchyRegistrationOptions>> typeHierarchyProvider  {};
    std::optional<std::variant<boolean, InlineValueOptions, InlineValueRegistrationOptions>> inlineValueProvider  {};
    std::optional<std::variant<boolean, InlayHintOptions, InlayHintRegistrationOptions>> inlayHintProvider  {};
    std::optional<std::variant<DiagnosticOptions, DiagnosticRegistrationOptions>> diagnosticProvider  {};
    std::optional<anon_59> workspace  {};
    std::optional<LSPAny> experimental  {};
};

template<>
inline JSONValue to_json(ServerCapabilities const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "positionEncoding", obj.positionEncoding);
    set(ret, "textDocumentSync", obj.textDocumentSync);
    set(ret, "notebookDocumentSync", obj.notebookDocumentSync);
    set(ret, "completionProvider", obj.completionProvider);
    set(ret, "hoverProvider", obj.hoverProvider);
    set(ret, "signatureHelpProvider", obj.signatureHelpProvider);
    set(ret, "declarationProvider", obj.declarationProvider);
    set(ret, "definitionProvider", obj.definitionProvider);
    set(ret, "typeDefinitionProvider", obj.typeDefinitionProvider);
    set(ret, "implementationProvider", obj.implementationProvider);
    set(ret, "referencesProvider", obj.referencesProvider);
    set(ret, "documentHighlightProvider", obj.documentHighlightProvider);
    set(ret, "documentSymbolProvider", obj.documentSymbolProvider);
    set(ret, "codeActionProvider", obj.codeActionProvider);
    set(ret, "codeLensProvider", obj.codeLensProvider);
    set(ret, "documentLinkProvider", obj.documentLinkProvider);
    set(ret, "colorProvider", obj.colorProvider);
    set(ret, "workspaceSymbolProvider", obj.workspaceSymbolProvider);
    set(ret, "documentFormattingProvider", obj.documentFormattingProvider);
    set(ret, "documentRangeFormattingProvider", obj.documentRangeFormattingProvider);
    set(ret, "documentOnTypeFormattingProvider", obj.documentOnTypeFormattingProvider);
    set(ret, "renameProvider", obj.renameProvider);
    set(ret, "foldingRangeProvider", obj.foldingRangeProvider);
    set(ret, "selectionRangeProvider", obj.selectionRangeProvider);
    set(ret, "executeCommandProvider", obj.executeCommandProvider);
    set(ret, "callHierarchyProvider", obj.callHierarchyProvider);
    set(ret, "linkedEditingRangeProvider", obj.linkedEditingRangeProvider);
    set(ret, "semanticTokensProvider", obj.semanticTokensProvider);
    set(ret, "monikerProvider", obj.monikerProvider);
    set(ret, "typeHierarchyProvider", obj.typeHierarchyProvider);
    set(ret, "inlineValueProvider", obj.inlineValueProvider);
    set(ret, "inlayHintProvider", obj.inlayHintProvider);
    set(ret, "diagnosticProvider", obj.diagnosticProvider);
    set(ret, "workspace", obj.workspace);
    set(ret, "experimental", obj.experimental);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ServerCapabilities& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ServerCapabilities" };

    TRY_RETURN(decode(value, "positionEncoding", target.positionEncoding));
    TRY_RETURN(decode(value, "textDocumentSync", target.textDocumentSync));
    TRY_RETURN(decode(value, "notebookDocumentSync", target.notebookDocumentSync));
    TRY_RETURN(decode(value, "completionProvider", target.completionProvider));
    TRY_RETURN(decode(value, "hoverProvider", target.hoverProvider));
    TRY_RETURN(decode(value, "signatureHelpProvider", target.signatureHelpProvider));
    TRY_RETURN(decode(value, "declarationProvider", target.declarationProvider));
    TRY_RETURN(decode(value, "definitionProvider", target.definitionProvider));
    TRY_RETURN(decode(value, "typeDefinitionProvider", target.typeDefinitionProvider));
    TRY_RETURN(decode(value, "implementationProvider", target.implementationProvider));
    TRY_RETURN(decode(value, "referencesProvider", target.referencesProvider));
    TRY_RETURN(decode(value, "documentHighlightProvider", target.documentHighlightProvider));
    TRY_RETURN(decode(value, "documentSymbolProvider", target.documentSymbolProvider));
    TRY_RETURN(decode(value, "codeActionProvider", target.codeActionProvider));
    TRY_RETURN(decode(value, "codeLensProvider", target.codeLensProvider));
    TRY_RETURN(decode(value, "documentLinkProvider", target.documentLinkProvider));
    TRY_RETURN(decode(value, "colorProvider", target.colorProvider));
    TRY_RETURN(decode(value, "workspaceSymbolProvider", target.workspaceSymbolProvider));
    TRY_RETURN(decode(value, "documentFormattingProvider", target.documentFormattingProvider));
    TRY_RETURN(decode(value, "documentRangeFormattingProvider", target.documentRangeFormattingProvider));
    TRY_RETURN(decode(value, "documentOnTypeFormattingProvider", target.documentOnTypeFormattingProvider));
    TRY_RETURN(decode(value, "renameProvider", target.renameProvider));
    TRY_RETURN(decode(value, "foldingRangeProvider", target.foldingRangeProvider));
    TRY_RETURN(decode(value, "selectionRangeProvider", target.selectionRangeProvider));
    TRY_RETURN(decode(value, "executeCommandProvider", target.executeCommandProvider));
    TRY_RETURN(decode(value, "callHierarchyProvider", target.callHierarchyProvider));
    TRY_RETURN(decode(value, "linkedEditingRangeProvider", target.linkedEditingRangeProvider));
    TRY_RETURN(decode(value, "semanticTokensProvider", target.semanticTokensProvider));
    TRY_RETURN(decode(value, "monikerProvider", target.monikerProvider));
    TRY_RETURN(decode(value, "typeHierarchyProvider", target.typeHierarchyProvider));
    TRY_RETURN(decode(value, "inlineValueProvider", target.inlineValueProvider));
    TRY_RETURN(decode(value, "inlayHintProvider", target.inlayHintProvider));
    TRY_RETURN(decode(value, "diagnosticProvider", target.diagnosticProvider));
    TRY_RETURN(decode(value, "workspace", target.workspace));
    TRY_RETURN(decode(value, "experimental", target.experimental));
    return {};
}

struct anon_60 {
    string name ;
    std::optional<string> version  {};
};

template<>
inline JSONValue to_json(anon_60 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "version", obj.version);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_60& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_60" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "version", target.version));
    return {};
}

struct InitializeResult {
    ServerCapabilities capabilities ;
    std::optional<anon_60> serverInfo  {};
};

template<>
inline JSONValue to_json(InitializeResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "capabilities", obj.capabilities);
    set(ret, "serverInfo", obj.serverInfo);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InitializeResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InitializeResult" };

    TRY_RETURN(decode(value, "capabilities", target.capabilities));
    TRY_RETURN(decode(value, "serverInfo", target.serverInfo));
    return {};
}

struct InitializeError {
    boolean retry { false };
};

template<>
inline JSONValue to_json(InitializeError const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "retry", obj.retry);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InitializeError& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InitializeError" };

    TRY_RETURN(decode(value, "retry", target.retry));
    return {};
}

struct InitializedParams {
};

template<>
inline JSONValue to_json(InitializedParams const& obj)
{
    JSONValue ret = JSONValue::object();
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InitializedParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InitializedParams" };

    return {};
}

struct DidChangeConfigurationParams {
    LSPAny settings ;
};

template<>
inline JSONValue to_json(DidChangeConfigurationParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "settings", obj.settings);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeConfigurationParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeConfigurationParams" };

    TRY_RETURN(decode(value, "settings", target.settings));
    return {};
}

struct DidChangeConfigurationRegistrationOptions {
    std::optional<std::variant<string, std::vector<string>>> section  {};
};

template<>
inline JSONValue to_json(DidChangeConfigurationRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "section", obj.section);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeConfigurationRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeConfigurationRegistrationOptions" };

    TRY_RETURN(decode(value, "section", target.section));
    return {};
}

struct ShowMessageParams {
    MessageType type ;
    string message ;
};

template<>
inline JSONValue to_json(ShowMessageParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "type", obj.type);
    set(ret, "message", obj.message);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowMessageParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowMessageParams" };

    TRY_RETURN(decode(value, "type", target.type));
    TRY_RETURN(decode(value, "message", target.message));
    return {};
}

struct MessageActionItem {
    string title ;
};

template<>
inline JSONValue to_json(MessageActionItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "title", obj.title);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, MessageActionItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "MessageActionItem" };

    TRY_RETURN(decode(value, "title", target.title));
    return {};
}

struct ShowMessageRequestParams {
    MessageType type ;
    string message ;
    std::optional<std::vector<MessageActionItem>> actions  {};
};

template<>
inline JSONValue to_json(ShowMessageRequestParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "type", obj.type);
    set(ret, "message", obj.message);
    set(ret, "actions", obj.actions);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ShowMessageRequestParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ShowMessageRequestParams" };

    TRY_RETURN(decode(value, "type", target.type));
    TRY_RETURN(decode(value, "message", target.message));
    TRY_RETURN(decode(value, "actions", target.actions));
    return {};
}

struct LogMessageParams {
    MessageType type ;
    string message ;
};

template<>
inline JSONValue to_json(LogMessageParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "type", obj.type);
    set(ret, "message", obj.message);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LogMessageParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LogMessageParams" };

    TRY_RETURN(decode(value, "type", target.type));
    TRY_RETURN(decode(value, "message", target.message));
    return {};
}

struct DidOpenTextDocumentParams {
    TextDocumentItem textDocument ;
};

template<>
inline JSONValue to_json(DidOpenTextDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidOpenTextDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidOpenTextDocumentParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct DidChangeTextDocumentParams {
    VersionedTextDocumentIdentifier textDocument ;
    std::vector<TextDocumentContentChangeEvent> contentChanges  {};
};

template<>
inline JSONValue to_json(DidChangeTextDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "contentChanges", obj.contentChanges);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeTextDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeTextDocumentParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "contentChanges", target.contentChanges));
    return {};
}

struct TextDocumentChangeRegistrationOptions : public TextDocumentRegistrationOptions {
    TextDocumentSyncKind syncKind ;
};

template<>
inline JSONValue to_json(TextDocumentChangeRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    set(ret, "syncKind", obj.syncKind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentChangeRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentChangeRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "syncKind", target.syncKind));
    return {};
}

struct DidCloseTextDocumentParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(DidCloseTextDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidCloseTextDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidCloseTextDocumentParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct DidSaveTextDocumentParams {
    TextDocumentIdentifier textDocument ;
    std::optional<string> text  {};
};

template<>
inline JSONValue to_json(DidSaveTextDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "text", obj.text);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidSaveTextDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidSaveTextDocumentParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "text", target.text));
    return {};
}

struct TextDocumentSaveRegistrationOptions : public TextDocumentRegistrationOptions, public SaveOptions {
};

template<>
inline JSONValue to_json(TextDocumentSaveRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<SaveOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, TextDocumentSaveRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "TextDocumentSaveRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "includeText", target.includeText));
    return {};
}

struct WillSaveTextDocumentParams {
    TextDocumentIdentifier textDocument ;
    TextDocumentSaveReason reason ;
};

template<>
inline JSONValue to_json(WillSaveTextDocumentParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "reason", obj.reason);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WillSaveTextDocumentParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WillSaveTextDocumentParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "reason", target.reason));
    return {};
}

struct FileEvent {
    DocumentUri uri ;
    FileChangeType type ;
};

template<>
inline JSONValue to_json(FileEvent const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "type", obj.type);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileEvent& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileEvent" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "type", target.type));
    return {};
}

struct DidChangeWatchedFilesParams {
    std::vector<FileEvent> changes  {};
};

template<>
inline JSONValue to_json(DidChangeWatchedFilesParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "changes", obj.changes);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeWatchedFilesParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeWatchedFilesParams" };

    TRY_RETURN(decode(value, "changes", target.changes));
    return {};
}

struct FileSystemWatcher {
    GlobPattern globPattern ;
    std::optional<WatchKind> kind  {};
};

template<>
inline JSONValue to_json(FileSystemWatcher const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "globPattern", obj.globPattern);
    set(ret, "kind", obj.kind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FileSystemWatcher& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FileSystemWatcher" };

    TRY_RETURN(decode(value, "globPattern", target.globPattern));
    TRY_RETURN(decode(value, "kind", target.kind));
    return {};
}

struct DidChangeWatchedFilesRegistrationOptions {
    std::vector<FileSystemWatcher> watchers  {};
};

template<>
inline JSONValue to_json(DidChangeWatchedFilesRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "watchers", obj.watchers);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DidChangeWatchedFilesRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DidChangeWatchedFilesRegistrationOptions" };

    TRY_RETURN(decode(value, "watchers", target.watchers));
    return {};
}

struct PublishDiagnosticsParams {
    DocumentUri uri ;
    std::optional<integer> version  {};
    std::vector<Diagnostic> diagnostics  {};
};

template<>
inline JSONValue to_json(PublishDiagnosticsParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    set(ret, "version", obj.version);
    set(ret, "diagnostics", obj.diagnostics);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PublishDiagnosticsParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "PublishDiagnosticsParams" };

    TRY_RETURN(decode(value, "uri", target.uri));
    TRY_RETURN(decode(value, "version", target.version));
    TRY_RETURN(decode(value, "diagnostics", target.diagnostics));
    return {};
}

struct CompletionContext {
    CompletionTriggerKind triggerKind ;
    std::optional<string> triggerCharacter  {};
};

template<>
inline JSONValue to_json(CompletionContext const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "triggerKind", obj.triggerKind);
    set(ret, "triggerCharacter", obj.triggerCharacter);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionContext& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionContext" };

    TRY_RETURN(decode(value, "triggerKind", target.triggerKind));
    TRY_RETURN(decode(value, "triggerCharacter", target.triggerCharacter));
    return {};
}

struct CompletionParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
    std::optional<CompletionContext> context  {};
};

template<>
inline JSONValue to_json(CompletionParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "context", obj.context);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "context", target.context));
    return {};
}

struct CompletionItemLabelDetails {
    std::optional<string> detail  {};
    std::optional<string> description  {};
};

template<>
inline JSONValue to_json(CompletionItemLabelDetails const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "detail", obj.detail);
    set(ret, "description", obj.description);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionItemLabelDetails& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionItemLabelDetails" };

    TRY_RETURN(decode(value, "detail", target.detail));
    TRY_RETURN(decode(value, "description", target.description));
    return {};
}

struct InsertReplaceEdit {
    string newText ;
    Range insert ;
    Range replace ;
};

template<>
inline JSONValue to_json(InsertReplaceEdit const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "newText", obj.newText);
    set(ret, "insert", obj.insert);
    set(ret, "replace", obj.replace);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, InsertReplaceEdit& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "InsertReplaceEdit" };

    TRY_RETURN(decode(value, "newText", target.newText));
    TRY_RETURN(decode(value, "insert", target.insert));
    TRY_RETURN(decode(value, "replace", target.replace));
    return {};
}

struct CompletionItem {
    string label ;
    std::optional<CompletionItemLabelDetails> labelDetails  {};
    std::optional<CompletionItemKind> kind  {};
    std::optional<std::vector<CompletionItemTag>> tags  {};
    std::optional<string> detail  {};
    std::optional<std::variant<string, MarkupContent>> documentation  {};
    std::optional<boolean> deprecated  {};
    std::optional<boolean> preselect  {};
    std::optional<string> sortText  {};
    std::optional<string> filterText  {};
    std::optional<string> insertText  {};
    std::optional<InsertTextFormat> insertTextFormat  {};
    std::optional<InsertTextMode> insertTextMode  {};
    std::optional<std::variant<TextEdit, InsertReplaceEdit>> textEdit  {};
    std::optional<string> textEditText  {};
    std::optional<std::vector<TextEdit>> additionalTextEdits  {};
    std::optional<std::vector<string>> commitCharacters  {};
    std::optional<Command> command  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(CompletionItem const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "labelDetails", obj.labelDetails);
    set(ret, "kind", obj.kind);
    set(ret, "tags", obj.tags);
    set(ret, "detail", obj.detail);
    set(ret, "documentation", obj.documentation);
    set(ret, "deprecated", obj.deprecated);
    set(ret, "preselect", obj.preselect);
    set(ret, "sortText", obj.sortText);
    set(ret, "filterText", obj.filterText);
    set(ret, "insertText", obj.insertText);
    set(ret, "insertTextFormat", obj.insertTextFormat);
    set(ret, "insertTextMode", obj.insertTextMode);
    set(ret, "textEdit", obj.textEdit);
    set(ret, "textEditText", obj.textEditText);
    set(ret, "additionalTextEdits", obj.additionalTextEdits);
    set(ret, "commitCharacters", obj.commitCharacters);
    set(ret, "command", obj.command);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionItem& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionItem" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "labelDetails", target.labelDetails));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "detail", target.detail));
    TRY_RETURN(decode(value, "documentation", target.documentation));
    TRY_RETURN(decode(value, "deprecated", target.deprecated));
    TRY_RETURN(decode(value, "preselect", target.preselect));
    TRY_RETURN(decode(value, "sortText", target.sortText));
    TRY_RETURN(decode(value, "filterText", target.filterText));
    TRY_RETURN(decode(value, "insertText", target.insertText));
    TRY_RETURN(decode(value, "insertTextFormat", target.insertTextFormat));
    TRY_RETURN(decode(value, "insertTextMode", target.insertTextMode));
    TRY_RETURN(decode(value, "textEdit", target.textEdit));
    TRY_RETURN(decode(value, "textEditText", target.textEditText));
    TRY_RETURN(decode(value, "additionalTextEdits", target.additionalTextEdits));
    TRY_RETURN(decode(value, "commitCharacters", target.commitCharacters));
    TRY_RETURN(decode(value, "command", target.command));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct anon_62 {
    Range insert ;
    Range replace ;
};

template<>
inline JSONValue to_json(anon_62 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "insert", obj.insert);
    set(ret, "replace", obj.replace);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_62& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_62" };

    TRY_RETURN(decode(value, "insert", target.insert));
    TRY_RETURN(decode(value, "replace", target.replace));
    return {};
}

struct anon_63 {
    Range insert ;
    Range replace ;
};

template<>
inline JSONValue to_json(anon_63 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "insert", obj.insert);
    set(ret, "replace", obj.replace);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_63& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_63" };

    TRY_RETURN(decode(value, "insert", target.insert));
    TRY_RETURN(decode(value, "replace", target.replace));
    return {};
}

struct anon_61 {
    std::optional<std::vector<string>> commitCharacters  {};
    std::optional<std::variant<Range, anon_63>> editRange  {};
    std::optional<InsertTextFormat> insertTextFormat  {};
    std::optional<InsertTextMode> insertTextMode  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(anon_61 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "commitCharacters", obj.commitCharacters);
    set(ret, "editRange", obj.editRange);
    set(ret, "insertTextFormat", obj.insertTextFormat);
    set(ret, "insertTextMode", obj.insertTextMode);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_61& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_61" };

    TRY_RETURN(decode(value, "commitCharacters", target.commitCharacters));
    TRY_RETURN(decode(value, "editRange", target.editRange));
    TRY_RETURN(decode(value, "insertTextFormat", target.insertTextFormat));
    TRY_RETURN(decode(value, "insertTextMode", target.insertTextMode));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct CompletionList {
    boolean isIncomplete { false };
    std::optional<anon_61> itemDefaults  {};
    std::vector<CompletionItem> items  {};
};

template<>
inline JSONValue to_json(CompletionList const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "isIncomplete", obj.isIncomplete);
    set(ret, "itemDefaults", obj.itemDefaults);
    set(ret, "items", obj.items);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionList& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionList" };

    TRY_RETURN(decode(value, "isIncomplete", target.isIncomplete));
    TRY_RETURN(decode(value, "itemDefaults", target.itemDefaults));
    TRY_RETURN(decode(value, "items", target.items));
    return {};
}

struct CompletionRegistrationOptions : public TextDocumentRegistrationOptions, public CompletionOptions {
};

template<>
inline JSONValue to_json(CompletionRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<CompletionOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CompletionRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CompletionRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "triggerCharacters", target.triggerCharacters));
    TRY_RETURN(decode(value, "allCommitCharacters", target.allCommitCharacters));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    TRY_RETURN(decode(value, "completionItem", target.completionItem));
    return {};
}

struct HoverParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
};

template<>
inline JSONValue to_json(HoverParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, HoverParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "HoverParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct Hover {
    std::variant<MarkupContent, MarkedString, std::vector<MarkedString>> contents  {};
    std::optional<Range> range  {};
};

template<>
inline JSONValue to_json(Hover const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "contents", obj.contents);
    set(ret, "range", obj.range);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, Hover& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "Hover" };

    TRY_RETURN(decode(value, "contents", target.contents));
    TRY_RETURN(decode(value, "range", target.range));
    return {};
}

struct HoverRegistrationOptions : public TextDocumentRegistrationOptions, public HoverOptions {
};

template<>
inline JSONValue to_json(HoverRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<HoverOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, HoverRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "HoverRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct ParameterInformation {
    std::variant<string, std::pair<uinteger, uinteger>> label  {};
    std::optional<std::variant<string, MarkupContent>> documentation  {};
};

template<>
inline JSONValue to_json(ParameterInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "documentation", obj.documentation);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ParameterInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ParameterInformation" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "documentation", target.documentation));
    return {};
}

struct SignatureInformation {
    string label ;
    std::optional<std::variant<string, MarkupContent>> documentation  {};
    std::optional<std::vector<ParameterInformation>> parameters  {};
    std::optional<uinteger> activeParameter  {};
};

template<>
inline JSONValue to_json(SignatureInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "documentation", obj.documentation);
    set(ret, "parameters", obj.parameters);
    set(ret, "activeParameter", obj.activeParameter);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureInformation" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "documentation", target.documentation));
    TRY_RETURN(decode(value, "parameters", target.parameters));
    TRY_RETURN(decode(value, "activeParameter", target.activeParameter));
    return {};
}

struct SignatureHelp {
    std::vector<SignatureInformation> signatures  {};
    std::optional<uinteger> activeSignature  {};
    std::optional<uinteger> activeParameter  {};
};

template<>
inline JSONValue to_json(SignatureHelp const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "signatures", obj.signatures);
    set(ret, "activeSignature", obj.activeSignature);
    set(ret, "activeParameter", obj.activeParameter);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelp& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelp" };

    TRY_RETURN(decode(value, "signatures", target.signatures));
    TRY_RETURN(decode(value, "activeSignature", target.activeSignature));
    TRY_RETURN(decode(value, "activeParameter", target.activeParameter));
    return {};
}

struct SignatureHelpContext {
    SignatureHelpTriggerKind triggerKind ;
    std::optional<string> triggerCharacter  {};
    boolean isRetrigger { false };
    std::optional<SignatureHelp> activeSignatureHelp  {};
};

template<>
inline JSONValue to_json(SignatureHelpContext const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "triggerKind", obj.triggerKind);
    set(ret, "triggerCharacter", obj.triggerCharacter);
    set(ret, "isRetrigger", obj.isRetrigger);
    set(ret, "activeSignatureHelp", obj.activeSignatureHelp);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpContext& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelpContext" };

    TRY_RETURN(decode(value, "triggerKind", target.triggerKind));
    TRY_RETURN(decode(value, "triggerCharacter", target.triggerCharacter));
    TRY_RETURN(decode(value, "isRetrigger", target.isRetrigger));
    TRY_RETURN(decode(value, "activeSignatureHelp", target.activeSignatureHelp));
    return {};
}

struct SignatureHelpParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
    std::optional<SignatureHelpContext> context  {};
};

template<>
inline JSONValue to_json(SignatureHelpParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "context", obj.context);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelpParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "context", target.context));
    return {};
}

struct SignatureHelpRegistrationOptions : public TextDocumentRegistrationOptions, public SignatureHelpOptions {
};

template<>
inline JSONValue to_json(SignatureHelpRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<SignatureHelpOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SignatureHelpRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SignatureHelpRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "triggerCharacters", target.triggerCharacters));
    TRY_RETURN(decode(value, "retriggerCharacters", target.retriggerCharacters));
    return {};
}

struct DefinitionParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(DefinitionParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DefinitionParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DefinitionParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct DefinitionRegistrationOptions : public TextDocumentRegistrationOptions, public DefinitionOptions {
};

template<>
inline JSONValue to_json(DefinitionRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DefinitionOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DefinitionRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DefinitionRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct ReferenceContext {
    boolean includeDeclaration { false };
};

template<>
inline JSONValue to_json(ReferenceContext const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "includeDeclaration", obj.includeDeclaration);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ReferenceContext& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ReferenceContext" };

    TRY_RETURN(decode(value, "includeDeclaration", target.includeDeclaration));
    return {};
}

struct ReferenceParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
    ReferenceContext context ;
};

template<>
inline JSONValue to_json(ReferenceParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "context", obj.context);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ReferenceParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ReferenceParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "context", target.context));
    return {};
}

struct ReferenceRegistrationOptions : public TextDocumentRegistrationOptions, public ReferenceOptions {
};

template<>
inline JSONValue to_json(ReferenceRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<ReferenceOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ReferenceRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ReferenceRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentHighlightParams : public TextDocumentPositionParams, public WorkDoneProgressParams, public PartialResultParams {
};

template<>
inline JSONValue to_json(DocumentHighlightParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlightParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentHighlightParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    return {};
}

struct DocumentHighlight {
    Range range ;
    std::optional<DocumentHighlightKind> kind  {};
};

template<>
inline JSONValue to_json(DocumentHighlight const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "kind", obj.kind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlight& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentHighlight" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "kind", target.kind));
    return {};
}

struct DocumentHighlightRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentHighlightOptions {
};

template<>
inline JSONValue to_json(DocumentHighlightRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentHighlightOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentHighlightRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentHighlightRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentSymbolParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(DocumentSymbolParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentSymbolParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentSymbolParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct BaseSymbolInformation {
    string name ;
    SymbolKind kind ;
    std::optional<std::vector<SymbolTag>> tags  {};
    std::optional<string> containerName  {};
};

template<>
inline JSONValue to_json(BaseSymbolInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "kind", obj.kind);
    set(ret, "tags", obj.tags);
    set(ret, "containerName", obj.containerName);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, BaseSymbolInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "BaseSymbolInformation" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "containerName", target.containerName));
    return {};
}

struct SymbolInformation : public BaseSymbolInformation {
    std::optional<boolean> deprecated  {};
    Location location ;
};

template<>
inline JSONValue to_json(SymbolInformation const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<BaseSymbolInformation>(obj));
    set(ret, "deprecated", obj.deprecated);
    set(ret, "location", obj.location);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SymbolInformation& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SymbolInformation" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "containerName", target.containerName));
    TRY_RETURN(decode(value, "deprecated", target.deprecated));
    TRY_RETURN(decode(value, "location", target.location));
    return {};
}

struct DocumentSymbol {
    string name ;
    std::optional<string> detail  {};
    SymbolKind kind ;
    std::optional<std::vector<SymbolTag>> tags  {};
    std::optional<boolean> deprecated  {};
    Range range ;
    Range selectionRange ;
    std::optional<std::vector<DocumentSymbol>> children  {};
};

template<>
inline JSONValue to_json(DocumentSymbol const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "name", obj.name);
    set(ret, "detail", obj.detail);
    set(ret, "kind", obj.kind);
    set(ret, "tags", obj.tags);
    set(ret, "deprecated", obj.deprecated);
    set(ret, "range", obj.range);
    set(ret, "selectionRange", obj.selectionRange);
    set(ret, "children", obj.children);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentSymbol& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentSymbol" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "detail", target.detail));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "deprecated", target.deprecated));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "selectionRange", target.selectionRange));
    TRY_RETURN(decode(value, "children", target.children));
    return {};
}

struct DocumentSymbolRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentSymbolOptions {
};

template<>
inline JSONValue to_json(DocumentSymbolRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentSymbolOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentSymbolRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentSymbolRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "label", target.label));
    return {};
}

struct CodeActionContext {
    std::vector<Diagnostic> diagnostics  {};
    std::optional<std::vector<CodeActionKind>> only  {};
    std::optional<CodeActionTriggerKind> triggerKind  {};
};

template<>
inline JSONValue to_json(CodeActionContext const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "diagnostics", obj.diagnostics);
    set(ret, "only", obj.only);
    set(ret, "triggerKind", obj.triggerKind);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionContext& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeActionContext" };

    TRY_RETURN(decode(value, "diagnostics", target.diagnostics));
    TRY_RETURN(decode(value, "only", target.only));
    TRY_RETURN(decode(value, "triggerKind", target.triggerKind));
    return {};
}

struct CodeActionParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
    Range range ;
    CodeActionContext context ;
};

template<>
inline JSONValue to_json(CodeActionParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "range", obj.range);
    set(ret, "context", obj.context);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeActionParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "context", target.context));
    return {};
}

struct anon_64 {
    string reason ;
};

template<>
inline JSONValue to_json(anon_64 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "reason", obj.reason);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_64& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_64" };

    TRY_RETURN(decode(value, "reason", target.reason));
    return {};
}

struct CodeAction {
    string title ;
    std::optional<CodeActionKind> kind  {};
    std::optional<std::vector<Diagnostic>> diagnostics  {};
    std::optional<boolean> isPreferred  {};
    std::optional<anon_64> disabled  {};
    std::optional<WorkspaceEdit> edit  {};
    std::optional<Command> command  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(CodeAction const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "title", obj.title);
    set(ret, "kind", obj.kind);
    set(ret, "diagnostics", obj.diagnostics);
    set(ret, "isPreferred", obj.isPreferred);
    set(ret, "disabled", obj.disabled);
    set(ret, "edit", obj.edit);
    set(ret, "command", obj.command);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeAction& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeAction" };

    TRY_RETURN(decode(value, "title", target.title));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "diagnostics", target.diagnostics));
    TRY_RETURN(decode(value, "isPreferred", target.isPreferred));
    TRY_RETURN(decode(value, "disabled", target.disabled));
    TRY_RETURN(decode(value, "edit", target.edit));
    TRY_RETURN(decode(value, "command", target.command));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct CodeActionRegistrationOptions : public TextDocumentRegistrationOptions, public CodeActionOptions {
};

template<>
inline JSONValue to_json(CodeActionRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<CodeActionOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeActionRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeActionRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "codeActionKinds", target.codeActionKinds));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct WorkspaceSymbolParams : public WorkDoneProgressParams, public PartialResultParams {
    string query ;
};

template<>
inline JSONValue to_json(WorkspaceSymbolParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "query", obj.query);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceSymbolParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceSymbolParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "query", target.query));
    return {};
}

struct anon_65 {
    DocumentUri uri ;
};

template<>
inline JSONValue to_json(anon_65 const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "uri", obj.uri);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, anon_65& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "anon_65" };

    TRY_RETURN(decode(value, "uri", target.uri));
    return {};
}

struct WorkspaceSymbol : public BaseSymbolInformation {
    std::variant<Location, anon_65> location  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(WorkspaceSymbol const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<BaseSymbolInformation>(obj));
    set(ret, "location", obj.location);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceSymbol& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceSymbol" };

    TRY_RETURN(decode(value, "name", target.name));
    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "tags", target.tags));
    TRY_RETURN(decode(value, "containerName", target.containerName));
    TRY_RETURN(decode(value, "location", target.location));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct WorkspaceSymbolRegistrationOptions : public WorkspaceSymbolOptions {
};

template<>
inline JSONValue to_json(WorkspaceSymbolRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkspaceSymbolOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkspaceSymbolRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkspaceSymbolRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct CodeLensParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(CodeLensParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLensParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLensParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct CodeLens {
    Range range ;
    std::optional<Command> command  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(CodeLens const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "command", obj.command);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLens& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLens" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "command", target.command));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct CodeLensRegistrationOptions : public TextDocumentRegistrationOptions, public CodeLensOptions {
};

template<>
inline JSONValue to_json(CodeLensRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<CodeLensOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CodeLensRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CodeLensRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct DocumentLinkParams : public WorkDoneProgressParams, public PartialResultParams {
    TextDocumentIdentifier textDocument ;
};

template<>
inline JSONValue to_json(DocumentLinkParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    ret.merge(to_json<PartialResultParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentLinkParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentLinkParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "partialResultToken", target.partialResultToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    return {};
}

struct DocumentLink {
    Range range ;
    std::optional<string> target  {};
    std::optional<string> tooltip  {};
    std::optional<LSPAny> data  {};
};

template<>
inline JSONValue to_json(DocumentLink const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "range", obj.range);
    set(ret, "target", obj.target);
    set(ret, "tooltip", obj.tooltip);
    set(ret, "data", obj.data);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentLink& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentLink" };

    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "target", target.target));
    TRY_RETURN(decode(value, "tooltip", target.tooltip));
    TRY_RETURN(decode(value, "data", target.data));
    return {};
}

struct DocumentLinkRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentLinkOptions {
};

template<>
inline JSONValue to_json(DocumentLinkRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentLinkOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentLinkRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentLinkRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "resolveProvider", target.resolveProvider));
    return {};
}

struct FormattingOptions {
    uinteger tabSize { 0 };
    boolean insertSpaces { false };
    std::optional<boolean> trimTrailingWhitespace  {};
    std::optional<boolean> insertFinalNewline  {};
    std::optional<boolean> trimFinalNewlines  {};
};

template<>
inline JSONValue to_json(FormattingOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "tabSize", obj.tabSize);
    set(ret, "insertSpaces", obj.insertSpaces);
    set(ret, "trimTrailingWhitespace", obj.trimTrailingWhitespace);
    set(ret, "insertFinalNewline", obj.insertFinalNewline);
    set(ret, "trimFinalNewlines", obj.trimFinalNewlines);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, FormattingOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "FormattingOptions" };

    TRY_RETURN(decode(value, "tabSize", target.tabSize));
    TRY_RETURN(decode(value, "insertSpaces", target.insertSpaces));
    TRY_RETURN(decode(value, "trimTrailingWhitespace", target.trimTrailingWhitespace));
    TRY_RETURN(decode(value, "insertFinalNewline", target.insertFinalNewline));
    TRY_RETURN(decode(value, "trimFinalNewlines", target.trimFinalNewlines));
    return {};
}

struct DocumentFormattingParams : public WorkDoneProgressParams {
    TextDocumentIdentifier textDocument ;
    FormattingOptions options ;
};

template<>
inline JSONValue to_json(DocumentFormattingParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentFormattingParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentFormattingParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct DocumentFormattingRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentFormattingOptions {
};

template<>
inline JSONValue to_json(DocumentFormattingRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentFormattingOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentFormattingRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentFormattingRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentRangeFormattingParams : public WorkDoneProgressParams {
    TextDocumentIdentifier textDocument ;
    Range range ;
    FormattingOptions options ;
};

template<>
inline JSONValue to_json(DocumentRangeFormattingParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "range", obj.range);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentRangeFormattingParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentRangeFormattingParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "range", target.range));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct DocumentRangeFormattingRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentRangeFormattingOptions {
};

template<>
inline JSONValue to_json(DocumentRangeFormattingRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentRangeFormattingOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentRangeFormattingRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentRangeFormattingRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    return {};
}

struct DocumentOnTypeFormattingParams {
    TextDocumentIdentifier textDocument ;
    Position position ;
    string ch ;
    FormattingOptions options ;
};

template<>
inline JSONValue to_json(DocumentOnTypeFormattingParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "textDocument", obj.textDocument);
    set(ret, "position", obj.position);
    set(ret, "ch", obj.ch);
    set(ret, "options", obj.options);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentOnTypeFormattingParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentOnTypeFormattingParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "ch", target.ch));
    TRY_RETURN(decode(value, "options", target.options));
    return {};
}

struct DocumentOnTypeFormattingRegistrationOptions : public TextDocumentRegistrationOptions, public DocumentOnTypeFormattingOptions {
};

template<>
inline JSONValue to_json(DocumentOnTypeFormattingRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<DocumentOnTypeFormattingOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, DocumentOnTypeFormattingRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "DocumentOnTypeFormattingRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "firstTriggerCharacter", target.firstTriggerCharacter));
    TRY_RETURN(decode(value, "moreTriggerCharacter", target.moreTriggerCharacter));
    return {};
}

struct RenameParams : public WorkDoneProgressParams {
    TextDocumentIdentifier textDocument ;
    Position position ;
    string newName ;
};

template<>
inline JSONValue to_json(RenameParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "textDocument", obj.textDocument);
    set(ret, "position", obj.position);
    set(ret, "newName", obj.newName);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "newName", target.newName));
    return {};
}

struct RenameRegistrationOptions : public TextDocumentRegistrationOptions, public RenameOptions {
};

template<>
inline JSONValue to_json(RenameRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentRegistrationOptions>(obj));
    ret.merge(to_json<RenameOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, RenameRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "RenameRegistrationOptions" };

    TRY_RETURN(decode(value, "documentSelector", target.documentSelector));
    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "prepareProvider", target.prepareProvider));
    return {};
}

struct PrepareRenameParams : public TextDocumentPositionParams, public WorkDoneProgressParams {
};

template<>
inline JSONValue to_json(PrepareRenameParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<TextDocumentPositionParams>(obj));
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, PrepareRenameParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "PrepareRenameParams" };

    TRY_RETURN(decode(value, "textDocument", target.textDocument));
    TRY_RETURN(decode(value, "position", target.position));
    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    return {};
}

struct ExecuteCommandParams : public WorkDoneProgressParams {
    string command ;
    std::optional<std::vector<LSPAny>> arguments  {};
};

template<>
inline JSONValue to_json(ExecuteCommandParams const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<WorkDoneProgressParams>(obj));
    set(ret, "command", obj.command);
    set(ret, "arguments", obj.arguments);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ExecuteCommandParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ExecuteCommandParams" };

    TRY_RETURN(decode(value, "workDoneToken", target.workDoneToken));
    TRY_RETURN(decode(value, "command", target.command));
    TRY_RETURN(decode(value, "arguments", target.arguments));
    return {};
}

struct ExecuteCommandRegistrationOptions : public ExecuteCommandOptions {
};

template<>
inline JSONValue to_json(ExecuteCommandRegistrationOptions const& obj)
{
    JSONValue ret = JSONValue::object();
    ret.merge(to_json<ExecuteCommandOptions>(obj));
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ExecuteCommandRegistrationOptions& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ExecuteCommandRegistrationOptions" };

    TRY_RETURN(decode(value, "workDoneProgress", target.workDoneProgress));
    TRY_RETURN(decode(value, "commands", target.commands));
    return {};
}

struct ApplyWorkspaceEditParams {
    std::optional<string> label  {};
    WorkspaceEdit edit ;
};

template<>
inline JSONValue to_json(ApplyWorkspaceEditParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "label", obj.label);
    set(ret, "edit", obj.edit);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ApplyWorkspaceEditParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ApplyWorkspaceEditParams" };

    TRY_RETURN(decode(value, "label", target.label));
    TRY_RETURN(decode(value, "edit", target.edit));
    return {};
}

struct ApplyWorkspaceEditResult {
    boolean applied { false };
    std::optional<string> failureReason  {};
    std::optional<uinteger> failedChange  {};
};

template<>
inline JSONValue to_json(ApplyWorkspaceEditResult const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "applied", obj.applied);
    set(ret, "failureReason", obj.failureReason);
    set(ret, "failedChange", obj.failedChange);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ApplyWorkspaceEditResult& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ApplyWorkspaceEditResult" };

    TRY_RETURN(decode(value, "applied", target.applied));
    TRY_RETURN(decode(value, "failureReason", target.failureReason));
    TRY_RETURN(decode(value, "failedChange", target.failedChange));
    return {};
}

struct WorkDoneProgressBegin {
    std::string kind  { "begin" };
    string title ;
    std::optional<boolean> cancellable  {};
    std::optional<string> message  {};
    std::optional<uinteger> percentage  {};
};

template<>
inline JSONValue to_json(WorkDoneProgressBegin const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "title", obj.title);
    set(ret, "cancellable", obj.cancellable);
    set(ret, "message", obj.message);
    set(ret, "percentage", obj.percentage);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressBegin& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressBegin" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "title", target.title));
    TRY_RETURN(decode(value, "cancellable", target.cancellable));
    TRY_RETURN(decode(value, "message", target.message));
    TRY_RETURN(decode(value, "percentage", target.percentage));
    return {};
}

struct WorkDoneProgressReport {
    std::string kind  { "report" };
    std::optional<boolean> cancellable  {};
    std::optional<string> message  {};
    std::optional<uinteger> percentage  {};
};

template<>
inline JSONValue to_json(WorkDoneProgressReport const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "cancellable", obj.cancellable);
    set(ret, "message", obj.message);
    set(ret, "percentage", obj.percentage);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressReport& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressReport" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "cancellable", target.cancellable));
    TRY_RETURN(decode(value, "message", target.message));
    TRY_RETURN(decode(value, "percentage", target.percentage));
    return {};
}

struct WorkDoneProgressEnd {
    std::string kind  { "end" };
    std::optional<string> message  {};
};

template<>
inline JSONValue to_json(WorkDoneProgressEnd const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "kind", obj.kind);
    set(ret, "message", obj.message);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, WorkDoneProgressEnd& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "WorkDoneProgressEnd" };

    TRY_RETURN(decode(value, "kind", target.kind));
    TRY_RETURN(decode(value, "message", target.message));
    return {};
}

struct SetTraceParams {
    TraceValues value ;
};

template<>
inline JSONValue to_json(SetTraceParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "value", obj.value);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, SetTraceParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "SetTraceParams" };

    TRY_RETURN(decode(value, "value", target.value));
    return {};
}

struct LogTraceParams {
    string message ;
    std::optional<string> verbose  {};
};

template<>
inline JSONValue to_json(LogTraceParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "message", obj.message);
    set(ret, "verbose", obj.verbose);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, LogTraceParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "LogTraceParams" };

    TRY_RETURN(decode(value, "message", target.message));
    TRY_RETURN(decode(value, "verbose", target.verbose));
    return {};
}

struct CancelParams {
    std::variant<integer, string> id  {};
};

template<>
inline JSONValue to_json(CancelParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "id", obj.id);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, CancelParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "CancelParams" };

    TRY_RETURN(decode(value, "id", target.id));
    return {};
}

struct ProgressParams {
    ProgressToken token ;
    LSPAny value ;
};

template<>
inline JSONValue to_json(ProgressParams const& obj)
{
    JSONValue ret = JSONValue::object();
    set(ret, "token", obj.token);
    set(ret, "value", obj.value);
    return ret;
}

template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, ProgressParams& target)
{
    if (!value.is_object())
        return JSONDecodeError { JSONDecodeError::Code::TypeMismatch, "ProgressParams" };

    TRY_RETURN(decode(value, "token", target.token));
    TRY_RETURN(decode(value, "value", target.value));
    return {};
}


struct WorkspaceDidChangeWorkspaceFolders : public Notification<DidChangeWorkspaceFoldersParams> {
    explicit WorkspaceDidChangeWorkspaceFolders(DidChangeWorkspaceFoldersParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidChangeWorkspaceFolders const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidChangeWorkspaceFoldersParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didChangeWorkspaceFolders");
    return msg;
}

struct WindowWorkDoneProgressCancel : public Notification<WorkDoneProgressCancelParams> {
    explicit WindowWorkDoneProgressCancel(WorkDoneProgressCancelParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WindowWorkDoneProgressCancel const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WorkDoneProgressCancelParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "window/workDoneProgress/cancel");
    return msg;
}

struct WorkspaceDidCreateFiles : public Notification<CreateFilesParams> {
    explicit WorkspaceDidCreateFiles(CreateFilesParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidCreateFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CreateFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didCreateFiles");
    return msg;
}

struct WorkspaceDidRenameFiles : public Notification<RenameFilesParams> {
    explicit WorkspaceDidRenameFiles(RenameFilesParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidRenameFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<RenameFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didRenameFiles");
    return msg;
}

struct WorkspaceDidDeleteFiles : public Notification<DeleteFilesParams> {
    explicit WorkspaceDidDeleteFiles(DeleteFilesParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidDeleteFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DeleteFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didDeleteFiles");
    return msg;
}

struct NotebookDocumentDidOpen : public Notification<DidOpenNotebookDocumentParams> {
    explicit NotebookDocumentDidOpen(DidOpenNotebookDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(NotebookDocumentDidOpen const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidOpenNotebookDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "notebookDocument/didOpen");
    return msg;
}

struct NotebookDocumentDidChange : public Notification<DidChangeNotebookDocumentParams> {
    explicit NotebookDocumentDidChange(DidChangeNotebookDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(NotebookDocumentDidChange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidChangeNotebookDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "notebookDocument/didChange");
    return msg;
}

struct NotebookDocumentDidSave : public Notification<DidSaveNotebookDocumentParams> {
    explicit NotebookDocumentDidSave(DidSaveNotebookDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(NotebookDocumentDidSave const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidSaveNotebookDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "notebookDocument/didSave");
    return msg;
}

struct NotebookDocumentDidClose : public Notification<DidCloseNotebookDocumentParams> {
    explicit NotebookDocumentDidClose(DidCloseNotebookDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(NotebookDocumentDidClose const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidCloseNotebookDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "notebookDocument/didClose");
    return msg;
}

struct Initialized : public Notification<InitializedParams> {
    explicit Initialized(InitializedParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(Initialized const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<InitializedParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "initialized");
    return msg;
}

struct Exit : public Notification<null> {
    Exit() = default;
};

template <>
inline JSONValue to_json(Exit const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "exit");
    return msg;
}

struct WorkspaceDidChangeConfiguration : public Notification<DidChangeConfigurationParams> {
    explicit WorkspaceDidChangeConfiguration(DidChangeConfigurationParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidChangeConfiguration const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidChangeConfigurationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didChangeConfiguration");
    return msg;
}

struct WindowShowMessage : public Notification<ShowMessageParams> {
    explicit WindowShowMessage(ShowMessageParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WindowShowMessage const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ShowMessageParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "window/showMessage");
    return msg;
}

struct WindowLogMessage : public Notification<LogMessageParams> {
    explicit WindowLogMessage(LogMessageParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WindowLogMessage const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<LogMessageParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "window/logMessage");
    return msg;
}

struct TelemetryEvent : public Notification<LSPAny> {
    explicit TelemetryEvent(LSPAny param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TelemetryEvent const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<LSPAny>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "telemetry/event");
    return msg;
}

struct TextDocumentDidOpen : public Notification<DidOpenTextDocumentParams> {
    explicit TextDocumentDidOpen(DidOpenTextDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentDidOpen const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidOpenTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/didOpen");
    return msg;
}

struct TextDocumentDidChange : public Notification<DidChangeTextDocumentParams> {
    explicit TextDocumentDidChange(DidChangeTextDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentDidChange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidChangeTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/didChange");
    return msg;
}

struct TextDocumentDidClose : public Notification<DidCloseTextDocumentParams> {
    explicit TextDocumentDidClose(DidCloseTextDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentDidClose const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidCloseTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/didClose");
    return msg;
}

struct TextDocumentDidSave : public Notification<DidSaveTextDocumentParams> {
    explicit TextDocumentDidSave(DidSaveTextDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentDidSave const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidSaveTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/didSave");
    return msg;
}

struct TextDocumentWillSave : public Notification<WillSaveTextDocumentParams> {
    explicit TextDocumentWillSave(WillSaveTextDocumentParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentWillSave const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WillSaveTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/willSave");
    return msg;
}

struct WorkspaceDidChangeWatchedFiles : public Notification<DidChangeWatchedFilesParams> {
    explicit WorkspaceDidChangeWatchedFiles(DidChangeWatchedFilesParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(WorkspaceDidChangeWatchedFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DidChangeWatchedFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "workspace/didChangeWatchedFiles");
    return msg;
}

struct TextDocumentPublishDiagnostics : public Notification<PublishDiagnosticsParams> {
    explicit TextDocumentPublishDiagnostics(PublishDiagnosticsParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json(TextDocumentPublishDiagnostics const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<PublishDiagnosticsParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "textDocument/publishDiagnostics");
    return msg;
}

struct $SetTrace : public Notification<SetTraceParams> {
    explicit $SetTrace(SetTraceParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json($SetTrace const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SetTraceParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "$/setTrace");
    return msg;
}

struct $LogTrace : public Notification<LogTraceParams> {
    explicit $LogTrace(LogTraceParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json($LogTrace const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<LogTraceParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "$/logTrace");
    return msg;
}

struct $CancelRequest : public Notification<CancelParams> {
    explicit $CancelRequest(CancelParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json($CancelRequest const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CancelParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "$/cancelRequest");
    return msg;
}

struct $Progress : public Notification<ProgressParams> {
    explicit $Progress(ProgressParams param) : Notification(std::move(param)) { }
};

template <>
inline JSONValue to_json($Progress const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ProgressParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "$/progress");
    return msg;
}


struct TextDocumentImplementation : public Request<ImplementationParams,std::variant<Definition, std::vector<DefinitionLink>, null>> {
    explicit TextDocumentImplementation(ImplementationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<Definition, std::vector<DefinitionLink>, null>>, JSONDecodeError> decode_response<TextDocumentImplementation>(JSONValue const& obj)
{
    return Response<std::variant<Definition, std::vector<DefinitionLink>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentImplementation const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ImplementationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/implementation");
    return msg;
}

struct TextDocumentTypeDefinition : public Request<TypeDefinitionParams,std::variant<Definition, std::vector<DefinitionLink>, null>> {
    explicit TextDocumentTypeDefinition(TypeDefinitionParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<Definition, std::vector<DefinitionLink>, null>>, JSONDecodeError> decode_response<TextDocumentTypeDefinition>(JSONValue const& obj)
{
    return Response<std::variant<Definition, std::vector<DefinitionLink>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentTypeDefinition const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<TypeDefinitionParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/typeDefinition");
    return msg;
}

struct WorkspaceWorkspaceFolders : public Request<null,std::variant<std::vector<WorkspaceFolder>, null>> {
    WorkspaceWorkspaceFolders() = default;
};

template<>
inline ErrorOr<Response<std::variant<std::vector<WorkspaceFolder>, null>>, JSONDecodeError> decode_response<WorkspaceWorkspaceFolders>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<WorkspaceFolder>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceWorkspaceFolders const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/workspaceFolders");
    return msg;
}

struct WorkspaceConfiguration : public Request<ConfigurationParams,std::vector<LSPAny>> {
    explicit WorkspaceConfiguration(ConfigurationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::vector<LSPAny>>, JSONDecodeError> decode_response<WorkspaceConfiguration>(JSONValue const& obj)
{
    return Response<std::vector<LSPAny>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceConfiguration const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ConfigurationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/configuration");
    return msg;
}

struct TextDocumentDocumentColor : public Request<DocumentColorParams,std::vector<ColorInformation>> {
    explicit TextDocumentDocumentColor(DocumentColorParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::vector<ColorInformation>>, JSONDecodeError> decode_response<TextDocumentDocumentColor>(JSONValue const& obj)
{
    return Response<std::vector<ColorInformation>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDocumentColor const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentColorParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/documentColor");
    return msg;
}

struct TextDocumentColorPresentation : public Request<ColorPresentationParams,std::vector<ColorPresentation>> {
    explicit TextDocumentColorPresentation(ColorPresentationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::vector<ColorPresentation>>, JSONDecodeError> decode_response<TextDocumentColorPresentation>(JSONValue const& obj)
{
    return Response<std::vector<ColorPresentation>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentColorPresentation const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ColorPresentationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/colorPresentation");
    return msg;
}

struct TextDocumentFoldingRange : public Request<FoldingRangeParams,std::variant<std::vector<FoldingRange>, null>> {
    explicit TextDocumentFoldingRange(FoldingRangeParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<FoldingRange>, null>>, JSONDecodeError> decode_response<TextDocumentFoldingRange>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<FoldingRange>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentFoldingRange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<FoldingRangeParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/foldingRange");
    return msg;
}

struct TextDocumentDeclaration : public Request<DeclarationParams,std::variant<Declaration, std::vector<DeclarationLink>, null>> {
    explicit TextDocumentDeclaration(DeclarationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<Declaration, std::vector<DeclarationLink>, null>>, JSONDecodeError> decode_response<TextDocumentDeclaration>(JSONValue const& obj)
{
    return Response<std::variant<Declaration, std::vector<DeclarationLink>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDeclaration const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DeclarationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/declaration");
    return msg;
}

struct TextDocumentSelectionRange : public Request<SelectionRangeParams,std::variant<std::vector<SelectionRange>, null>> {
    explicit TextDocumentSelectionRange(SelectionRangeParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<SelectionRange>, null>>, JSONDecodeError> decode_response<TextDocumentSelectionRange>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<SelectionRange>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentSelectionRange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SelectionRangeParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/selectionRange");
    return msg;
}

struct WindowWorkDoneProgressCreate : public Request<WorkDoneProgressCreateParams,null> {
    explicit WindowWorkDoneProgressCreate(WorkDoneProgressCreateParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WindowWorkDoneProgressCreate>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WindowWorkDoneProgressCreate const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WorkDoneProgressCreateParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "window/workDoneProgress/create");
    return msg;
}

struct TextDocumentPrepareCallHierarchy : public Request<CallHierarchyPrepareParams,std::variant<std::vector<CallHierarchyItem>, null>> {
    explicit TextDocumentPrepareCallHierarchy(CallHierarchyPrepareParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<CallHierarchyItem>, null>>, JSONDecodeError> decode_response<TextDocumentPrepareCallHierarchy>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<CallHierarchyItem>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentPrepareCallHierarchy const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CallHierarchyPrepareParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/prepareCallHierarchy");
    return msg;
}

struct CallHierarchyIncomingCalls : public Request<CallHierarchyIncomingCallsParams,std::variant<std::vector<CallHierarchyIncomingCall>, null>> {
    explicit CallHierarchyIncomingCalls(CallHierarchyIncomingCallsParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<CallHierarchyIncomingCall>, null>>, JSONDecodeError> decode_response<CallHierarchyIncomingCalls>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<CallHierarchyIncomingCall>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(CallHierarchyIncomingCalls const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CallHierarchyIncomingCallsParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "callHierarchy/incomingCalls");
    return msg;
}

struct CallHierarchyOutgoingCalls : public Request<CallHierarchyOutgoingCallsParams,std::variant<std::vector<CallHierarchyOutgoingCall>, null>> {
    explicit CallHierarchyOutgoingCalls(CallHierarchyOutgoingCallsParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<CallHierarchyOutgoingCall>, null>>, JSONDecodeError> decode_response<CallHierarchyOutgoingCalls>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<CallHierarchyOutgoingCall>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(CallHierarchyOutgoingCalls const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CallHierarchyOutgoingCallsParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "callHierarchy/outgoingCalls");
    return msg;
}

struct TextDocumentSemanticTokensFull : public Request<SemanticTokensParams,std::variant<SemanticTokens, null>> {
    explicit TextDocumentSemanticTokensFull(SemanticTokensParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<SemanticTokens, null>>, JSONDecodeError> decode_response<TextDocumentSemanticTokensFull>(JSONValue const& obj)
{
    return Response<std::variant<SemanticTokens, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentSemanticTokensFull const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SemanticTokensParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/semanticTokens/full");
    return msg;
}

struct TextDocumentSemanticTokensFullDelta : public Request<SemanticTokensDeltaParams,std::variant<SemanticTokens, SemanticTokensDelta, null>> {
    explicit TextDocumentSemanticTokensFullDelta(SemanticTokensDeltaParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<SemanticTokens, SemanticTokensDelta, null>>, JSONDecodeError> decode_response<TextDocumentSemanticTokensFullDelta>(JSONValue const& obj)
{
    return Response<std::variant<SemanticTokens, SemanticTokensDelta, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentSemanticTokensFullDelta const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SemanticTokensDeltaParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/semanticTokens/full/delta");
    return msg;
}

struct TextDocumentSemanticTokensRange : public Request<SemanticTokensRangeParams,std::variant<SemanticTokens, null>> {
    explicit TextDocumentSemanticTokensRange(SemanticTokensRangeParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<SemanticTokens, null>>, JSONDecodeError> decode_response<TextDocumentSemanticTokensRange>(JSONValue const& obj)
{
    return Response<std::variant<SemanticTokens, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentSemanticTokensRange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SemanticTokensRangeParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/semanticTokens/range");
    return msg;
}

struct WorkspaceSemanticTokensRefresh : public Request<null,null> {
    WorkspaceSemanticTokensRefresh() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WorkspaceSemanticTokensRefresh>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceSemanticTokensRefresh const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/semanticTokens/refresh");
    return msg;
}

struct WindowShowDocument : public Request<ShowDocumentParams,ShowDocumentResult> {
    explicit WindowShowDocument(ShowDocumentParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<ShowDocumentResult>, JSONDecodeError> decode_response<WindowShowDocument>(JSONValue const& obj)
{
    return Response<ShowDocumentResult>::decode_json(obj);
}

template<>
JSONValue to_json(WindowShowDocument const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ShowDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "window/showDocument");
    return msg;
}

struct TextDocumentLinkedEditingRange : public Request<LinkedEditingRangeParams,std::variant<LinkedEditingRanges, null>> {
    explicit TextDocumentLinkedEditingRange(LinkedEditingRangeParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<LinkedEditingRanges, null>>, JSONDecodeError> decode_response<TextDocumentLinkedEditingRange>(JSONValue const& obj)
{
    return Response<std::variant<LinkedEditingRanges, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentLinkedEditingRange const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<LinkedEditingRangeParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/linkedEditingRange");
    return msg;
}

struct WorkspaceWillCreateFiles : public Request<CreateFilesParams,std::variant<WorkspaceEdit, null>> {
    explicit WorkspaceWillCreateFiles(CreateFilesParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<WorkspaceEdit, null>>, JSONDecodeError> decode_response<WorkspaceWillCreateFiles>(JSONValue const& obj)
{
    return Response<std::variant<WorkspaceEdit, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceWillCreateFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CreateFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/willCreateFiles");
    return msg;
}

struct WorkspaceWillRenameFiles : public Request<RenameFilesParams,std::variant<WorkspaceEdit, null>> {
    explicit WorkspaceWillRenameFiles(RenameFilesParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<WorkspaceEdit, null>>, JSONDecodeError> decode_response<WorkspaceWillRenameFiles>(JSONValue const& obj)
{
    return Response<std::variant<WorkspaceEdit, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceWillRenameFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<RenameFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/willRenameFiles");
    return msg;
}

struct WorkspaceWillDeleteFiles : public Request<DeleteFilesParams,std::variant<WorkspaceEdit, null>> {
    explicit WorkspaceWillDeleteFiles(DeleteFilesParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<WorkspaceEdit, null>>, JSONDecodeError> decode_response<WorkspaceWillDeleteFiles>(JSONValue const& obj)
{
    return Response<std::variant<WorkspaceEdit, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceWillDeleteFiles const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DeleteFilesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/willDeleteFiles");
    return msg;
}

struct TextDocumentMoniker : public Request<MonikerParams,std::variant<std::vector<Moniker>, null>> {
    explicit TextDocumentMoniker(MonikerParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<Moniker>, null>>, JSONDecodeError> decode_response<TextDocumentMoniker>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<Moniker>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentMoniker const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<MonikerParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/moniker");
    return msg;
}

struct TextDocumentPrepareTypeHierarchy : public Request<TypeHierarchyPrepareParams,std::variant<std::vector<TypeHierarchyItem>, null>> {
    explicit TextDocumentPrepareTypeHierarchy(TypeHierarchyPrepareParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TypeHierarchyItem>, null>>, JSONDecodeError> decode_response<TextDocumentPrepareTypeHierarchy>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TypeHierarchyItem>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentPrepareTypeHierarchy const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<TypeHierarchyPrepareParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/prepareTypeHierarchy");
    return msg;
}

struct TypeHierarchySupertypes : public Request<TypeHierarchySupertypesParams,std::variant<std::vector<TypeHierarchyItem>, null>> {
    explicit TypeHierarchySupertypes(TypeHierarchySupertypesParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TypeHierarchyItem>, null>>, JSONDecodeError> decode_response<TypeHierarchySupertypes>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TypeHierarchyItem>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TypeHierarchySupertypes const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<TypeHierarchySupertypesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "typeHierarchy/supertypes");
    return msg;
}

struct TypeHierarchySubtypes : public Request<TypeHierarchySubtypesParams,std::variant<std::vector<TypeHierarchyItem>, null>> {
    explicit TypeHierarchySubtypes(TypeHierarchySubtypesParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TypeHierarchyItem>, null>>, JSONDecodeError> decode_response<TypeHierarchySubtypes>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TypeHierarchyItem>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TypeHierarchySubtypes const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<TypeHierarchySubtypesParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "typeHierarchy/subtypes");
    return msg;
}

struct TextDocumentInlineValue : public Request<InlineValueParams,std::variant<std::vector<InlineValue>, null>> {
    explicit TextDocumentInlineValue(InlineValueParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<InlineValue>, null>>, JSONDecodeError> decode_response<TextDocumentInlineValue>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<InlineValue>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentInlineValue const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<InlineValueParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/inlineValue");
    return msg;
}

struct WorkspaceInlineValueRefresh : public Request<null,null> {
    WorkspaceInlineValueRefresh() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WorkspaceInlineValueRefresh>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceInlineValueRefresh const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/inlineValue/refresh");
    return msg;
}

struct TextDocumentInlayHint : public Request<InlayHintParams,std::variant<std::vector<InlayHint>, null>> {
    explicit TextDocumentInlayHint(InlayHintParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<InlayHint>, null>>, JSONDecodeError> decode_response<TextDocumentInlayHint>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<InlayHint>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentInlayHint const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<InlayHintParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/inlayHint");
    return msg;
}

struct InlayHintResolve : public Request<InlayHint,InlayHint> {
    explicit InlayHintResolve(InlayHint param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<InlayHint>, JSONDecodeError> decode_response<InlayHintResolve>(JSONValue const& obj)
{
    return Response<InlayHint>::decode_json(obj);
}

template<>
JSONValue to_json(InlayHintResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<InlayHint>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "inlayHint/resolve");
    return msg;
}

struct WorkspaceInlayHintRefresh : public Request<null,null> {
    WorkspaceInlayHintRefresh() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WorkspaceInlayHintRefresh>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceInlayHintRefresh const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/inlayHint/refresh");
    return msg;
}

struct TextDocumentDiagnostic : public Request<DocumentDiagnosticParams,DocumentDiagnosticReport> {
    explicit TextDocumentDiagnostic(DocumentDiagnosticParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<DocumentDiagnosticReport>, JSONDecodeError> decode_response<TextDocumentDiagnostic>(JSONValue const& obj)
{
    return Response<DocumentDiagnosticReport>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDiagnostic const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentDiagnosticParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/diagnostic");
    return msg;
}

struct WorkspaceDiagnostic : public Request<WorkspaceDiagnosticParams,WorkspaceDiagnosticReport> {
    explicit WorkspaceDiagnostic(WorkspaceDiagnosticParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<WorkspaceDiagnosticReport>, JSONDecodeError> decode_response<WorkspaceDiagnostic>(JSONValue const& obj)
{
    return Response<WorkspaceDiagnosticReport>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceDiagnostic const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WorkspaceDiagnosticParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/diagnostic");
    return msg;
}

struct WorkspaceDiagnosticRefresh : public Request<null,null> {
    WorkspaceDiagnosticRefresh() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WorkspaceDiagnosticRefresh>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceDiagnosticRefresh const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/diagnostic/refresh");
    return msg;
}

struct ClientRegisterCapability : public Request<RegistrationParams,null> {
    explicit ClientRegisterCapability(RegistrationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<ClientRegisterCapability>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(ClientRegisterCapability const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<RegistrationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "client/registerCapability");
    return msg;
}

struct ClientUnregisterCapability : public Request<UnregistrationParams,null> {
    explicit ClientUnregisterCapability(UnregistrationParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<ClientUnregisterCapability>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(ClientUnregisterCapability const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<UnregistrationParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "client/unregisterCapability");
    return msg;
}

struct Initialize : public Request<InitializeParams,InitializeResult> {
    explicit Initialize(InitializeParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<InitializeResult>, JSONDecodeError> decode_response<Initialize>(JSONValue const& obj)
{
    return Response<InitializeResult>::decode_json(obj);
}

template<>
JSONValue to_json(Initialize const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<InitializeParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "initialize");
    return msg;
}

struct Shutdown : public Request<null,null> {
    Shutdown() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<Shutdown>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(Shutdown const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "shutdown");
    return msg;
}

struct WindowShowMessageRequest : public Request<ShowMessageRequestParams,std::variant<MessageActionItem, null>> {
    explicit WindowShowMessageRequest(ShowMessageRequestParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<MessageActionItem, null>>, JSONDecodeError> decode_response<WindowShowMessageRequest>(JSONValue const& obj)
{
    return Response<std::variant<MessageActionItem, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WindowShowMessageRequest const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ShowMessageRequestParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "window/showMessageRequest");
    return msg;
}

struct TextDocumentWillSaveWaitUntil : public Request<WillSaveTextDocumentParams,std::variant<std::vector<TextEdit>, null>> {
    explicit TextDocumentWillSaveWaitUntil(WillSaveTextDocumentParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TextEdit>, null>>, JSONDecodeError> decode_response<TextDocumentWillSaveWaitUntil>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TextEdit>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentWillSaveWaitUntil const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WillSaveTextDocumentParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/willSaveWaitUntil");
    return msg;
}

struct TextDocumentCompletion : public Request<CompletionParams,std::variant<std::vector<CompletionItem>, CompletionList, null>> {
    explicit TextDocumentCompletion(CompletionParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<CompletionItem>, CompletionList, null>>, JSONDecodeError> decode_response<TextDocumentCompletion>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<CompletionItem>, CompletionList, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentCompletion const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CompletionParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/completion");
    return msg;
}

struct CompletionItemResolve : public Request<CompletionItem,CompletionItem> {
    explicit CompletionItemResolve(CompletionItem param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<CompletionItem>, JSONDecodeError> decode_response<CompletionItemResolve>(JSONValue const& obj)
{
    return Response<CompletionItem>::decode_json(obj);
}

template<>
JSONValue to_json(CompletionItemResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CompletionItem>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "completionItem/resolve");
    return msg;
}

struct TextDocumentHover : public Request<HoverParams,std::variant<Hover, null>> {
    explicit TextDocumentHover(HoverParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<Hover, null>>, JSONDecodeError> decode_response<TextDocumentHover>(JSONValue const& obj)
{
    return Response<std::variant<Hover, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentHover const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<HoverParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/hover");
    return msg;
}

struct TextDocumentSignatureHelp : public Request<SignatureHelpParams,std::variant<SignatureHelp, null>> {
    explicit TextDocumentSignatureHelp(SignatureHelpParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<SignatureHelp, null>>, JSONDecodeError> decode_response<TextDocumentSignatureHelp>(JSONValue const& obj)
{
    return Response<std::variant<SignatureHelp, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentSignatureHelp const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<SignatureHelpParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/signatureHelp");
    return msg;
}

struct TextDocumentDefinition : public Request<DefinitionParams,std::variant<Definition, std::vector<DefinitionLink>, null>> {
    explicit TextDocumentDefinition(DefinitionParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<Definition, std::vector<DefinitionLink>, null>>, JSONDecodeError> decode_response<TextDocumentDefinition>(JSONValue const& obj)
{
    return Response<std::variant<Definition, std::vector<DefinitionLink>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDefinition const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DefinitionParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/definition");
    return msg;
}

struct TextDocumentReferences : public Request<ReferenceParams,std::variant<std::vector<Location>, null>> {
    explicit TextDocumentReferences(ReferenceParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<Location>, null>>, JSONDecodeError> decode_response<TextDocumentReferences>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<Location>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentReferences const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ReferenceParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/references");
    return msg;
}

struct TextDocumentDocumentHighlight : public Request<DocumentHighlightParams,std::variant<std::vector<DocumentHighlight>, null>> {
    explicit TextDocumentDocumentHighlight(DocumentHighlightParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<DocumentHighlight>, null>>, JSONDecodeError> decode_response<TextDocumentDocumentHighlight>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<DocumentHighlight>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDocumentHighlight const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentHighlightParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/documentHighlight");
    return msg;
}

struct TextDocumentDocumentSymbol : public Request<DocumentSymbolParams,std::variant<std::vector<SymbolInformation>, std::vector<DocumentSymbol>, null>> {
    explicit TextDocumentDocumentSymbol(DocumentSymbolParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<SymbolInformation>, std::vector<DocumentSymbol>, null>>, JSONDecodeError> decode_response<TextDocumentDocumentSymbol>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<SymbolInformation>, std::vector<DocumentSymbol>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDocumentSymbol const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentSymbolParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/documentSymbol");
    return msg;
}

struct TextDocumentCodeAction : public Request<CodeActionParams,std::variant<std::vector<std::variant<Command, CodeAction>>, null>> {
    explicit TextDocumentCodeAction(CodeActionParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<std::variant<Command, CodeAction>>, null>>, JSONDecodeError> decode_response<TextDocumentCodeAction>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<std::variant<Command, CodeAction>>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentCodeAction const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CodeActionParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/codeAction");
    return msg;
}

struct CodeActionResolve : public Request<CodeAction,CodeAction> {
    explicit CodeActionResolve(CodeAction param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<CodeAction>, JSONDecodeError> decode_response<CodeActionResolve>(JSONValue const& obj)
{
    return Response<CodeAction>::decode_json(obj);
}

template<>
JSONValue to_json(CodeActionResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CodeAction>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "codeAction/resolve");
    return msg;
}

struct WorkspaceSymbolRequest : public Request<WorkspaceSymbolParams,std::variant<std::vector<SymbolInformation>, std::vector<WorkspaceSymbol>, null>> {
    explicit WorkspaceSymbolRequest(WorkspaceSymbolParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<SymbolInformation>, std::vector<WorkspaceSymbol>, null>>, JSONDecodeError> decode_response<WorkspaceSymbolRequest>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<SymbolInformation>, std::vector<WorkspaceSymbol>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceSymbolRequest const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WorkspaceSymbolParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/symbol");
    return msg;
}

struct WorkspaceSymbolResolve : public Request<WorkspaceSymbol,WorkspaceSymbol> {
    explicit WorkspaceSymbolResolve(WorkspaceSymbol param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<WorkspaceSymbol>, JSONDecodeError> decode_response<WorkspaceSymbolResolve>(JSONValue const& obj)
{
    return Response<WorkspaceSymbol>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceSymbolResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<WorkspaceSymbol>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspaceSymbol/resolve");
    return msg;
}

struct TextDocumentCodeLens : public Request<CodeLensParams,std::variant<std::vector<CodeLens>, null>> {
    explicit TextDocumentCodeLens(CodeLensParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<CodeLens>, null>>, JSONDecodeError> decode_response<TextDocumentCodeLens>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<CodeLens>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentCodeLens const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CodeLensParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/codeLens");
    return msg;
}

struct CodeLensResolve : public Request<CodeLens,CodeLens> {
    explicit CodeLensResolve(CodeLens param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<CodeLens>, JSONDecodeError> decode_response<CodeLensResolve>(JSONValue const& obj)
{
    return Response<CodeLens>::decode_json(obj);
}

template<>
JSONValue to_json(CodeLensResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<CodeLens>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "codeLens/resolve");
    return msg;
}

struct WorkspaceCodeLensRefresh : public Request<null,null> {
    WorkspaceCodeLensRefresh() = default;
};

template<>
inline ErrorOr<Response<null>, JSONDecodeError> decode_response<WorkspaceCodeLensRefresh>(JSONValue const& obj)
{
    return Response<null>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceCodeLensRefresh const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<null>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/codeLens/refresh");
    return msg;
}

struct TextDocumentDocumentLink : public Request<DocumentLinkParams,std::variant<std::vector<DocumentLink>, null>> {
    explicit TextDocumentDocumentLink(DocumentLinkParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<DocumentLink>, null>>, JSONDecodeError> decode_response<TextDocumentDocumentLink>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<DocumentLink>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentDocumentLink const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentLinkParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/documentLink");
    return msg;
}

struct DocumentLinkResolve : public Request<DocumentLink,DocumentLink> {
    explicit DocumentLinkResolve(DocumentLink param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<DocumentLink>, JSONDecodeError> decode_response<DocumentLinkResolve>(JSONValue const& obj)
{
    return Response<DocumentLink>::decode_json(obj);
}

template<>
JSONValue to_json(DocumentLinkResolve const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentLink>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "documentLink/resolve");
    return msg;
}

struct TextDocumentFormatting : public Request<DocumentFormattingParams,std::variant<std::vector<TextEdit>, null>> {
    explicit TextDocumentFormatting(DocumentFormattingParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TextEdit>, null>>, JSONDecodeError> decode_response<TextDocumentFormatting>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TextEdit>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentFormatting const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentFormattingParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/formatting");
    return msg;
}

struct TextDocumentRangeFormatting : public Request<DocumentRangeFormattingParams,std::variant<std::vector<TextEdit>, null>> {
    explicit TextDocumentRangeFormatting(DocumentRangeFormattingParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TextEdit>, null>>, JSONDecodeError> decode_response<TextDocumentRangeFormatting>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TextEdit>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentRangeFormatting const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentRangeFormattingParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/rangeFormatting");
    return msg;
}

struct TextDocumentOnTypeFormatting : public Request<DocumentOnTypeFormattingParams,std::variant<std::vector<TextEdit>, null>> {
    explicit TextDocumentOnTypeFormatting(DocumentOnTypeFormattingParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<std::vector<TextEdit>, null>>, JSONDecodeError> decode_response<TextDocumentOnTypeFormatting>(JSONValue const& obj)
{
    return Response<std::variant<std::vector<TextEdit>, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentOnTypeFormatting const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<DocumentOnTypeFormattingParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/onTypeFormatting");
    return msg;
}

struct TextDocumentRename : public Request<RenameParams,std::variant<WorkspaceEdit, null>> {
    explicit TextDocumentRename(RenameParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<WorkspaceEdit, null>>, JSONDecodeError> decode_response<TextDocumentRename>(JSONValue const& obj)
{
    return Response<std::variant<WorkspaceEdit, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentRename const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<RenameParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/rename");
    return msg;
}

struct TextDocumentPrepareRename : public Request<PrepareRenameParams,std::variant<PrepareRenameResult, null>> {
    explicit TextDocumentPrepareRename(PrepareRenameParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<PrepareRenameResult, null>>, JSONDecodeError> decode_response<TextDocumentPrepareRename>(JSONValue const& obj)
{
    return Response<std::variant<PrepareRenameResult, null>>::decode_json(obj);
}

template<>
JSONValue to_json(TextDocumentPrepareRename const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<PrepareRenameParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "textDocument/prepareRename");
    return msg;
}

struct WorkspaceExecuteCommand : public Request<ExecuteCommandParams,std::variant<LSPAny, null>> {
    explicit WorkspaceExecuteCommand(ExecuteCommandParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<std::variant<LSPAny, null>>, JSONDecodeError> decode_response<WorkspaceExecuteCommand>(JSONValue const& obj)
{
    return Response<std::variant<LSPAny, null>>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceExecuteCommand const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ExecuteCommandParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/executeCommand");
    return msg;
}

struct WorkspaceApplyEdit : public Request<ApplyWorkspaceEditParams,ApplyWorkspaceEditResult> {
    explicit WorkspaceApplyEdit(ApplyWorkspaceEditParams param) : Request(std::move(param)) { }
};

template<>
inline ErrorOr<Response<ApplyWorkspaceEditResult>, JSONDecodeError> decode_response<WorkspaceApplyEdit>(JSONValue const& obj)
{
    return Response<ApplyWorkspaceEditResult>::decode_json(obj);
}

template<>
JSONValue to_json(WorkspaceApplyEdit const& obj)
{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<ApplyWorkspaceEditParams>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "workspace/applyEdit");
    return msg;
}

} // scratch::lsp
