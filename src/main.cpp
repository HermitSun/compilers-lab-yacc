#include <iostream>
#include <string>
#include "includes/lex_analyzer.h"
#include "includes/syntax_analyzer.h"
using std::cout;
using std::endl;
using std::string;

int main()
{
    const string in_path = "../Test.sw";
    const string out_path = "../Test_out_syntax.txt";
    vector<string> tokens;
    bool successed = analyze_lex(in_path, tokens);
    if (successed)
    {
        cout << "Lex analysis finished successfully." << endl;
        successed = analyze_syntax(tokens, out_path);
        if (successed)
        {
            cout << "Syntax analysis finished successfully." << endl;
        }
    }
}