#ifndef string_utils

#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * 去除字符串左边的空格
 * @param s 源字符串
 */
static inline void ltrim(string &s);
/**
 * 去除字符串右边的空格
 * @param s 源字符串
 */
static inline void rtrim(string &s);
/**
 * 去除字符串两边的空格
 * @param s 源字符串
 */
static inline void trim(string &s);
/**
 * 分割字符串
 * @param s 待分割字符串
 * @param delimiters （可选）分隔符，默认为空格
 */
vector<string> split_string(const string &s, const string &delimiters = " ");

#endif