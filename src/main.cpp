#include "helpFunc.h"
#include "web.h"
#include "doubleCipher.h"
#include "vernam.h"
#include "menuFunc.h"


int main() {
    displayMainMenu();
    
    int choiceMenu;
    cin >> choiceMenu;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (static_cast<mainMenu>(choiceMenu)) {
        case mainMenu::CIPHER: {
            displayCipherMenu("шифрования");

            int choiceCipher;
            while (true) {
                cin >> choiceCipher;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch (static_cast<cipherMenu>(choiceCipher)) {
                    case cipherMenu::DOUBLE_CIPHER: {
                        vector<size_t> keys;
                        string inputText;
                        int choiceInput;
                        displayInputMenu("ключа");

                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    keys = checkKeyMenu<vector<size_t>>([](vector<size_t> c) {return !(doublecipher::checkKey(c[0])) || !(doublecipher::checkKey(c[1]));});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    keys = openFileKey<vector<size_t>>([](vector<size_t> c) {return !(doublecipher::checkKey(c[0])) || !(doublecipher::checkKey(c[1]));},\ 
                                                                        doublecipher::genFile, convert::convertstringToSizeT);
                                    for (auto& key : keys) {
                                        cout << key << " ";
                                    }
                                    cout << endl;

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        displayInputMenu("текста");

                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    inputText = readInputText();
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    inputText = openFileText();

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        cout << "Введите названия файла, куда сохранится зашифрованный текст: " << endl;
                        string fileName;
                        cin >> fileName;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileName, doublecipher::encryptCipherText(inputText, keys));

                        cout << "Зашифрованный текст сохранён в " << fileName << endl;

                        break;
                    }
                    
                    case cipherMenu::VERNAM: {
                        string key;
                        string inputText;
                        int choiceInput;
                        displayInputMenu("ключа");
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    key = checkKeyMenu<string>([](string c) {return c.empty();});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    key = openFileKey<string>([](string c) {return c.empty();}, vernam::genFile, [](const string& a){return a;});
                                    cout << key << endl;

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        displayInputMenu("текста");
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    inputText = readInputText();
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    inputText = openFileText();
                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        cout << "Введите названия файла, куда сохранится зашифрованный текст: " << endl;
                        string fileName;
                        cin >> fileName;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileName, vernam::encryptCipherText(inputText, key));

                        cout << "Зашифрованный текст сохранён в " << fileName << endl;

                        break;
                    }
                    
                    case cipherMenu::WEB: {
                        size_t key;
                        string inputText;
                        int choiceInput;
                        displayInputMenu("ключа");
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    key = checkKeyMenu<size_t>([](size_t a){return a <= 0;});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    key = openFileKey<size_t>([](size_t a){return a <= 0;}, web::genFile, [](const string& a){return static_cast<size_t>(stoi(a));});
                                    cout << key << endl;

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        displayInputMenu("текста");
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    inputText = readInputText();
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    inputText = openFileText();

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        cout << "Введите названия файла, куда сохранится зашифрованный текст: " << endl;
                        string fileCipherText;
                        cin >> fileCipherText;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        cout << "Введите названия файла, куда сохранится преобразованный ключ (нужен для расшифровки): " << endl;
                        string fileKeyText;
                        cin >> fileKeyText;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileCipherText, web::encryptCipherText(inputText, key));
                        saveText(fileKeyText, to_string(key));

                        cout << "Зашифрованный текст сохранён в " << fileCipherText << endl;
                        cout << "Преобразованный ключ сохранён в " << fileKeyText << endl;

                        break;
                    }

                    default: {
                        cout << "Неверный ввод" << endl;
                        continue;
                    }
                }
                break;
            }
            break;
        }
        
        case mainMenu::DECIPHER: {
            string inputText;            
            int choiceInput;

            displayInputMenu("текста");

            while (true) {
                cin >> choiceInput;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch (static_cast<keyInputMenu>(choiceInput)) {
                    case keyInputMenu::FROM_CONSOLE: {
                        inputText = readInputText();
                        break;
                    }
                    
                    case keyInputMenu::FROM_FILE: {
                        inputText = openFileText();

                        break;
                    }

                    default: {
                        cout << "Неверный ввод" << endl;
                        continue;
                    }
                }
                break;
            }

            displayCipherMenu("расшифровки");

            while (true) {
                cin >> choiceInput;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (static_cast<cipherMenu>(choiceInput)) {
                    case cipherMenu::DOUBLE_CIPHER: {
                        vector<size_t> keys;

                        displayInputMenu("ключа");
                        // \n3. Предыдущее меню" << endl;
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    keys = checkKeyMenu<vector<size_t>>([](vector<size_t> c) {return !(doublecipher::checkKey(c[0])) || !(doublecipher::checkKey(c[1]));});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    keys = openFileKeyWithoutGen<vector<size_t>>([](vector<size_t> a){return !(doublecipher::checkKey(a[0])) || !(doublecipher::checkKey(a[1]));},\
                                                                                convert::convertstringToSizeT);
                                    for (auto& key : keys) {
                                        cout << key << " ";
                                    }
                                    cout << endl;

                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }
                        
                        cout << "Введите названия файла, куда сохранится расшифрованный текст: " << endl;
                        string fileName;
                        cin >> fileName;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileName, doublecipher::decryptCipherText(inputText, keys));

                        cout << "Расшифрованный текст сохранён в " << fileName << endl;

                        break;
                    }
                    
                    case cipherMenu::VERNAM: {
                        string key;

                        displayInputMenu("ключа");
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    key = checkKeyMenu<string>([](string c) {return c.empty();});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    key = openFileKeyWithoutGen<string>([](string c) {return c.empty();},[](const string& a){return a;});
                                    cout << key << endl;
                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        cout << "Введите названия файла, куда сохранится расшифрованный текст: " << endl;
                        string fileName;
                        cin >> fileName;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileName, vernam::decryptCipherText(inputText, key));

                        cout << "Расшифрованный текст сохранён в " << fileName << endl;

                        break;
                    }
                    
                    case cipherMenu::WEB: {
                        size_t key;

                        displayInputMenu("ключа");
                        // \n3. Предыдущее меню" << endl;
                        while (true) {
                            cin >> choiceInput;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            switch (static_cast<keyInputMenu>(choiceInput)) {
                                case keyInputMenu::FROM_CONSOLE: {
                                    key = checkKeyMenu<size_t>([](size_t k){return k <= 0;});
                                    break;
                                }
                                
                                case keyInputMenu::FROM_FILE: {
                                    key = openFileKeyWithoutGen<size_t>([](size_t k){return k <= 0;}, [](const string& a){return static_cast<size_t>(stoi(a));});
                                    cout << key << endl;
                                    break;
                                }

                                default: {
                                    cout << "Неверный ввод" << endl;
                                    continue;
                                }
                            }
                            break;
                        }

                        cout << "Введите названия файла, куда сохранится расшифрованный текст: " << endl;
                        string fileName;
                        cin >> fileName;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        saveText(fileName, web::decryptCipherText(inputText, key));

                        cout << "Расшифрованный текст сохранён в " << fileName << endl;

                        break;
                    }

                    default: {
                        cout << "Неверный ввод" << endl;
                        continue;
                    }
                }
                break;
            }

            break;
        }
        
        case mainMenu::EXIT: {
            cout << "Выход" << endl;
            return 0;
        }

        default: {
            cout << "Неверный ввод" << endl;
            break;
        }
    }  

    return 0;
}