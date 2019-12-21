#include <iostream>
#include <string>
#include "../includes/syntax_analyzer.h"
#include "../includes/string_utils.h"
using namespace std;

void preprocess(vector<string> &tokens);

bool analyze_syntax(vector<string> &tokens)
{
    preprocess(tokens);
    for (const string &s : tokens)
    {
        cout << s << endl;
    }
    return true;
}

/**
 * 对token进行预处理
 * @param tokens 保存tokens的vector
 */
void preprocess(vector<string> &tokens)
{
    vector<string> processed_tokens;
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
            processed_tokens.push_back(type);
        }
        else
        {
            processed_tokens.push_back(content);
        }
    }
    tokens.clear();
    tokens.assign(processed_tokens.begin(), processed_tokens.end());
}