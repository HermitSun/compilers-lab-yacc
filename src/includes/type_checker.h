#ifndef type_checker

#include <string>
using std::string;

/**
 * 判断是否是合法字符
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_char(const char &c);
/**
 * 判断是否是字符串中的字符
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_stringchar(const char &c);
/**
 * 判断是否是字母
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_letter(const char &c);
/**
 * 判断是否是数字
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_digit(const char &c);
/**
 * 判断是否是操作符
 * @param s 待判断字符串
 * @return true是，false否
 */
bool is_operator(const string &s);
/**
 * 判断是否是分隔符
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_separator(const char &c);
/**
 * 判断是否是关键字
 * @param s 待判断字符串
 * @return true是，false否
 */
bool is_keyword(const string &s);
/**
 * 判断是否是空白符
 * @param c 待判断字符
 * @return true是，false否
 */
bool is_whitespace(const char &c);

#endif