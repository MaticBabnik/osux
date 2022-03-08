#pragma once

#include <string>
#include <vector>

using namespace std;

vector<string> StringSplit(const string &str, const string &delim) {
    vector<string> result;

    size_t pos = 0;

    while (true) {
        size_t next = str.find(delim, pos);

        if (next == string::npos) {
            result.push_back(str.substr(pos));
            break;
        } else {
            result.push_back(str.substr(pos, next - pos));
        }

        pos = next + delim.length();
    }

    return result;
}