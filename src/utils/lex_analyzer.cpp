#include <fstream>
#include <iostream>
#include <string>
#include <fcntl.h>
#include "../includes/lex_analyzer.h"
#include "../includes/type_checker.h"
#include "../includes/lex_enums.h"
using namespace std;

// 函数声明
void trim_token(string &token, const char &mode);
void reset_FA(vector<string> &out_vec,
              string &current_token,
              string &current_token_type,
              FA_STATES &current_state);
void reset_FA_and_trim(ifstream &in_file,
                       vector<string> &out_vec,
                       string &current_token,
                       string &current_token_type,
                       FA_STATES &current_state);

bool analyze_lex(const string &in_path, vector<string> &out_vec)
{
    // 为确保“提前读”有效，在末尾增加一个空白字符，结束时删掉
    ofstream temp_stream(in_path, ios::app);
    temp_stream << " ";
    temp_stream.close();
    // 开启文件
    // 必须采用这种方式，否则会导致流的错误行为；并且似乎只会在Windows下出现
    ifstream in_file(in_path, ios_base::in | ios_base::binary);
    // 状态
    FA_STATES current_state = STATE_I0;
    string current_token;
    string current_token_type;
    // 行数
    int lines_count = 1;
    // 读取文件
    char c;
    while (in_file.get(c))
    {
        // 加入token中
        current_token += c;

        // cout << current_token << " " << current_state << endl;

        // 遇到换行，行数 + 1
        // Windows和Linux的换行都包括\n
        // 这里不考虑MacOS的\r，因为我没有Mac:-(
        if (c == '\n')
        {
            ++lines_count;
        }
        // 基于FA的分析，参见实验报告中的DFAo
        switch (current_state)
        {
        case STATE_I0:
            // 空白符
            if (c == ' ' || c == '\t' || c == '\f')
            {
                current_token = current_token.substr(0, current_token.length() - 1);
            }
            else if (c == '\r' || c == '\n')
            {
                current_token = current_token.substr(0, current_token.length() - ENTER_LENGTH);
            }
            else if (c == '"')
            {
                current_state = STATE_I6;
            }
            // 操作符中的'/'可能和注释冲突，所以把注释的优先级放高一点
            else if (c == '/')
            {
                current_state = STATE_I12;
            }
            else if (c == '-')
            {
                current_state = STATE_I25;
            }
            else if (is_digit(c))
            {
                current_token_type = "NUMBER";
                current_state = STATE_I4;
            }
            else if (is_letter(c) || c == '_')
            {
                current_token_type = "ID";
                current_state = STATE_I3;
            }
            // 操作符可能不止一个字符，所以需要使用字符串进行比较
            else if (is_operator(current_token))
            {
                char next = in_file.peek();
                // 如果有下一个字符，并且下一个字符和当前字符拼起来还是操作符
                // 因为存在长度为2的操作符
                if (next && is_operator(current_token + next))
                {
                    current_token += next;
                    in_file.get();
                }
                current_token_type = "OPERATOR";
                current_state = STATE_I1;
            }
            else if (is_separator(c))
            {
                current_token_type = "SEPARATOR";
                current_state = STATE_I1;
            }
            // 其他字符视为错误，跳出循环
            // 随便设置一个状态
            else
            {
                current_state = STATE_I1;
                goto exist;
            }
            break;
        case STATE_I1:
            reset_FA_and_trim(in_file, out_vec,
                              current_token, current_token_type, current_state);
            break;
        case STATE_I3:
        {
            if (is_letter(c) || is_digit(c) || c == '_')
            {
                current_state = STATE_I3;
                // 如果没有下一个字符，或者下一个是其他字符，重置状态
                char next = in_file.peek();
                if (!next ||
                    (!is_letter(next) && !is_digit(next) && next != '_'))
                {
                    // 判断是否是关键字
                    if (is_keyword(current_token))
                    {
                        current_token_type = "KEYWORD";
                    }
                    reset_FA(out_vec,
                             current_token, current_token_type, current_state);
                }
            }
            // ID长度为1，读入了其他字符
            else
            {
                reset_FA_and_trim(in_file, out_vec,
                                  current_token, current_token_type, current_state);
            }
            break;
        }
        case STATE_I4:
        {
            if (is_digit(c))
            {
                current_state = STATE_I4;
                // 如果没有下一个字符，或者下一个不是数字，重置状态
                char next = in_file.peek();
                if (!next || !is_digit(next))
                {
                    reset_FA(out_vec,
                             current_token, current_token_type, current_state);
                }
            }
            else if (c == '.')
            {
                current_state = STATE_I15;
            }
            else
            {
                reset_FA_and_trim(in_file, out_vec,
                                  current_token, current_token_type, current_state);
            }
            break;
        }
        case STATE_I6:
            if (is_stringchar(c))
            {
                current_state = STATE_I6;
            }
            else if (c == '\\')
            {
                current_state = STATE_I24;
            }
            else if (c == '"')
            {
                current_token_type = "STRING";
                current_state = STATE_I1;
            }
            break;
        case STATE_I12:
            // 遇到'/'说明是注释
            if (c == '/')
            {
                current_state = STATE_I18;
            }
            // 其他字符则是操作符
            // 这里不按状态机来了，直接结束算了
            else
            {
                current_token_type = "OPERATOR";
                reset_FA_and_trim(in_file, out_vec,
                                  current_token, current_token_type, current_state);
            }
            break;
        case STATE_I15:
            if (is_digit(c))
            {
                current_token_type = "NUMBER";
                current_state = STATE_I19;
            }
            break;
        case STATE_I18:
            if (is_char(c))
            {
                current_state = STATE_I18;
            }
            // 注释的换行符代表注释的结束
            else if (c == '\n')
            {
                // 去掉换行符
                current_token = current_token.substr(0, current_token.length() - ENTER_LENGTH);
                current_token_type = "COMMENT";
                current_state = STATE_I1;
            }
            break;
        case STATE_I19:
            if (is_digit(c))
            {
                current_state = STATE_I19;
                // 如果没有下一个字符，或者下一个不是数字，重置状态
                char next = in_file.peek();
                if (!next || !is_digit(next))
                {
                    reset_FA(out_vec,
                             current_token, current_token_type, current_state);
                }
            }
            else
            {
                reset_FA_and_trim(in_file, out_vec,
                                  current_token, current_token_type, current_state);
            }
            break;
        case STATE_I24:
            if (c == '"')
            {
                current_state = STATE_I6;
            }
            break;
        case STATE_I25:
            if (is_digit(c))
            {
                current_state = STATE_I4;
            }
            break;
        default:
            break;
        }
    }
exist:
    // 去掉额外添加的空白字符
    int temp_file = open(in_path.c_str(), O_RDWR);
    chsize(temp_file, filelength(temp_file) - 1);
    // 关闭文件
    in_file.close();
    close(temp_file);
    // 结束时状态机没有重置
    // 只能说明有错误……
    if (current_state != STATE_I0)
    {
        cout << "Unknown token. Perhaps in line " + to_string(lines_count) + "." << endl;
        return false;
    }
    // 添加结束符
    out_vec.push_back("$, $");
    return true;
}

/**
 * 去除token右侧的空白符
 * @param token 需要修改的token
 * @param mode 空白符类型
 */
void trim_token(string &token, const char &mode)
{
    if (mode == ' ')
    {
        token = token.substr(0, token.length() - 1);
    }
    else if (mode == '\n')
    {
        token = token.substr(0, token.length() - ENTER_LENGTH);
    }
}

/**
 * 重置状态机并输出现有的token
 * @param out_vec 输出token的vector
 * @param current_token 当前token
 * @param current_token_type 当前token的类型
 * @param current_state 当前状态
 */
void reset_FA(vector<string> &out_vec,
              string &current_token,
              string &current_token_type,
              FA_STATES &current_state)
{
    out_vec.push_back(current_token + ", " + current_token_type);
    current_state = STATE_I0;
    current_token = "";
    current_token_type = "";
}

/**
 * 重置状态机并输出现有的token
 * 用于token长度为1的情况，因为实现是“提前读”，所以“退还”多读的字符
 * @param in_file 输入文件流
 * @param out_vec 输出token的vector
 * @param current_token 当前token
 * @param current_token_type 当前token的类型
 * @param current_state 当前状态
 */
void reset_FA_and_trim(ifstream &in_file,
                       vector<string> &out_vec,
                       string &current_token,
                       string &current_token_type,
                       FA_STATES &current_state)
{
    out_vec.push_back(current_token.substr(0, current_token.length() - 1) +
                      ", " +
                      current_token_type);
    // 到终态后重置状态
    current_state = STATE_I0;
    current_token = "";
    current_token_type = "";
    // 对最后多读的字符进行处理，文件指针前移一格
    in_file.seekg(-1, ios::cur);
}