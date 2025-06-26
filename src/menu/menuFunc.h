#ifndef MENU_FUNC_H
#define MENU_FUNC_H

#include "helpFunc.h"

enum class mainMenu {
    CIPHER = 1,
    DECIPHER,
    EXIT
};

enum class cipherMenu {
    DOUBLE_CIPHER = 1,
    VERNAM,
    WEB,
};

enum class keyInputMenu {
    FROM_CONSOLE = 1,
    FROM_FILE,
};

void displayMainMenu();

void displayCipherMenu(const string& action);

void displayInputMenu(const string& entity);

template<typename T>
T checkKeyMenu(bool (*check)(T) = nullptr) {
    while (true) {
        T keys;
        try {
            cin >> keys;
            if (check != nullptr && check(keys)) throw string("Введён неправильный ключ (нажмите Enter, чтобы ввести ключи)");
            return keys;
        }
        catch (const string& e) {
            cout << e << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template<typename T>
T openFileKey(bool (*check)(T), T (*cipherGenFile)(const string&), T (*getKey)(const string&)) {
    T keys;
    string path;
    while (true) {
        cout << "Введите название файла или полный путь, если файл не находится в директории с программой" << endl;
        cin >> path;
        try {
            string stringKey = files::readFile(path);
            keys = getKey(stringKey);
            if (check(keys)) throw string("Введён неправильный ключ");
            return keys;
        }
        catch (const invalid_argument& e) {
            cout << "Введён неправильный ключ" << endl;
        }
        catch (const string& e) {
            cout << e << endl;
        }
        catch (const runtime_error& e) {
            cerr << e.what() << endl;
            cout << "Создать файл? \n1. Да \n2. Нет" << endl;
            int check;
            while (true) {
                cin >> check;
                switch (check) {
                    case 1: {
                        return cipherGenFile(path);
                        
                        break;
                    }

                    case 2 : {
                        break;
                    }

                    default: {
                        cout << "Неверный ввод" << endl;
                        continue;
                    }
                }
                break;
            }
        }
    }
}

template<typename T>
T openFileKeyWithoutGen(bool (*check)(T), T (*getKey)(const string&)) {
    string path;
    T keys;
    while (true) {
        cout << "Введите название файла или полный путь, если файл не находится в директории с программой" << endl;
        cin >> path;
        try {
            string stringKey = files::readFile(path);
            keys = getKey(stringKey);
            if (check(keys)) throw string("Введён неправильный ключ");
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

string readInputText();

void saveText(const string& fileName, const string& cipherText);

string openFileText();

#endif