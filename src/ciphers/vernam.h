#ifndef VERNAM_H
#define VERNAM_H

#include "helpFunc.h"

namespace vernam {
    string encryptCipherText(const string& inputText, const string& key);

    string decryptCipherText(const string& inputText, const string& key);

    string keyGen(const size_t& lengthKey);

    string genFile(const string& path);
}

#endif