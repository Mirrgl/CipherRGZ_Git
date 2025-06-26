#include "vernam.h"

namespace vernam {
    string encryptCipherText(const string& inputText, const string& key) {
        if (files::isTextFile(inputText)) {
            wstring resultText = L"";
            wstring inputWText = convert::strToWStr(inputText);
            wstring wKey = convert::strToWStr(key);
            for (int i = 0; i < inputWText.size(); i++) {
                int a = inputWText[i] ^ wKey[i % wKey.size()];
                resultText += inputWText[i] ^ wKey[i % wKey.size()];
            }

            return convert::wstrToString(resultText);
        }
        else {
            string resultText = "";
            for (int i = 0; i < inputText.size(); i++) {
                resultText += inputText[i] ^ key[i % key.size()];
            }

            return resultText;
        }
    }

    string decryptCipherText(const string& inputText, const string& key) {
        if (files::isTextFile(inputText)) {
            wstring resultText = L"";
            wstring inputWText = convert::strToWStr(inputText);
            wstring wKey = convert::strToWStr(key);
            for (int i = 0; i < inputWText.size(); i++) {
                resultText += inputWText[i] ^ wKey[i % wKey.size()];
            }

            return convert::wstrToString(manipwstring::unpadWString(resultText));
        }
        else {
            string resultText = "";
            for (int i = 0; i < inputText.size(); i++) {
                resultText += inputText[i] ^ key[i % key.size()];
            }

            return manipstring::unpadString(resultText);
        }
    }

    string keyGen(const size_t& lengthKey) {
        uniform_int_distribution<> dist(33,126);
        string key = "";
        for (size_t i = 0; i < lengthKey; i++) {
            key += dist(gen);
        }
        return key;
    }

    string genFile(const string& path) {
        string key;
        cout << "Введите длину ключа: ";
        size_t firstKeyLength;                                                        
        while (true) {
            cin >> firstKeyLength;                                                
            try {
                key = keyGen(firstKeyLength);
                files::writeFile(path, key);
                return key;
            }
            catch (const string& e) {
                cout << e << endl;
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }
        }
    }
}