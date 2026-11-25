#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <string>
#include <windows.h>

#include "Developer.h"
#include "MobileApp.h"
#include "UtilityApp.h"
#include "EnterpriseApp.h"

using namespace std;

struct PriceChangeRecord {
    MobileApp* app;
    double oldPrice;

    PriceChangeRecord(MobileApp* a = nullptr, double p = 0.0) : app(a), oldPrice(p) {}
};

void printAppsTable(const vector<MobileApp*>& apps, ostream& os) {
    const int tableWidth = 128;

    os << setfill('=') << setw(tableWidth) << "" << setfill(' ') << "\n"
        << "| " << left << setw(20) << "Название"
        << " | " << setw(7) << "Рейтинг"
        << " | " << setw(20) << "Цена"
        << " | " << setw(34) << "Ведущий разраб."
        << " | " << setw(25) << "Специфика" << " |\n"
        << setfill('-') << setw(tableWidth) << "" << setfill(' ') << "\n";

    for (size_t i = 0; i < apps.size(); ++i) {
        if (apps[i] != nullptr) {
            apps[i]->printTableRow(os);
        }
    }

    os << setfill('=') << setw(tableWidth) << "" << setfill(' ') << "\n";
}

struct AppItem {
    MobileApp* app;

    AppItem(MobileApp* a = nullptr) : app(a) {}
};

bool operator<(const AppItem& a, const AppItem& b) {
    if (!a.app || !b.app) return false;
    return a.app->getRating() < b.app->getRating();
}

bool operator>(const AppItem& a, const AppItem& b) {
    if (!a.app || !b.app) return false;
    return a.app->getRating() > b.app->getRating();
}

typedef priority_queue<AppItem, vector<AppItem>, less<vector<AppItem>::value_type> > PriorityDescQueue;
typedef priority_queue<AppItem, vector<AppItem>, greater<vector<AppItem>::value_type> > PriorityAscQueue;

void clearInputLine() {
    cin.clear();
    cin.ignore(32767, '\n');
}

void dumpQueue(queue<MobileApp*> q, ostream& os) {
    if (q.empty()) {
        os << "Очередь релиза пуста.\n";
        return;
    }
    vector<MobileApp*> temp;
    while (!q.empty()) {
        temp.push_back(q.front());
        q.pop();
    }
    printAppsTable(temp, os);
}

void dumpStack(stack<MobileApp*> st, ostream& os) {
    if (st.empty()) {
        os << "Стек истории пуст.\n";
        return;
    }
    vector<MobileApp*> temp;
    while (!st.empty()) {
        temp.push_back(st.top());
        st.pop();
    }
    printAppsTable(temp, os);
}

void dumpPriorityDesc(PriorityDescQueue pq, ostream& os) {
    if (pq.empty()) {
        os << "Очередь приоритета пуста.\n";
        return;
    }
    vector<MobileApp*> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top().app);
        pq.pop();
    }
    printAppsTable(temp, os);
}

MobileApp* findOrEditInQueue(queue<MobileApp*>& q, const string& targetName, bool editMode, double newRating) {
    queue<MobileApp*> temp;
    MobileApp* found = nullptr;

    while (!q.empty()) {
        MobileApp* cur = q.front();
        q.pop();
        if (cur && cur->getName() == targetName) {
            found = cur;
            if (editMode) {
                cur->setRating(newRating);
            }
        }
        temp.push(cur);
    }
    q = temp;
    return found;
}

void filterQueueByMinRating(queue<MobileApp*> q, double minRating, ostream& os) {
    vector<MobileApp*> matched;
    while (!q.empty()) {
        MobileApp* cur = q.front();
        q.pop();
        if (cur && cur->getRating() >= minRating) {
            matched.push_back(cur);
        }
    }
    if (matched.empty()) {
        os << "Приложений с рейтингом >= " << minRating << " не найдено.\n";
    }
    else {
        printAppsTable(matched, os);
    }
}

bool compareAppPtrByPriceAsc(MobileApp* a, MobileApp* b) {
    if (!a || !b) return false;
    return a->getPrice() < b->getPrice();
}

void sortQueueByPrice(queue<MobileApp*>& q) {
    vector<MobileApp*> items;
    while (!q.empty()) {
        items.push_back(q.front());
        q.pop();
    }
    sort(items.begin(), items.end(), compareAppPtrByPriceAsc);
    for (size_t i = 0; i < items.size(); ++i) {
        q.push(items[i]);
    }
}

MobileApp* findInStackAndPushTop(stack<MobileApp*>& st, const string& targetName) {
    stack<MobileApp*> rev;
    MobileApp* found = nullptr;

    while (!st.empty()) {
        MobileApp* cur = st.top();
        st.pop();
        if (!found && cur && cur->getName() == targetName) {
            found = cur;
        }
        else {
            rev.push(cur);
        }
    }

    while (!rev.empty()) {
        st.push(rev.top());
        rev.pop();
    }

    if (found) {
        st.push(found);
    }
    return found;
}

bool editPriceInStackWithUndo(stack<MobileApp*>& st, stack<PriceChangeRecord>& undoStack, const string& targetName, double newPrice) {
    stack<MobileApp*> rev;
    bool updated = false;

    while (!st.empty()) {
        MobileApp* cur = st.top();
        st.pop();
        if (!updated && cur && cur->getName() == targetName) {
            undoStack.push(PriceChangeRecord(cur, cur->getPrice()));
            cur->setPrice(newPrice);
            updated = true;
        }
        rev.push(cur);
    }

    while (!rev.empty()) {
        st.push(rev.top());
        rev.pop();
    }

    return updated;
}

void filterStackByMinRating(stack<MobileApp*> st, double minRating, ostream& os) {
    vector<MobileApp*> matched;
    while (!st.empty()) {
        MobileApp* cur = st.top();
        st.pop();
        if (cur && cur->getRating() >= minRating) {
            matched.push_back(cur);
        }
    }
    if (matched.empty()) {
        os << "Приложений с рейтингом >= " << minRating << " не найдено.\n";
    }
    else {
        printAppsTable(matched, os);
    }
}

void sortStackByPrice(stack<MobileApp*>& st) {
    vector<MobileApp*> items;
    while (!st.empty()) {
        items.push_back(st.top());
        st.pop();
    }
    sort(items.begin(), items.end(), compareAppPtrByPriceAsc);
    for (size_t i = 0; i < items.size(); ++i) {
        st.push(items[i]);
    }
}

MobileApp* findInPriorityDesc(PriorityDescQueue pq, const string& targetName) {
    while (!pq.empty()) {
        MobileApp* cur = pq.top().app;
        pq.pop();
        if (cur && cur->getName() == targetName) {
            return cur;
        }
    }
    return nullptr;
}

bool editRatingInPriorityQueues(PriorityDescQueue& pqDesc, PriorityAscQueue& pqAsc, const string& targetName, double newRating) {
    vector<MobileApp*> items;
    bool found = false;

    while (!pqDesc.empty()) {
        items.push_back(pqDesc.top().app);
        pqDesc.pop();
    }
    while (!pqAsc.empty()) {
        pqAsc.pop();
    }

    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] && items[i]->getName() == targetName) {
            items[i]->setRating(newRating);
            found = true;
        }
        if (items[i]) {
            pqDesc.push(AppItem(items[i]));
            pqAsc.push(AppItem(items[i]));
        }
    }
    return found;
}

void filterPriorityDescByMinRating(PriorityDescQueue pq, double minRating, ostream& os) {
    vector<MobileApp*> matched;
    while (!pq.empty()) {
        MobileApp* cur = pq.top().app;
        pq.pop();
        if (cur && cur->getRating() >= minRating) {
            matched.push_back(cur);
        }
    }
    if (matched.empty()) {
        os << "Приложений с рейтингом >= " << minRating << " не найдено.\n";
    }
    else {
        printAppsTable(matched, os);
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    list<Developer> staffList;
    staffList.push_back(Developer("Иванов Иван", "TeamLead iOS", 7));
    staffList.push_back(Developer("Петров Петр", "Senior Android Dev", 5));
    staffList.push_back(Developer("Сидорова Анна", "Middle Flutter Dev", 3));

    list<Developer>::iterator it1 = staffList.begin();
    list<Developer>::iterator it2 = staffList.begin();
    advance(it2, 1);
    list<Developer>::iterator it3 = staffList.begin();
    advance(it3, 2);

    Developer* dev1 = &(*it1);
    Developer* dev2 = &(*it2);
    Developer* dev3 = &(*it3);

    UtilityApp* app1 = new UtilityApp("Fitness Tracker", 4.8, 0.0, dev1, true, "Android 11+");
    EnterpriseApp* app2 = new EnterpriseApp("SberBank Mobile", 4.9, 1500000.0, dev2, "ПАО Сбербанк", "ГОСТ-34.12");
    UtilityApp* app3 = new UtilityApp("Photo Editor Pro", 4.2, 299.0, dev1, false, "Android 9+");
    UtilityApp* app4 = new UtilityApp("Weather Forecast", 4.6, 149.0, dev3, false, "Android 8+");

    vector<MobileApp*> allAllocatedApps;
    allAllocatedApps.push_back(app1);
    allAllocatedApps.push_back(app2);
    allAllocatedApps.push_back(app3);
    allAllocatedApps.push_back(app4);

    queue<MobileApp*> releaseQueue;
    stack<MobileApp*> historyStack;
    stack<PriceChangeRecord> priceUndoStack;
    PriorityDescQueue pqDesc;
    PriorityAscQueue pqAsc;

    for (size_t i = 0; i < allAllocatedApps.size(); ++i) {
        releaseQueue.push(allAllocatedApps[i]);
        historyStack.push(allAllocatedApps[i]);
        pqDesc.push(AppItem(allAllocatedApps[i]));
        pqAsc.push(AppItem(allAllocatedApps[i]));
    }

    int mainChoice = -1;
    do {
        cout << "\n======================================================\n";
        cout << "                  ГЛАВНОЕ МЕНЮ                        \n";
        cout << "======================================================\n";
        cout << " 1. Очередь релиза                    \n";
        cout << " 2. История и откат цены              \n";
        cout << " 3. Приоритет по рейтингу            \n";
        cout << " 0. Выход                                             \n";
        cout << "------------------------------------------------------\n";
        cout << "Выберите пункт: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1: {
            int subChoice = -1;
            do {
                cout << "\n--- QUEUE (ОЧЕРЕДЬ РЕЛИЗА: ПЕРВЫМ ПРИШЕЛ — ПЕРВЫМ ВЫШЕЛ) ---\n";
                cout << " 1. Показать очередь релиза\n";
                cout << " 2. Поставить новую сборку в конец очереди (push)\n";
                cout << " 3. Выпустить первую сборку из очереди (front + pop)\n";
                cout << " 4. Найти сборку по названию\n";
                cout << " 5. Обновить рейтинг сборки в очереди\n";
                cout << " 6. Фильтр по минимальному рейтингу\n";
                cout << " 7. Упорядочить очередь по цене\n";
                cout << " 8. Сохранить отчет очереди в файл (queue_report.txt)\n";
                cout << " 0. Назад в главное меню\n";
                cout << "Выбор: ";
                cin >> subChoice;

                switch (subChoice) {
                case 1: {
                    dumpQueue(releaseQueue, cout);
                    break;
                }
                case 2: {
                    string name;
                    double rating, price;
                    cout << "Название: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Рейтинг: ";
                    cin >> rating;
                    cout << "Цена: ";
                    cin >> price;

                    MobileApp* created = new UtilityApp(name, rating, price, dev1, false, "Android 10+");
                    allAllocatedApps.push_back(created);
                    releaseQueue.push(created);
                    pqDesc.push(AppItem(created));
                    pqAsc.push(AppItem(created));
                    cout << "Сборка добавлена в конец очереди релиза.\n";
                    break;
                }
                case 3: {
                    if (!releaseQueue.empty()) {
                        MobileApp* nextApp = releaseQueue.front();
                        releaseQueue.pop();
                        cout << "Выпущена самая ранняя заявка из очереди:\n";
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(nextApp);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Очередь релиза пуста.\n";
                    }
                    break;
                }
                case 4: {
                    string name;
                    cout << "Введите название для поиска: ";
                    clearInputLine();
                    getline(cin, name);
                    MobileApp* found = findOrEditInQueue(releaseQueue, name, false, 0.0);
                    if (found) {
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(found);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 5: {
                    string name;
                    double newRating;
                    cout << "Введите название приложения: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Новый рейтинг: ";
                    cin >> newRating;
                    MobileApp* found = findOrEditInQueue(releaseQueue, name, true, newRating);
                    if (found) {
                        cout << "Рейтинг обновлен.\n";
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 6: {
                    double minRating;
                    cout << "Минимальный рейтинг: ";
                    cin >> minRating;
                    filterQueueByMinRating(releaseQueue, minRating, cout);
                    break;
                }
                case 7: {
                    sortQueueByPrice(releaseQueue);
                    cout << "Очередь упорядочена по цене (по возрастанию).\n";
                    break;
                }
                case 8: {
                    ofstream fout("queue_report.txt");
                    fout << "=== ОТЧЕТ ПО КОНТЕЙНЕРУ QUEUE (ОЧЕРЕДЬ РЕЛИЗА) ===\n\n";
                    dumpQueue(releaseQueue, fout);
                    fout.close();
                    cout << "Сохранено в queue_report.txt\n";
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Неверный выбор.\n";
                    break;
                }
            } while (subChoice != 0);
            break;
        }
        case 2: {
            int subChoice = -1;
            do {
                cout << "\n--- STACK (ИСТОРИЯ И ОТКАТ ЦЕНЫ: ПОСЛЕДНИМ ПРИШЕЛ — ПЕРВЫМ ВЫШЕЛ) ---\n";
                cout << " 1. Показать стек истории (сверху вниз)\n";
                cout << " 2. Добавить приложение на вершину стека (push)\n";
                cout << " 3. Закрыть верхнее приложение \n";
                cout << " 4. Найти приложение и поднять на вершину истории\n";
                cout << " 5. Изменить цену приложения (с записью в стек отката)\n";
                cout << " 6. Откатить последнее изменение цены (LIFO)\n";
                cout << " 7. Фильтр по минимальному рейтингу\n";
                cout << " 8. Упорядочить стек по цене\n";
                cout << " 9. Сохранить отчет стека в файл (stack_report.txt)\n";
                cout << " 0. Назад в главное меню\n";
                cout << "Выбор: ";
                cin >> subChoice;

                switch (subChoice) {
                case 1: {
                    dumpStack(historyStack, cout);
                    break;
                }
                case 2: {
                    string name;
                    double rating, price;
                    cout << "Название: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Рейтинг: ";
                    cin >> rating;
                    cout << "Цена: ";
                    cin >> price;

                    MobileApp* created = new UtilityApp(name, rating, price, dev2, false, "iOS 16+");
                    allAllocatedApps.push_back(created);
                    historyStack.push(created);
                    cout << "Приложение помещено на вершину стека.\n";
                    break;
                }
                case 3: {
                    if (!historyStack.empty()) {
                        MobileApp* topApp = historyStack.top();
                        historyStack.pop();
                        cout << "Снят верхний элемент стека:\n";
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(topApp);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Стек пуст.\n";
                    }
                    break;
                }
                case 4: {
                    string name;
                    cout << "Введите название для поиска: ";
                    clearInputLine();
                    getline(cin, name);
                    MobileApp* found = findInStackAndPushTop(historyStack, name);
                    if (found) {
                        cout << "Найдено и перемещено на вершину истории:\n";
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(found);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 5: {
                    string name;
                    double newPrice;
                    cout << "Введите название приложения: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Новая цена: ";
                    cin >> newPrice;
                    if (editPriceInStackWithUndo(historyStack, priceUndoStack, name, newPrice)) {
                        cout << "Цена обновлена (предыдущее значение сохранено в стеке отката).\n";
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 6: {
                    if (!priceUndoStack.empty()) {
                        PriceChangeRecord rec = priceUndoStack.top();
                        priceUndoStack.pop();
                        if (rec.app) {
                            rec.app->setPrice(rec.oldPrice);
                            cout << "Откачена цена для \"" << rec.app->getName()
                                << "\" -> " << fixed << setprecision(2) << rec.oldPrice << " руб.\n";
                        }
                    }
                    else {
                        cout << "Стек откатов цены пуст.\n";
                    }
                    break;
                }
                case 7: {
                    double minRating;
                    cout << "Минимальный рейтинг: ";
                    cin >> minRating;
                    filterStackByMinRating(historyStack, minRating, cout);
                    break;
                }
                case 8: {
                    sortStackByPrice(historyStack);
                    cout << "Стек упорядочен по цене.\n";
                    break;
                }
                case 9: {
                    ofstream fout("stack_report.txt");
                    fout << "=== ОТЧЕТ ПО КОНТЕЙНЕРУ STACK (ИСТОРИЯ) ===\n\n";
                    dumpStack(historyStack, fout);
                    fout.close();
                    cout << "Сохранено в stack_report.txt\n";
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Неверный выбор.\n";
                    break;
                }
            } while (subChoice != 0);
            break;
        }
        case 3: {
            int subChoice = -1;
            do {
                cout << "\n--- PRIORITY_QUEUE (ПРИОРИТЕТ ПО РЕЙТИНГУ) ---\n";
                cout << " 1. Вывести по убыванию рейтинга (максимум на вершине)\n";
                cout << " 2. Добавить приложение\n";
                cout << " 3. Извлечь элемент с наивысшим рейтингом \n";
                cout << " 4. Найти приложение по названию\n";
                cout << " 5. Редактировать рейтинг и пересчитать приоритеты\n";
                cout << " 6. Фильтр по минимальному рейтингу\n";
                cout << " 7. Вывести от меньшего рейтинга к большему\n";
                cout << " 8. Сохранить отчет в файл (pqueue_report.txt)\n";
                cout << " 0. Назад в главное меню\n";
                cout << "Выбор: ";
                cin >> subChoice;

                switch (subChoice) {
                case 1: {
                    dumpPriorityDesc(pqDesc, cout);
                    break;
                }
                case 2: {
                    string name;
                    double rating, price;
                    cout << "Название: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Рейтинг: ";
                    cin >> rating;
                    cout << "Цена: ";
                    cin >> price;

                    MobileApp* created = new UtilityApp(name, rating, price, dev3, true, "Android 12+");
                    allAllocatedApps.push_back(created);
                    pqDesc.push(AppItem(created));
                    pqAsc.push(AppItem(created));
                    cout << "Добавлено в очередь с приоритетом.\n";
                    break;
                }
                case 3: {
                    if (!pqDesc.empty()) {
                        MobileApp* topApp = pqDesc.top().app;
                        pqDesc.pop();
                        cout << "Извлечен самый приоритетный элемент:\n";
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(topApp);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Очередь с приоритетом пуста.\n";
                    }
                    break;
                }
                case 4: {
                    string name;
                    cout << "Введите название для поиска: ";
                    clearInputLine();
                    getline(cin, name);
                    MobileApp* found = findInPriorityDesc(pqDesc, name);
                    if (found) {
                        vector<MobileApp*> oneItem;
                        oneItem.push_back(found);
                        printAppsTable(oneItem, cout);
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 5: {
                    string name;
                    double newRating;
                    cout << "Введите название приложения: ";
                    clearInputLine();
                    getline(cin, name);
                    cout << "Новый рейтинг: ";
                    cin >> newRating;
                    if (editRatingInPriorityQueues(pqDesc, pqAsc, name, newRating)) {
                        cout << "Рейтинг обновлен, приоритеты пересчитаны.\n";
                    }
                    else {
                        cout << "Приложение не найдено.\n";
                    }
                    break;
                }
                case 6: {
                    double minRating;
                    cout << "Минимальный рейтинг: ";
                    cin >> minRating;
                    filterPriorityDescByMinRating(pqDesc, minRating, cout);
                    break;
                }
                case 7: {
                    PriorityAscQueue copyAsc = pqAsc;
                    vector<MobileApp*> ascList;
                    while (!copyAsc.empty()) {
                        ascList.push_back(copyAsc.top().app);
                        copyAsc.pop();
                    }
                    printAppsTable(ascList, cout);
                    break;
                }
                case 8: {
                    ofstream fout("pqueue_report.txt");
                    fout << "=== ОТЧЕТ ПО PRIORITY_QUEUE ===\n\n";
                    dumpPriorityDesc(pqDesc, fout);
                    fout.close();
                    cout << "Сохранено в pqueue_report.txt\n";
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Неверный выбор.\n";
                    break;
                }
            } while (subChoice != 0);
            break;
        }
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор.\n";
            break;
        }
    } while (mainChoice != 0);

    for (size_t i = 0; i < allAllocatedApps.size(); ++i) {
        delete allAllocatedApps[i];
    }

    return 0;
}