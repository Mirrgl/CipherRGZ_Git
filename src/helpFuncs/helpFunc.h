#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <sstream>
#include <set>
#include <random>
#include <limits>

using namespace std;


static random_device rd;
static mt19937_64 gen(rd());

namespace files {
    bool isTextFile(const string& inputText);

    string readFile(const string& filename);
    
    void writeFile(const string& filename, const string& data);
}

namespace convert {
    wstring strToWStr(const string& str);

    string wstrToString(const wstring& wstr);

    vector<size_t> convertstringToSizeT(const string& inputText);
}

namespace manipstring {
    vector<string> createBlocks(const string& inputText, u_int8_t sizeBlock, const char& padChar);

    string createString(const vector<vector<char>>& inputMatrix);

    string unpadString(const string& inputLine);
}

namespace manipwstring {
    vector<wstring> createWBlocks(const wstring& inputText, u_int8_t sizeBlock, const wchar_t& padChar);

    wstring createWString(const vector<vector<wchar_t>>& inputMatrix);

    wstring unpadWString(const wstring& inputLine);
}

namespace maths{
    int maxDigit(int n);
}

istream& operator>>(istream& is, vector<size_t>& v);

#endif