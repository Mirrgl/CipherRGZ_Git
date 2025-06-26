#include "doubleCipher.h"

namespace doublecipher {
    vector<vector<char>> createMatrix(const string& text, const u_int8_t& length) {
        vector<vector<char>> matrixFromKey;
        vector<char> tempRow;
        for (size_t i = 0; i < text.size(); i++) {
            tempRow.push_back(text[i]);
            if ((i + 1) % length == 0) {
                matrixFromKey.push_back(tempRow);
                tempRow = {};
            }
        }

        return matrixFromKey;
    }

    vector<vector<char>> swapColumns(const vector<vector<char>>& inputMatrix, size_t key) {
        vector<size_t> vKey;
        while (key) {
            vKey.push_back(key % 10);
            key /= 10;
        }
        reverse(vKey.begin(), vKey.end());

        vector<vector<char>> swapedMatrix(inputMatrix.size(), vector<char>(vKey.size(), ' '));
        for (size_t column = 0; column < vKey.size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                swapedMatrix[row][vKey[column] - 1] = inputMatrix[row][column];
            }
        }

        return swapedMatrix;
    }

    vector<vector<char>> reverseSwapColumns(const vector<vector<char>>& inputMatrix, size_t key) {
        vector<size_t> vKey;
        while (key) {
            vKey.push_back(key % 10);
            key /= 10;
        }
        reverse(vKey.begin(), vKey.end());

        vector<vector<char>> swapedMatrix(inputMatrix.size(), vector<char>(vKey.size(), ' '));
        for (size_t column = 0; column < vKey.size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                swapedMatrix[row][column] = inputMatrix[row][vKey[column] - 1];
            }
        }

        return swapedMatrix;
    }

    vector<vector<char>> transposeMatrix(const vector<vector<char>>& inputMatrix) {
        vector<vector<char>> transposedMatrix;
        vector<char> tempRow;
        for (size_t column = 0; column < inputMatrix[0].size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                tempRow.push_back(inputMatrix[row][column]);
            }
            transposedMatrix.push_back(tempRow);
            tempRow = {};
        }
        return transposedMatrix;
    }

    vector<vector<wchar_t>> createWMatrix(const wstring& text, const u_int8_t& length) {
        vector<vector<wchar_t>> matrixFromKey;
        vector<wchar_t> tempRow;
        for (size_t i = 0; i < text.size(); i++) {
            tempRow.push_back(text[i]);
            if ((i + 1) % length == 0) {
                matrixFromKey.push_back(tempRow);
                tempRow = {};
            }
        }

        return matrixFromKey;
    }

    vector<vector<wchar_t>> swapWColumns(const vector<vector<wchar_t>>& inputMatrix, size_t key) {
        vector<size_t> vKey;
        while (key) {
            vKey.push_back(key % 10);
            key /= 10;
        }
        reverse(vKey.begin(), vKey.end());

        vector<vector<wchar_t>> swapedMatrix(inputMatrix.size(), vector<wchar_t>(vKey.size(), ' '));
        for (size_t column = 0; column < vKey.size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                swapedMatrix[row][vKey[column] - 1] = inputMatrix[row][column];
            }
        }

        return swapedMatrix;
    }

    vector<vector<wchar_t>> reverseSwapWColumns(const vector<vector<wchar_t>>& inputMatrix, size_t key) {
        vector<size_t> vKey;
        while (key) {
            vKey.push_back(key % 10);
            key /= 10;
        }
        reverse(vKey.begin(), vKey.end());

        vector<vector<wchar_t>> swapedMatrix(inputMatrix.size(), vector<wchar_t>(vKey.size(), ' '));
        for (size_t column = 0; column < vKey.size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                swapedMatrix[row][column] = inputMatrix[row][vKey[column] - 1];
            }
        }

        return swapedMatrix;
    }

    vector<vector<wchar_t>> transposeWMatrix(const vector<vector<wchar_t>>& inputMatrix) {
        vector<vector<wchar_t>> transposedMatrix;
        vector<wchar_t> tempRow;
        for (size_t column = 0; column < inputMatrix[0].size(); column++) {
            for (size_t row = 0; row < inputMatrix.size(); row++) {
                tempRow.push_back(inputMatrix[row][column]);
            }
            transposedMatrix.push_back(tempRow);
            tempRow = {};
        }
        return transposedMatrix;
    }

/* -------------------------------------------------------------------------------------------------------------------------------------------- */

    string encryptCipherText(const string& inputText, const vector<size_t> keys) {
        if (files::isTextFile(inputText)) {
            wstring result = L"";
            auto inputBlocks = manipwstring::createWBlocks(convert::strToWStr(inputText), maths::maxDigit(keys[0]) * maths::maxDigit(keys[1]), ' ');
            
            for (auto& inputData : inputBlocks) {
                vector<vector<wchar_t>> encryptedMatrix = createWMatrix(inputData, maths::maxDigit(keys[0]));

                encryptedMatrix = swapWColumns(encryptedMatrix, keys[0]);
                encryptedMatrix = transposeWMatrix(encryptedMatrix);
                encryptedMatrix = createWMatrix(manipwstring::createWString(encryptedMatrix), maths::maxDigit(keys[1]));
                encryptedMatrix = swapWColumns(encryptedMatrix, keys[1]);

                result += manipwstring::createWString(encryptedMatrix);
            }

            return convert::wstrToString(result);
        }
        else {
            string result = "";
            auto inputBlocks = manipstring::createBlocks(inputText, maths::maxDigit(keys[0]) * maths::maxDigit(keys[1]), ' ');
            
            for (auto& inputData : inputBlocks) {
                vector<vector<char>> encryptedMatrix = createMatrix(inputData, maths::maxDigit(keys[0]));

                encryptedMatrix = swapColumns(encryptedMatrix, keys[0]);
                encryptedMatrix = transposeMatrix(encryptedMatrix);
                encryptedMatrix = createMatrix(manipstring::createString(encryptedMatrix), maths::maxDigit(keys[1]));
                encryptedMatrix = swapColumns(encryptedMatrix, keys[1]);

                result += manipstring::createString(encryptedMatrix);
            }

            return result;            
        }
    }

    string decryptCipherText(const string& inputText, const vector<size_t> keys) {
        if (files::isTextFile(inputText)) {
            wstring result = L"";
            auto inputBlocks = manipwstring::createWBlocks(convert::strToWStr(inputText), maths::maxDigit(keys[0]) * maths::maxDigit(keys[1]), ' ');

            for (auto& inputData : inputBlocks) {
                vector<vector<wchar_t>> decryptedMatrix = createWMatrix(inputData, maths::maxDigit(keys[1]));
            
                decryptedMatrix = reverseSwapWColumns(decryptedMatrix, keys[1]);
                wstring tempstring = manipwstring::createWString(decryptedMatrix);
                decryptedMatrix = createWMatrix(tempstring, tempstring.size() / maths::maxDigit(keys[0]));
                decryptedMatrix = transposeWMatrix(decryptedMatrix);
                decryptedMatrix = reverseSwapWColumns(decryptedMatrix, keys[0]);

                result += manipwstring::createWString(decryptedMatrix); 
            }

            return convert::wstrToString(manipwstring::unpadWString(result));
        }
        else {
            string result = "";
            auto inputBlocks = manipstring::createBlocks(inputText, maths::maxDigit(keys[0]) * maths::maxDigit(keys[1]), ' ');

            for (auto& inputData : inputBlocks) {
                vector<vector<char>> decryptedMatrix = createMatrix(inputData, maths::maxDigit(keys[1]));
            
                decryptedMatrix = reverseSwapColumns(decryptedMatrix, keys[1]);
                string tempstring = manipstring::createString(decryptedMatrix);
                decryptedMatrix = createMatrix(tempstring, tempstring.size() / maths::maxDigit(keys[0]));
                decryptedMatrix = transposeMatrix(decryptedMatrix);
                decryptedMatrix = reverseSwapColumns(decryptedMatrix, keys[0]);

                result += manipstring::createString(decryptedMatrix); 
            }

            return manipstring::unpadString(result);
        }
    }

    bool checkKey(const size_t& key) {
        string stringKey = to_string(key);

        if (stringKey.size() != set(stringKey.begin(), stringKey.end()).size()) return false;

        sort(stringKey.begin(), stringKey.end());
        if (stringKey[0] == '0') return false;
        if (stoi(string() + stringKey.back()) != stringKey.size()) return false;

        for (u_int8_t i = 0; i < stringKey.size() - 1; i++) {
            if ((stoi(string() + stringKey[i]) + 1) != stoi(string() + stringKey[i + 1])) {
                return false;
            }
        }
        return true;
    }

    vector<size_t> keyGen(const size_t& firstKeyLength, size_t secondKeyLength = 0) {
        if (secondKeyLength == 0) {
            secondKeyLength = firstKeyLength;
        }

        if ((firstKeyLength < 1 || firstKeyLength > 9) || (secondKeyLength < 1 || secondKeyLength > 9)) {
            throw string("Длина ключа должна быть от 1 до 9 включительно");
        }

        vector<size_t> keys;
        while(true) {
            uniform_int_distribution<> dist(0,firstKeyLength - 1);
            size_t temp = 0;
            vector<u_int8_t> usedDigits;
            for (u_int8_t i = 1; i <= firstKeyLength; i++) {
                u_int8_t digit = dist(gen);
                if (find(usedDigits.begin(), usedDigits.end(), digit) == usedDigits.end()) {
                    temp += i * pow(10,digit);
                    usedDigits.push_back(digit);
                    continue;
                }
                i--;
            }
            if (checkKey(temp)) {
                keys.push_back(temp);
                break;
            }
        }
        while(true) {
            uniform_int_distribution<> dist(0,secondKeyLength - 1);
            size_t temp = 0;
            vector<u_int8_t> usedDigits;
            for (u_int8_t i = 1; i <= secondKeyLength; i++) {
                u_int8_t digit = dist(gen);
                if (find(usedDigits.begin(), usedDigits.end(), digit) == usedDigits.end()) {
                    temp += i * pow(10,digit);
                    usedDigits.push_back(digit);
                    continue;
                }
                i--;
            }
            if (checkKey(temp)) {
                keys.push_back(temp);
                break;
            }
        }
        return keys;
    }

    vector<size_t> genFile(const string& path) {
        vector<size_t> keys;
        cout << "Введите длины ключей: ";
        size_t firstKeyLength, secondKeyLength;                                                        
        while (true) {
            cin >> firstKeyLength >> secondKeyLength;                                                
            try {
                keys = keyGen(firstKeyLength, secondKeyLength);
                files::writeFile(path, to_string(keys[0]) + ' ' + to_string(keys[1]));
                return keys;
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