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

vector<string> split_string(const string &s, const string &delim)
{
    vector<string> res;
    int p = 0;
    string::size_type pos1, pos2;
    size_t len = s.length();
    pos2 = s.find(delim);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        res.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delim.size();
        pos2 = s.find(delim, pos1);
    }
    if (pos1 != len)
        res.push_back(s.substr(pos1));
    return res;
}