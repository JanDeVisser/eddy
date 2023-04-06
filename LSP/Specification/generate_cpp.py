#!/usr/bin/python3

import json
import sys

with open('metaModel.json') as fd:
    model = json.load(fd)

emitted_structures = set()
emitted_types = []
structures = {}
aliases = {}
enums = {}
anon_count = 0
current = set()


def emit_forwards():
    for s in model["structures"]:
        print(f"struct {s['name']};")
    print()


def render_type(optional, typedesc):
    if 'rendered' in typedesc:
        return typedesc['rendered']
    ret: str = ""
    if optional:
        ret = "std::optional<"
    if typedesc["kind"] == "base" or typedesc["kind"] == "reference" or typedesc["kind"] == "literal":
        ret += f"{typedesc['name']}"
    if typedesc["kind"] == "array":
        ret += "std::vector<"
        ret += render_type(False, typedesc['element'])
        ret += ">"
    if typedesc["kind"] == "map":
        ret += f"std::map<"
        ret += render_type(False, typedesc['key'])
        ret += ", "
        ret += render_type(False, typedesc['value'])
        ret += ">"
    if typedesc['kind'] == "or":
        ret += "std::variant<"
        first_item = True
        for item in typedesc['items']:
            if not first_item:
                ret += ", "
            first_item = False
            ret += render_type(False, item)
        ret += ">"
    if typedesc['kind'] == "stringLiteral":
        ret += "std::string"
    if typedesc['kind'] == "tuple":
        if len(typedesc['items']) != 2:
            print("Tuple with nr elements != 2", file=sys.stderr)
            exit(1)
        ret += f"std::pair<"
        ret += render_type(False, typedesc['items'][0])
        ret += ", "
        ret += render_type(False, typedesc['items'][1])
        ret += ">"
    if optional:
        ret += ">"
    typedesc['rendered'] = ret
    return ret


def emit_type(optional, typedesc):
    print(render_type(optional, typedesc), end="")


def type_initializer(optional, typedesc):
    if 'initializer' in typedesc:
        return typedesc['initializer']
    ret: str = ""
    if optional:
        ret += " {}"
    else:
        if typedesc["kind"] == "base":
            if typedesc["name"] == 'integer' or typedesc["name"] == 'uinteger':
                ret += "{ 0 }"
            if typedesc["name"] == 'boolean':
                ret += "{ false }"
        if typedesc["kind"] == "reference" or typedesc["kind"] == "literal":
            pass
        if typedesc["kind"] == "array":
            ret += " {}"
        if typedesc["kind"] == "map":
            ret += " {}"
        if typedesc['kind'] == "or":
            ret += " {}"
        if typedesc['kind'] == "stringLiteral":
            ret += f' {{ "{typedesc["value"]}" }}'
    typedesc["initializer"] = ret
    return ret


def emit_properties(s):
    for prop in s["properties"]:
        # Hack. SelectionRange contains an optional parent range. That doesn't work.
        if 'ignore' in prop and prop['ignore']:
            continue
        prop['ignore'] = False
        if prop['type']['kind'] == 'reference' and prop['type']['name'] == s['name']:
            prop['ignore'] = True
            continue

        optional = "optional" in prop and prop["optional"]
        print(f"    {render_type(optional, prop['type'])} {prop['name']} {type_initializer(optional, prop['type'])};")


def struct_to_json(s):
    name = s['name']
    print("template<>")
    print(f"inline JSONValue to_json({name} const& obj)")
    print("{")
    print("    JSONValue ret = JSONValue::object();")
    if "extends" in s:
        for base_class in s["extends"]:
            print(f"    ret.merge(to_json<{base_class['name']}>(obj));")
    if "mixins" in s:
        for mixin in s["mixins"]:
            print(f"    ret.merge(to_json<{mixin['name']}>(obj));")
    for prop in s["properties"]:
        if prop['ignore']:
            continue
        prop_name = prop['name']
        print(f'    set(ret, "{prop_name}", obj.{prop_name});')
    print(f"    return ret;")
    print("}")
    print()


def emit_structure(name):
    if name in emitted_structures or name in current:
        return
    if name in aliases:
        emit_alias(name)
        return
    if name in structures:
        s = structures[name]
    else:
        print(f"Unknown struct {name}", file=sys.stderr)
        return
    current.add(name)
    if "extends" in s:
        for base_class in s["extends"]:
            emit_structure(base_class["name"])
    if "mixins" in s:
        for mixin in s["mixins"]:
            emit_structure(mixin["name"])
    for prop in s["properties"]:
        emit_references(prop['type'])
    print(f"struct {s['name']}", end="")
    first = True
    if "extends" in s:
        for base_class in s["extends"]:
            if first:
                print(" : ", end="")
                first = False
            else:
                print(", ", end="")
            print(f"public {base_class['name']}", end="")
    if "mixins" in s:
        for mixin in s["mixins"]:
            if first:
                print(" : ", end="")
                first = False
            else:
                print(", ", end="")
            print(f"public {mixin['name']}", end="")
    print(" {")
    emit_properties(s)
    print("};")
    print()
    struct_to_json(s)
    decode(s)
    emitted_structures.add(name)
    emitted_types.append(('S', name))
    current.remove(name)


def emit_references(typedesc):
    kind = typedesc['kind']
    if kind == "reference":
        if typedesc['name'] in structures:
            emit_structure(typedesc['name'])
        if typedesc['name'] in enums:
            emit_enumeration(typedesc['name'])
        if typedesc['name'] in aliases:
            emit_alias(typedesc['name'])
    if kind == "array":
        emit_references(typedesc['element'])
    if kind == "map":
        emit_references(typedesc['key'])
        emit_references(typedesc['value'])
    if kind == "or":
        for item in typedesc['items']:
            emit_references(item)
    if kind == "literal":
        global anon_count
        typedesc['name'] = f"anon_{anon_count}"
        anon_count += 1
        typedesc['properties'] = typedesc['value']['properties']
        structures[typedesc['name']] = typedesc
        for prop in typedesc["properties"]:
            emit_references(prop['type'])
        emit_structure(typedesc['name'])


def emit_alias(name):
    if name in emitted_structures or name.startswith('LSP'):
        return
    alias = aliases[name]
    emit_references(alias["type"])
    print(f'using {name} = {render_type("optional" in alias and alias["optional"], alias["type"])};')
    emitted_structures.add(name)
    emitted_types.append(('A', name))


def emit_aliases():
    print()
    for a in aliases:
        emit_alias(a)
    print()


def emit_enumeration(name):
    if name in emitted_structures:
        return
    enum = enums[name]
    if enum['type']['kind'] != 'base':
        print(f"Enum {name} has kind {enum['type']['kind']}", file=sys.stderr)
        exit(1)
    t = enum['type']['name']
    print(f"enum class {enum['name']} {{")
    for value in enum['values']:
        value['cname'] = value['name'].capitalize()
        print(f"    {value['cname']}", end="")
        if t == "integer" or t == "uinteger":
            print(f" = {value['value']}", end="")
        print(",")
    print("};")
    print()
    if t == 'string':
        print(f"std::string_view string_view({name} value)")
        print("{")
        print(f"    switch (value) {{")
        for value in enum['values']:
            print(f'    case {name}::{value["cname"]}: "{value["value"]}"sv;')
        print('    default: fatal("Unreachable");')
        print("    }")
        print("}")
        print()
    print("template<>")
    print(f"inline JSONValue to_json({name} const& obj)")
    print("{")
    if t == "string":
        print(f"    return {{ string_view(obj) }};")
    if t == "integer" or t == "uinteger":
        print(f"    return {{ static_cast<{t}>(obj) }};")
    print("}")
    print()
    print(
f"""template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, {name}& target)
{{""")
    if t == "string":
        print(f"    if (!value.is_string())")
        print(f'         return JSONDecodeError {{ JSONDecodeError::Code::TypeMismatch, "" }};')
        for value in enum['values']:
            print(f'    if (value.to_string() == "{value["value"]}") target = {name}::{value["cname"]};')
    if t == "integer" or t == "uinteger":
        print(f"    if (!value.is_integer())")
        print(f'         return JSONDecodeError {{ JSONDecodeError::Code::TypeMismatch, "" }};')
        print(f"    target = static_cast<{name}>(*(value.to_int<{t}>()));")
    print("    return {};")
    print("}")
    print()

    emitted_structures.add(name)
    emitted_types.append(('E', name))


def emit_enumerations():
    for e in enums:
        emit_enumeration(e)
    print()


def emit_structures():
    for s in model["structures"]:
        emit_structure(s["name"])


def decode_properties(s):
    if "extends" in s:
        for base_class in s["extends"]:
            decode_properties(structures[base_class['name']])
    if "mixins" in s:
        for mixin in s["mixins"]:
            decode_properties(structures[mixin['name']])
    for prop in s["properties"]:
        if prop['ignore']:
            continue
        prop_name = prop['name']
        # kind = prop['type']['kind']
        # print(f'        TRY_RETURN(decode<{prop["type"]["name"]}>(msg, "{prop_name}", result.{prop_name}));')
        print(f'    TRY_RETURN(decode(value, "{prop_name}", target.{prop_name}));')


def decode(s):
    name = s['name']
    print(
f"""template <>
inline ErrorOr<void,JSONDecodeError> decode_value(JSONValue const& value, {name}& target)
{{
    if (!value.is_object())
        return JSONDecodeError {{ JSONDecodeError::Code::TypeMismatch, "{name}" }};
""")
    decode_properties(s)
    print(f"    return {{}};")
    print(f"}}")
    print()


def notifications():
    print()
    for notification in model["notifications"]:
        method: str = notification['method']
        parts = method.split("/")
        name = "".join(p[0].upper() + p[1:] for p in parts)
        notification['name'] = name
        if "params" not in notification:
            notification['params'] = { 'rendered': 'null' }
            print(f"struct {name} : public Notification<null> {{")
            print(f'    {name}() = default;')
        else:
            print(f"struct {name} : public Notification<{render_type(False, notification['params'])}> {{")
            print(f"    explicit {name}({render_type(False, notification['params'])} param) : Notification(std::move(param)) {{ }}")
        print("};")
        print(f"""
template <>
inline JSONValue to_json({name} const& obj)
{{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<{render_type(False, notification['params'])}>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("method", "{notification['method']}");
    return msg;
}}
""")


def requests():
    print()
    for request in model["requests"]:
        method: str = request['method']
        parts = method.split("/")
        name = "".join(p[0].upper() + p[1:] for p in parts)
        if name in structures or name in aliases or name in enums:
            name = name + "Request"
        request['name'] = name
        if "params" not in request:
            request['params'] = {'rendered': 'null'}
            print(f"struct {name} : public Request<null,{render_type(False, request['result'])}> {{")
            print(f'    {name}() = default;')
        else:
            print(f"struct {name} : public Request<{render_type(False, request['params'])},{render_type(False, request['result'])}> {{")
            print(f"    explicit {name}({render_type(False, request['params'])} param) : Request(std::move(param)) {{ }}")
        print("};")
        print(f"""
template<>
inline ErrorOr<Response<{render_type(False, request['result'])}>, JSONDecodeError> decode_response<{name}>(JSONValue const& obj)
{{
    return Response<{render_type(False, request['result'])}>::decode_json(obj);
}}""")
        print(f"""
template<>
JSONValue to_json({name} const& obj)
{{
    auto msg = JSONValue::object();
    msg.set("jsonrpc", JSONValue("2.0"));
    auto param = to_json<{render_type(False, request['params'])}>(obj.parameter());
    if (!param.is_null())
        msg.set("params", param);
    msg.set("id", obj.id());
    msg.set("method", "{request['method']}");
    return msg;
}}
""")


def header():
    print("""/**
 * Copyright (c) 2023, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 *
 * THIS IS GENERATED CODE. DO NOT MODIFY.
 */
""")

    print("#pragma once")
    print()
    print("#include <map>")
    print("#include <optional>")
    print("#include <variant>")
    print("#include <vector>")
    print()
    print("#include <LSP/Message.h>")
    print()
    print("namespace scratch::lsp {")
    print()


def footer():
    print("} // scratch::lsp")
    print()


header()
# emit_forwards()

for enum in model['enumerations']:
    enums[enum['name']] = enum
for structure in model["structures"]:
    structures[structure["name"]] = structure
for alias in model['typeAliases']:
    aliases[alias['name']] = alias

emit_enumerations()
emit_aliases()
emit_structures()
notifications()
requests()
footer()
