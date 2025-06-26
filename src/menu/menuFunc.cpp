#include "menuFunc.h"


void displayMainMenu() {
    cout << "Добро пожаловать в шифратор!   \
    \nВыберите пункт меню:                  \
    \n1. Шифрование текста                  \ 
    \n2. Расшифровка текста                 \
    \n3. Выход" << endl;
}

void displayCipherMenu(const string& action) {
    cout << "Выберите способ " << action << ":  \
    \n1. Шифр двойной перестановки              \
    \n2. Шифр Вернама                           \
    \n3. Сеть Фейстеля" << endl;
}

void displayInputMenu(const string& entity) {
    cout << "Выберите способ ввода " << entity << ":    \
    \n1. Ввести из консоли                         \
    \n2. Ввести из файла" << endl;
}

string readInputText() {
    string inputText;
    bool isEmptyLine = 0;
    string temp;
    while (true) {
        getline(cin, temp);
        if (isEmptyLine) break;
        if (temp.empty()) isEmptyLine = 1;
        inputText.insert(inputText.end(), temp.begin(), temp.end());
    }
    return inputText;
}

void saveText(const string& fileName, const string& cipherText) {
    while (true) {
        try {
            files::writeFile(fileName, cipherText);
            return;
        }
        catch (...) {
            cout << "Ошибка процесса" << endl;
            return;
        }
    }
}

string  openFileText() {
    string path;
    string inputText;
    while (true) {
        cout << "Введите название файла или полный путь, если файл не находится в директории с программой" << endl;
        cin >> path;
        try {
            inputText = files::readFile(path);
            return inputText;
        }
        catch (const runtime_error& e) {
            cerr << e.what() << endl;
            cout << "Создать файл? \n1. Да \n2. Нет" << endl;
            int check;
            while (true) {
                cin >> check;
                switch (check) {
                    case 1: {
                        cout << "Введите текст:" << endl;
                        cin >> inputText;
                        try {
                            files::writeFile(path, inputText);
                        }
                        catch (const runtime_error& e) {
                            cerr << e.what() << endl;
                        }
                        return inputText;

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