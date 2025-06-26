#ifndef DOUBLECIPHER_H
#define DOUBLECIPHER_H

#include "helpFunc.h"

namespace doublecipher {
    vector<vector<char>> createMatrix(const string& text, const u_int8_t& length);

    vector<vector<char>> swapColumns(const vector<vector<char>>& inputMatrix, size_t key);

    vector<vector<char>> reverseSwapColumns(const vector<vector<char>>& inputMatrix, size_t key);

    vector<vector<char>> transposeMatrix(const vector<vector<char>>& inputMatrix);

    vector<vector<wchar_t>> createWMatrix(const wstring& text, const u_int8_t& length);

    vector<vector<wchar_t>> swapWColumns(const vector<vector<wchar_t>>& inputMatrix, size_t key);

    vector<vector<wchar_t>> reverseSwapWColumns(const vector<vector<wchar_t>>& inputMatrix, size_t key);

    vector<vector<wchar_t>> transposeWMatrix(const vector<vector<wchar_t>>& inputMatrix);

    string encryptCipherText(const string& inputText, const vector<size_t> keys);

    string decryptCipherText(const string& inputText, const vector<size_t> keys);

    bool checkKey(const size_t& key);

    vector<size_t> keyGen(const size_t& firstKeyLength, size_t secondKeyLength);

    vector<size_t> genFile(const string& path);
}

#endif