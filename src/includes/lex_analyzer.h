#ifndef lex_analyzer

#include <vector>
#include <string>
using std::vector;
using std::string;

/**
 * 读取指定路径的文件进行词法分析，并保存到指定的vector中
 * @param in_path 输入文件路径
 * @param out 存放tokens的vector
 */
bool analyze_lex(const string &in_path, vector<string> &out_vec);

#endif