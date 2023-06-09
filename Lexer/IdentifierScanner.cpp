/*
 * Copyright (c) 2021, Jan de Visser <jan@finiandarcy.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Tokenizer.h"

namespace Obelix {

IdentifierScanner::IdentifierScanner()
    : Scanner(15)
{
}

IdentifierScanner::IdentifierScanner(Config config)
    : Scanner(15)
    , m_config(std::move(config))
{
}

bool IdentifierScanner::filter_character(Tokenizer& tokenizer, int ch) const {
    bool ret;

    if (!ch)
        return false;

    auto filter_against = [ch](auto filter_against, auto alpha_class, auto digits_allowed) {
        if (isalpha(ch)) {
            switch (alpha_class) {
            case IdentifierCharacterClass::NoAlpha:
                return false;
            case IdentifierCharacterClass::OnlyLower:
                return (bool) islower(ch);
            case IdentifierCharacterClass::OnlyUpper:
                return (bool) isupper(ch);
            default:
                return true;
            }
        } else if (isdigit(ch)) {
            return digits_allowed;
        } else if (!filter_against.empty()) {
            return filter_against.find_first_of(ch) != std::string::npos;
        }
        return true;
    };
    ret = filter_against(m_config.filter, m_config.alpha, m_config.digits);

    if (ret && tokenizer.current_token().empty()) {
        ret = filter_against(m_config.starts_with, m_config.startswith_alpha, m_config.startswith_digits);
    }
    return ret;
}

void IdentifierScanner::match(Tokenizer& tokenizer)
{
    int ch;
    bool identifier_found { false };

    for (ch = tokenizer.peek(); filter_character(tokenizer, ch); ch = tokenizer.peek()) {
        identifier_found = true;
        switch (m_config.alpha) {
        case IdentifierCharacterClass::CaseSensitive:
        case IdentifierCharacterClass::OnlyLower:
        case IdentifierCharacterClass::OnlyUpper:
            tokenizer.push();
            break;
        case IdentifierCharacterClass::FoldToUpper:
            tokenizer.push_as(toupper(ch));
            break;
        case IdentifierCharacterClass::FoldToLower:
            tokenizer.push_as(tolower(ch));
            break;
        default:
            break;
        }
    }
    if (identifier_found)
        tokenizer.accept(m_config.code);
}

}
