#ifndef WEB_H
#define WEB_H

#include "helpFunc.h"

#define CHARACTERS 4
#define ROUNDS 2

namespace web {
    string cyclicShift(const string& dataBytes, const u_int8_t& shift);

    string xorBlocks(const string& leftBlock, const string& rightBlock);
    
    wstring cyclicShiftW(const wstring& dataBytes, const u_int8_t& shift);

    wstring xorWBlocks(const wstring& leftBlock, const wstring& rightBlock);

    string encryptCipherText(const string& inputText, size_t& key);

    string decryptCipherText(const string& inputText, size_t key);

    size_t keyGen(const size_t& keyLength);

    size_t genFile(const string& path);
}

#endif