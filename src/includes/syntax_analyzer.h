#ifndef syntax_analyzer

#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * 读取tokens进行语法分析
 * @param tokens 存放tokens的vector
 * @return true成功，false出现错误
 */
bool analyze_syntax(vector<string> &tokens);

#endif