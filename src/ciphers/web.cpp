#include "web.h"

namespace web {
    string cyclicShift(const string& dataBytes, const u_int8_t& shift) {
        if (dataBytes.size() == 1) return dataBytes;
        string cycledData = dataBytes;
        for (size_t i = 0; i < shift; i++) {
            string temp(cycledData.begin() + 1, cycledData.end());
            temp.insert(temp.end(), cycledData.begin(), cycledData.begin() + 1);
            cycledData = temp;
        }
        return cycledData;
    }

    string xorBlocks(const string& leftBlock, const string& rightBlock) {
        string resultBlock = "";
        for (int i = 0; i < leftBlock.size(); i++) {
            resultBlock += leftBlock[i] ^ rightBlock[i];
        }
        return resultBlock;
    }

    wstring cyclicShiftW(const wstring& dataBytes, const u_int8_t& shift) {
        if (dataBytes.size() == 1) return dataBytes;
        wstring cycledData = dataBytes;
        for (size_t i = 0; i < shift; i++) {
            wstring temp(cycledData.begin() + 1, cycledData.end());
            temp.insert(temp.end(), cycledData.begin(), cycledData.begin() + 1);
            cycledData = temp;
        }
        return cycledData;
    }

    wstring xorWBlocks(const wstring& leftBlock, const wstring& rightBlock) {
        wstring resultBlock = L"";
        for (int i = 0; i < leftBlock.size(); i++) {
            resultBlock += leftBlock[i] ^ rightBlock[i];
        }
        return resultBlock;
    }

    string encryptCipherText(const string& inputText, size_t& key) {
        if (files::isTextFile(inputText)) {
            size_t lastkey;
            wstring result = L"";

            auto blocks = manipwstring::createWBlocks(convert::strToWStr(inputText), CHARACTERS, L' ');
            for (auto& block : blocks) {
                size_t roundKey = key;
                auto leftRightBlocks = manipwstring::createWBlocks(block, block.size()/2, L' '); //[0] - left. [1] - right
                for (int i = 0; i < ROUNDS - 1; i++) {
                    leftRightBlocks[0] = web::xorWBlocks(leftRightBlocks[0], web::cyclicShiftW(leftRightBlocks[1], roundKey));
                    swap(leftRightBlocks[0], leftRightBlocks[1]);
                    roundKey++;
                }
                leftRightBlocks[0] = web::xorWBlocks(leftRightBlocks[0], web::cyclicShiftW(leftRightBlocks[1], roundKey));
                result += leftRightBlocks[0] + leftRightBlocks[1];
                lastkey = roundKey;
            }
            key = lastkey;
            return convert::wstrToString(result);
        }
        else {
            size_t lastkey;
            string result = "";

            auto blocks = manipstring::createBlocks(inputText, CHARACTERS, ' ');
            for (auto& block : blocks) {
                size_t roundKey = key;
                auto leftRightBlocks = manipstring::createBlocks(block, block.size()/2, ' '); //[0] - left. [1] - right
                for (int i = 0; i < ROUNDS - 1; i++) {
                    leftRightBlocks[0] = web::xorBlocks(leftRightBlocks[0], web::cyclicShift(leftRightBlocks[1], roundKey));
                    swap(leftRightBlocks[0], leftRightBlocks[1]);
                    roundKey++;
                }
                leftRightBlocks[0] = web::xorBlocks(leftRightBlocks[0], web::cyclicShift(leftRightBlocks[1], roundKey));
                result += leftRightBlocks[0] + leftRightBlocks[1];
                lastkey = roundKey;
            }
            key = lastkey;
            return result;
        }
    }

    string decryptCipherText(const string& inputText, size_t key) {
        if (files::isTextFile(inputText)) {
            size_t lastkey;
            wstring result = L"";

            auto blocks = manipwstring::createWBlocks(convert::strToWStr(inputText), CHARACTERS, L' ');
            for (auto& block : blocks) {
                size_t roundKey = key;
                auto leftRightBlocks = manipwstring::createWBlocks(block, block.size()/2, L' '); //[0] - left. [1] - right
                for (int i = 0; i < ROUNDS - 1; i++) {
                    leftRightBlocks[0] = xorWBlocks(leftRightBlocks[0], cyclicShiftW(leftRightBlocks[1], roundKey));
                    swap(leftRightBlocks[0], leftRightBlocks[1]);
                    roundKey--;
                }
                leftRightBlocks[0] = xorWBlocks(leftRightBlocks[0], cyclicShiftW(leftRightBlocks[1], roundKey));
                result += leftRightBlocks[0] + leftRightBlocks[1];
                lastkey = roundKey;
            }   
            key = lastkey;
            return convert::wstrToString(manipwstring::unpadWString(result));
        }
        else {
            size_t lastkey;
            string result = "";

            auto blocks = manipstring::createBlocks(inputText, CHARACTERS, ' ');
            for (auto& block : blocks) {
                size_t roundKey = key;
                auto leftRightBlocks = manipstring::createBlocks(block, block.size()/2, ' '); //[0] - left. [1] - right
                for (int i = 0; i < ROUNDS - 1; i++) {
                    leftRightBlocks[0] = xorBlocks(leftRightBlocks[0], cyclicShift(leftRightBlocks[1], roundKey));
                    swap(leftRightBlocks[0], leftRightBlocks[1]);
                    roundKey--;
                }
                leftRightBlocks[0] = xorBlocks(leftRightBlocks[0], cyclicShift(leftRightBlocks[1], roundKey));
                result += leftRightBlocks[0] + leftRightBlocks[1];
                lastkey = roundKey;
            }   
            key = lastkey;
            return manipstring::unpadString(result);            
        }
    }

    size_t keyGen(const size_t& keyLength) {
        if (keyLength >= 20 || keyLength < 1) throw string("Длина ключа должна быть от 1 до 19 включительно");
        uniform_real_distribution<> dist((size_t)1, UINT64_MAX % (size_t)pow((size_t)10, keyLength));
        return dist(gen);
    }

    size_t genFile(const string& path) {
        size_t key;
        cout << "Введите длину ключа: ";
        size_t firstKeyLength;                                                        
        while (true) {
            cin >> firstKeyLength;                                                
            try {
                key = keyGen(firstKeyLength);
                files::writeFile(path, to_string(key));
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