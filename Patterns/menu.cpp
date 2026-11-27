#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <windows.h>
#include "MobileApp.h"

using namespace std;

void initRegistry() {
    GameApp::Register();     
    SocialApp::Register();    
    FinanceApp::Register();   
    EducationApp::Register(); 
    UtilityApp::Register();   
}

void createDefaultFileIfNotExists(const string& filename) {
    ifstream checkFile(filename);
    if (checkFile.good()) {
        checkFile.close();
        return;
    }

    ofstream out(filename);
    if (out.is_open()) {
        out << "0;Sims4;14.8;Симулятор\n";
        out << "1;Chat;10.5;200000\n";
        out << "2;БелБанк Онлайн;3.2;BYN\n";
        out << "3;LearnC++;3.5;C++\n";
        out << "4;DazzCam;4.2;0\n";
        out.close();
    }
}

void loadFromFile(const string& filename, vector<unique_ptr<MobileApp>>& apps) {
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Ошибка открытия файла " << filename << "!\n";
        return;
    }

    
    apps.clear();

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string typeStr, name, verStr, extra;

        getline(ss, typeStr, ';');
        getline(ss, name, ';');
        getline(ss, verStr, ';');
        getline(ss, extra, ';');

        int type = stoi(typeStr);
        double version = stod(verStr);

        unique_ptr<AppSpec> spec;
        if (type == GAME_APP)           spec = make_unique<GameAppSpec>(name, version, extra);
        else if (type == SOCIAL_APP)    spec = make_unique<SocialAppSpec>(name, version, stoi(extra));
        else if (type == FINANCE_APP)   spec = make_unique<FinanceAppSpec>(name, version, extra);
        else if (type == EDUCATION_APP) spec = make_unique<EducationAppSpec>(name, version, extra);
        else if (type == UTILITY_APP)   spec = make_unique<UtilityAppSpec>(name, version, stoi(extra) != 0);

        if (spec) {
            apps.push_back(makeAppWithArgs(spec.get()));
        }
    }
    in.close();
    cout << "Успешно загружено объектов из файла: " << apps.size() << "\n";
}

void saveAllToFile(const string& filename, const vector<unique_ptr<MobileApp>>& apps) {
    ofstream out(filename);
    if (out.is_open()) {
        for (const auto& app : apps) {
            app->saveToFile(out);
        }
        out.close();
        cout << "Все приложения сохранены в файл " << filename << "!\n";
    }
}

int chooseAppType() {
    int t;
    cout << "Выберите тип приложения:\n"
        << "0 - Игра (GameApp)\n"
        << "1 - Соцсеть (SocialApp)\n"
        << "2 - Финансы (FinanceApp)\n"
        << "3 - Образование (EducationApp)\n"
        << "4 - Утилита (UtilityApp)\n"
        << "Ваш выбор: ";
    cin >> t;
    return t;
}

void showAll(const vector<unique_ptr<MobileApp>>& apps) {
    if (apps.empty()) {
        cout << "Список приложений пуст.\n";
        return;
    }

    string line(123, '-'); 

    cout << "\n" << line << "\n";
    cout << left
        << "| " << setw(3) << "№"
        << "| " << setw(12) << "Категория"
        << "| " << setw(18) << "Название"
        << "| " << setw(7) << "Версия"
        << "| " << setw(46) << "Программный модуль (Полиморфная фабрика)"
        << "| " << setw(24) << "Специфика приложения" << "|\n";
    cout << line << "\n";

    for (size_t i = 0; i < apps.size(); ++i) {
        cout << left << "| " << setw(3) << (i + 1);
        apps[i]->print(cout);
    }
    cout << line << "\n";
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const string filename = "apps.txt";
    initRegistry();
    createDefaultFileIfNotExists(filename);

    vector<unique_ptr<MobileApp>> apps;
    int choice = -1;

    while (choice != 0) {
        cout << "\n================ МЕНЮ УЧЕТА ПРИЛОЖЕНИЙ ================\n"
            << "1. Добавить (Паттерн 1: Фабричный метод по умолчанию)\n"
            << "2. Добавить с параметрами (Паттерн 2: Фабричный метод с аргументами)\n"
            << "3. Добавить через реестр (Паттерн 3: Фабричный конструктор)\n"
            << "4. Клонировать существующее (Паттерн 5: Полиморфное копирование)\n"
            << "5. Показать текущий список на экране (Паттерн 4: Модули)\n"
            << "6. Редактировать приложение\n"
            << "7. Удалить приложение\n"
            << "8. Сохранить текущий список в файл (" << filename << ")\n"
            << "9. Прочитать данные из файла (" << filename << ") и показать\n"
            << "0. Выход\n"
            << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            int t = chooseAppType();
            unique_ptr<MobileApp> app = makeAppSimple(static_cast<AppType>(t));
            if (app) {
                apps.push_back(move(app));
                cout << "Приложение создано через простой фабричный метод!\n";
            }
        }
        else if (choice == 2) {
            int t = chooseAppType();
            string name;
            double ver;
            cout << "Введите название: ";
            getline(cin >> ws, name);
            cout << "Введите версию: ";
            cin >> ver;

            unique_ptr<AppSpec> spec;
            if (t == GAME_APP) {
                string genre;
                cout << "Введите жанр: ";
                getline(cin >> ws, genre);
                spec = make_unique<GameAppSpec>(name, ver, genre);
            }
            else if (t == SOCIAL_APP) {
                int maxG;
                cout << "Макс. размер группы: ";
                cin >> maxG;
                spec = make_unique<SocialAppSpec>(name, ver, maxG);
            }
            else if (t == FINANCE_APP) {
                string curr;
                cout << "Валюта: ";
                cin >> curr;
                spec = make_unique<FinanceAppSpec>(name, ver, curr);
            }
            else if (t == EDUCATION_APP) {
                string subj;
                cout << "Предмет: ";
                getline(cin >> ws, subj);
                spec = make_unique<EducationAppSpec>(name, ver, subj);
            }
            else if (t == UTILITY_APP) {
                bool root;
                cout << "Нужен Root (1/0): ";
                cin >> root;
                spec = make_unique<UtilityAppSpec>(name, ver, root);
            }

            if (spec) {
                apps.push_back(makeAppWithArgs(spec.get()));
                cout << "Приложение создано с передачей аргументов!\n";
            }
        }
        else if (choice == 3) {
            int id = chooseAppType();
            unique_ptr <MobileApp> app = MobileApp::createFromRegistry(id);
            if (app) {
                apps.push_back(move(app));
                cout << "Приложение создано через динамический реестр!\n";
            }
        }
        else if (choice == 4) {
            showAll(apps);
            if (!apps.empty()) {
                int idx;
                cout << "Введите номер приложения для копирования: ";
                cin >> idx;
                if (idx >= 1 && idx <= static_cast<int>(apps.size())) {
                    apps.push_back(apps[idx - 1]->cloneUnique());
                    cout << "Копия успешно создана!\n";
                }
            }
        }
        else if (choice == 5) {
            showAll(apps);
        }
        else if (choice == 6) {
            showAll(apps);
            if (!apps.empty()) {
                int idx;
                cout << "Введите номер приложения для редактирования: ";
                cin >> idx;
                 if (idx >= 1 && idx <= static_cast<int>(apps.size())) {
                    apps[idx - 1]->edit();
                    cout << "Данные обновлены!\n";
                }
            }
        }
        else if (choice == 7) {
            showAll(apps);
            if (!apps.empty()) {
                int idx;
                cout << "Введите номер приложения для удаления: ";
                cin >> idx;
                if (idx >= 1 && idx <= static_cast<int>(apps.size())) {
                    
                    apps.erase(apps.begin() + (idx - 1));
                    cout << "Приложение удалено!\n";
                }
            }
        }
        else if (choice == 8) {
            saveAllToFile(filename, apps);
        }
        else if (choice == 9) {
            loadFromFile(filename, apps);
            showAll(apps);
        }
    }

    
    return 0;
}
