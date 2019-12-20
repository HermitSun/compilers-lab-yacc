#ifndef enums

#if defined(__linux__)
#define ENTER_LENGTH 1
#elif defined(_WIN32)
#define ENTER_LENGTH 2
#endif

#include <set>
#include <string>
using std::set;
using std::string;

// “所有”的字符
const set<char> allchar = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                           'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                           'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                           'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                           '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                           '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-',
                           '=', '`', '~', '{', '}', '[', ']', ':', ';', '\'', ',', '.', '<',
                           '>', '?', '/', '\\', '|', ' ', '"'};
// 字符串中的字符（不包括双引号"）
const set<char> stringchar = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                              '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '-',
                              '=', '`', '~', '{', '}', '[', ']', ':', ';', '\'', ',', '.', '<',
                              '>', '?', '/', '\\', '|', ' '};
// 字母
const set<char> letter = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
                          'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                          'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// 数字
const set<char> digit = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
// 操作符
const set<string> OPERATOR = {"+", "-", "*", "/", "(", ")", "<", ">", "<=", ">=", "==", "!=",
                              "=", "[", "]", ".", "\\"};
// 分隔符
const set<char> SEPARATOR = {',', ';', '{', '}'};
// 注释
const set<char> COMMENT = {'/', '\n'};
// 控制
const set<string> CONTROL = {"if", "else", "while", "break", "continue", "return"};
// 模块
const set<string> MODULE = {"import", "export"};
// 异常
const set<string> EXCEPTION = {"try", "catch", "throw"};
// 关键字
const set<string> KEYWORD = {
    "number", "string", "function", "void",
    "try", "catch", "throw",
    "if", "else", "while", "break", "continue", "return",
    "import", "export"};

// FA具有的状态
enum FA_STATES
{
    STATE_I0 = 0,
    STATE_I1 = 1,
    STATE_I3 = 3,
    STATE_I4 = 4,
    STATE_I6 = 6,
    STATE_I12 = 12,
    STATE_I15 = 15,
    STATE_I18 = 18,
    STATE_I19 = 19,
    STATE_I24 = 24,
    STATE_I25 = 25
};

#endif