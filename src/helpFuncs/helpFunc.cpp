#include "helpFunc.h"

namespace files {
    bool isTextFile(const string& inputText) {
        try {
            return !(convert::strToWStr(inputText).empty());
        }
        catch (...) {
            return 0;
        }
    }

    string readFile(const string& filename){
        ifstream file(filename, ios::binary);
        if (!file) {
            throw runtime_error("Не удалось открыть файл: " + filename);
        }
        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return data;
    }
    
    void writeFile(const string& filename, const string& data) {
        ofstream file(filename, ios::binary);
        if (!file) {
            throw string("Не удалось открыть файл для записи: " + filename);
        }
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        file.close();
    }
}

namespace convert {
    wstring strToWStr(const string& str) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }

    string wstrToString(const wstring& wstr) {
        wstring_convert<codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }

    vector<size_t> convertstringToSizeT(const string& inputText) {
        vector<size_t> output;
        string temp;
        stringstream wss(inputText);
        while(wss >> temp) {
            try {
                output.push_back((size_t)stoi(temp));
                continue;
            }
            catch (...) {
                throw string("Невозможно преобразовать текст в числа");
            }
        }
        return output;
    }
}

namespace manipstring {
    vector<string> createBlocks(const string& inputText, u_int8_t sizeBlock, const char& padChar) {
        vector<string> blocks;
        string tempstring = "";
        for (size_t i = 0; i < inputText.size(); i++) {
            tempstring.push_back(inputText[i]);
            if ((i + 1) % sizeBlock == 0) {
                blocks.push_back(tempstring);
                tempstring = "";
            }
        }

        if (tempstring.size() != 0 && tempstring.size() != sizeBlock) {
            u_int8_t length = tempstring.size();
            for (size_t i = 0; i < sizeBlock - length; i++) {
                tempstring.push_back(padChar);
            }
            blocks.push_back(tempstring);
        }

        return blocks;
    }

    string createString(const vector<vector<char>>& inputMatrix) {
        string tempstring;
        for (size_t i = 0; i < inputMatrix.size(); i++){
            tempstring.insert(tempstring.end(), inputMatrix[i].begin(), inputMatrix[i].end());
        }

        return tempstring;
    }    

    string unpadString(const string& inputLine) {
        string paddedLine = inputLine;

        u_int8_t count = 0;
        for (size_t i = paddedLine.size() - 1; i > 0; i--) {
            if (paddedLine[i] != ' ') {
                break;
            }
            count++;
        }
        paddedLine.resize(paddedLine.size() - count);

        return paddedLine;
    }
}

namespace manipwstring {
    vector<wstring> createWBlocks(const wstring& inputText, u_int8_t sizeBlock, const wchar_t& padChar) {
        vector<wstring> blocks;
        wstring tempstring = L"";
        for (size_t i = 0; i < inputText.size(); i++) {
            tempstring.push_back(inputText[i]);
            if ((i + 1) % sizeBlock == 0) {
                blocks.push_back(tempstring);
                tempstring = L"";
            }
        }

        if (tempstring.size() != 0 && tempstring.size() != sizeBlock) {
            u_int8_t length = tempstring.size();
            for (size_t i = 0; i < sizeBlock - length; i++) {
                tempstring.push_back(padChar);
            }
            blocks.push_back(tempstring);
        }

        return blocks;
    }

    wstring createWString(const vector<vector<wchar_t>>& inputMatrix) {
        wstring tempstring;
        for (size_t i = 0; i < inputMatrix.size(); i++){
            tempstring.insert(tempstring.end(), inputMatrix[i].begin(), inputMatrix[i].end());
        }

        return tempstring;
    }    

    wstring unpadWString(const wstring& inputLine) {
        wstring paddedLine = inputLine;

        u_int8_t count = 0;
        for (size_t i = paddedLine.size() - 1; i > 0; i--) {
            if (paddedLine[i] != ' ') {
                break;
            }
            count++;
        }
        paddedLine.resize(paddedLine.size() - count);

        return paddedLine;
    }
}



namespace maths{
    int maxDigit(int n) {return (n ? max(n%10, maxDigit(n/10)) : 0);};
}

istream& operator>>(istream& is, vector<size_t>& v) {
    string line;
    getline(is, line);
    istringstream iss(line);
    size_t inputWord;

    while (iss >> inputWord) {
        v.push_back(inputWord);
    }

    if (v.empty()) throw string("Неверный ввод: ключи должен быть числами (нажмите Enter, чтобы ввести ключи)");

    return is;
}