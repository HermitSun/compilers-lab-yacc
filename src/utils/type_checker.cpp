#include "../includes/type_checker.h"
#include "../includes/lex_enums.h"

bool is_char(const char &c)
{
    return allchar.find(c) != allchar.end();
}

bool is_stringchar(const char &c)
{
    return stringchar.find(c) != stringchar.end();
}

bool is_letter(const char &c)
{
    return letter.find(c) != letter.end();
}

bool is_digit(const char &c)
{
    return digit.find(c) != digit.end();
}

bool is_operator(const string &s)
{
    return OPERATOR.find(s) != OPERATOR.end();
}

bool is_separator(const char &c)
{
    return SEPARATOR.find(c) != SEPARATOR.end();
}

bool is_keyword(const string &s)
{
    return KEYWORD.find(s) != KEYWORD.end();
}

bool is_whitespace(const char &c)
{
    return c == ' ' ||
           c == '\t' ||
           c == '\n' ||
           c == '\r' ||
           c == '\f';
}