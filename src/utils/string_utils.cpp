#include "../includes/string_utils.h"
#include <sstream>
#include <iterator>
#include <algorithm>
using std::istream_iterator;
using std::istringstream;

static inline void ltrim(string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
}

static inline void rtrim(string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            })
                .base(),
            s.end());
}

static inline void trim(string &s)
{
    ltrim(s);
    rtrim(s);
}

vector<string> split_string(const string &s, const string &delimiters)
{
    vector<string> tokens;
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos)); //use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
    return tokens;
}