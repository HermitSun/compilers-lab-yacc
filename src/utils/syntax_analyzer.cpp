#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include "../includes/syntax_analyzer.h"
#include "../includes/string_utils.h"
#include "../includes/syntax_enums.h"
using namespace std;

// 可能的操作类型
enum OPERATIONS
{
    ACC,
    SHIFT,
    REDUCE,
    GOTO
};

// 函数声明
queue<string> preprocess(vector<string> &tokens);
OPERATIONS get_operation_type(const string &op);
bool go_to(vector<int> &state_stack, vector<string> &symbol_stack);
void print_stack_trace(ofstream &out_file,
                       vector<int> &state_stack,
                       vector<string> &symbol_stack);
string predict_error_message(vector<string> &symbol_stack);

// 不用stack的原因是需要输出每一步的规约过程……用vector总觉得有哪里不对
bool analyze_syntax(vector<string> &tokens, const string &out_path)
{
    // 处理过的token
    queue<string> processed_tokens = preprocess(tokens);
    // 规约过程保存路径
    ofstream out_file(out_path);
    // 状态栈，初始0号自动机
    vector<int> state_stack;
    state_stack.push_back(0);
    // 符号栈，栈底预先压一个$
    vector<string> symbol_stack;
    symbol_stack.push_back("$");
    // 读头不为空
    while (!processed_tokens.empty())
    {
        int state = state_stack.back();
        // 读头项
        string reader_item = processed_tokens.front();
        out_file << state << " " << reader_item << endl;
        // 查表获取操作类型
        auto element_index = element_to_number.find(reader_item);
        // 如果查不到，未知操作数，报错
        if (element_index == element_to_number.end())
        {
            cout << "Error exist. "
                 << "Unknown operand: " + reader_item
                 << endl;
            return false;
        }
        string operation = SLR_table[state][element_index->second];
        // 未定义行为
        if (operation == " ")
        {
            cout << "Error exist. "
                 << predict_error_message(symbol_stack)
                 << endl;
            return false;
        }
        out_file << operation << endl;
        switch (get_operation_type(operation))
        {
        // 语法分析正确完成
        case ACC:
            out_file << "acc" << endl;
            return true;
        case SHIFT:
        {
            // 移进式
            int index = atoi(operation.substr(1, operation.length() - 1).c_str());
            state_stack.push_back(index);
            symbol_stack.push_back(reader_item);
            // 读头项出队
            processed_tokens.pop();
            print_stack_trace(out_file, state_stack, symbol_stack);
            break;
        }
        case REDUCE:
        {
            // 规约式
            pair<string, string> reduction =
                CFG[atoi(operation.substr(1, operation.length() - 1).c_str())];
            // 如果不能用ε规约
            if (reduction.first != "")
            {
                // 需要pop的项数
                int pop_num = split_string(reduction.first, " ").size();
                for (int i = 0; i < pop_num; ++i)
                {
                    state_stack.pop_back();
                    symbol_stack.pop_back();
                }
            }
            // 规约后，符号栈压栈
            symbol_stack.push_back(reduction.second);
            print_stack_trace(out_file, state_stack, symbol_stack);
            // 进行GOTO操作
            bool result = go_to(state_stack, symbol_stack);
            // 出错
            if (!result)
            {
                cout << "Error exist."
                     << predict_error_message(symbol_stack)
                     << endl;
                return false;
            }
            // 成功后输出栈信息
            print_stack_trace(out_file, state_stack, symbol_stack);
            break;
        }
        case GOTO:
            // 状态栈压栈
            state_stack.push_back(atoi(operation.c_str()));
            print_stack_trace(out_file, state_stack, symbol_stack);
            break;
        default:
            return false;
        }
    }
    return true;
}

/**
 * 对token进行预处理
 * @param tokens 保存tokens的vector
 * @return token队列
 */
queue<string> preprocess(vector<string> &tokens)
{
    queue<string> processed_tokens;
    for (const string &token : tokens)
    {
        vector<string> splitted_token = split_string(token, ", ");
        string content = splitted_token[0];
        string type = splitted_token[1];
        // 扔掉注释
        if (type == "COMMENT")
        {
            continue;
        }
        // 将部分token泛化为类型
        else if (type == "NUMBER" || type == "ID")
        {
            processed_tokens.push(type);
        }
        else
        {
            processed_tokens.push(content);
        }
    }
    return processed_tokens;
}

/**
 * 判断SLR Table中操作的类型
 * @param op 操作
 * @return 操作类型，acc/移进/规约/跳转
 */
OPERATIONS get_operation_type(const string &op)
{
    if (op == "acc")
    {
        return ACC;
    }
    else if (op[0] == 's')
    {
        return SHIFT;
    }
    else if (op[0] == 'r')
    {
        return REDUCE;
    }
    else
    {
        return GOTO;
    }
}

/**
 * GOTO操作
 * @param state_stack 状态栈
 * @param symbol_stack 符号栈
 * @return true成功，false存在错误
 */
bool go_to(vector<int> &state_stack, vector<string> &symbol_stack)
{
    int state = state_stack.back();
    string symbol = symbol_stack.back();
    string goto_state = SLR_table[state][element_to_number[symbol]];
    // 没有预定的行为
    if (goto_state == " ")
    {
        cout << "Unknown GOTO operation." << endl;
        return false;
    }
    else
    {
        state_stack.push_back(atoi(goto_state.c_str()));
        return true;
    }
}

/**
 * 输出栈的操作轨迹
 * @param out_file 输出文件流
 * @param state_stack 状态栈
 * @param symbol_stack 符号栈
 */
void print_stack_trace(
    ofstream &out_file,
    vector<int> &state_stack,
    vector<string> &symbol_stack)
{
    // 打印栈
    out_file << "State Stack: ";
    for (const int &state : state_stack)
    {
        out_file << state << " ";
    }
    out_file << endl;
    out_file << "Symbol Stack: ";
    for (const string &symbol : symbol_stack)
    {
        out_file << symbol << " ";
    }
    out_file << endl
             << endl;
}

/**
 * 根据当前栈的情况推测错误信息
 * @param symbol_stack 符号栈
 */
string predict_error_message(vector<string> &symbol_stack)
{
    int brackets = 0;
    int square_brackets = 0;
    int curly_braces = 0;
    for (const string &s : symbol_stack)
    {
        if (s == "(")
        {
            ++brackets;
        }
        else if (s == "[")
        {
            ++square_brackets;
        }
        else if (s == "{")
        {
            ++curly_braces;
        }
        else if (s == ")")
        {
            --brackets;
        }
        else if (s == "]")
        {
            --square_brackets;
        }
        else if (s == "}")
        {
            --curly_braces;
        }
    }
    if (brackets)
    {
        return "Maybe '(' did not match?";
    }
    else if (square_brackets)
    {
        return "Maybe '[' did not match?";
    }
    else if (curly_braces)
    {
        return "Maybe '{' did not match?";
    }
    else
    {
        return "Maybe some statements did not end with ';' ?";
    }
}