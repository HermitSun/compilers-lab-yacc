#include <iostream>
#include <string>
#include "includes/lex_analyzer.h"
using std::cout;
using std::endl;
using std::string;

int main()
{
    const string in_path = "../Test.sw";
    vector<string> tokens;
    bool successed = analyze_lex(in_path, tokens);
    if (successed)
    {
        cout << "Lex analysis finished successfully." << endl;
    }
    for (const string &token : tokens)
    {
        cout << token << endl;
    }
}