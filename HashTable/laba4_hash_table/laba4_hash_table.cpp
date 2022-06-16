#include <iostream>
#include "HashTable.h"
#include "HashChain.h"
#include "HashOpen.h"
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

typedef int TYPE;

int cinKey() {
    while (1) {
        cout << "Введите ключ на интервале [100000000; 300000000]: ";
        int x;
        cin >> x;
        if (x >= 100000000 and x <= 300000000) return x;
        cout << "Неверное значение!.\n";
    }
}

int Hash(int key, int size) {
    int pair1 = key / 1000000;
    int pair2 = key / 1000 % 1000;
    int pair3 = key % 1000;
    return (((pair1^1 + pair2^2 + pair3^3) % 1000) % size);
}

void TestHashFunc(int size) {
    srand(time(0));
    
    int* arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = 0;

    for (int i = 0; i < 20*size; i++) {
        int key = rand() % 200000000 + 100000000;
        int k = Hash(key, size);
        
        arr[k]++;
    }
    
    double sum = 0;
    double hi2 = 0;
    for (int i = 0; i < size; i++) {
        sum += (arr[i] - 20) * (arr[i] - 20);
    }
    sum = sum / 20;
    cout << "m-sqrt(m) " << (double)(size - sqrt((double)size)) << endl;
    cout << "Xi^2: " << sum << endl;
    cout << "m+sqrt(m) " << (double)(size + sqrt((double)size)) << endl;
    delete[] arr;
}

void TestHashTable(double alpha, bool isChain, int size) {
    srand(time(0));
    double ins, fnd, del;
    ins = fnd = del = 0;
    HashTable<TYPE, TYPE>* ht;
    if (isChain)
        ht = new HashChain<>(size);
    else
        ht = new HashOpen<>(size);
    int count = (int)(alpha * ht->getSize());
    int* arr = new int[count];
    for (int i = 0; i < count; i++) {
        int key = rand() % 200000000 + 100000000;
        ht->insert(key, i);
        arr[i] = key;
    }
    ht->getViewCount();
    cout << "Размер до " << ht->getCount() << endl;
    for (int i = 0; i < count / 2; i++) {
        if (i % 10 != 0) {
            int index = rand() % count;
            ht->remove(arr[index]);
            del += ht->getViewCount();
            int x = rand() % 200000000 + 100000000;
            arr[index] = x;
            ht->insert(x, 1);
            ins += ht->getViewCount();
            index = rand() % count;
            try {
                ht->search(arr[index]);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        }
        else {
            int x = rand() % 200000000 + 100000000;
            ht->remove(x);
            del += ht->getViewCount();
            int index = rand() % count;
            ht->insert(arr[index], 1);
            ins += ht->getViewCount();
            x = rand() % 200000000 + 100000000;
            try {
                ht->search(x);
                fnd += ht->getViewCount();
            }
            catch (runtime_error) { fnd += ht->getViewCount(); }
        }
    }
    delete[] arr;
    cout << "Размер после " << ht->getCount() << endl;
    if (isChain)
        cout << "Вставка T " << 1 + alpha << endl;
    else
        cout << "Вставка T " << 0.1 * (-log(1 - alpha) / alpha) + 0.9 * (1 / (1 - alpha)) << endl;
    cout << "Вставка " << ins / (count / 2) << endl;
    if (isChain)
        cout << "Удаление T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Удаление T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Удаление " << del / (count / 2) << endl;
    if (isChain)
        cout << "Поиск T " << 0.1 * (1 + alpha) + 0.9 * (1 + alpha / 2) << endl;
    else
        cout << "Поиск T " << 0.9 * (-log(1 - alpha) / alpha) + 0.1 * (1 / (1 - alpha)) << endl;
    cout << "Поиск " << fnd / (count / 2) << endl;
    delete ht;
}


void clearConsole() {
    for (int i = 0; i < 20; ++i) {
        cout << endl;
    }
}

void showMenu(bool main = true) {
    
    if (main) {
        cout << "MENU\n"
            "1. Размер таблицы            \n"
            "2. Кол-во элементов в таблице    \n"
            "3. Проверка на пустоту таблицы             \n"
            "4. Очистить таблицу                 \n"
            "5. Поиск по ключу               \n"
            "6. Вставка по ключу                \n"
            "7. Удаление по ключу               \n"
            "8. Установить форму цепочек              \n"
            "9. Установить форму открытой адресации               \n"
            "10. Узнать текущую форму             \n"
            "11. Установить на начало                 \n"
            "12. Установить в конец                   \n"
            "13. Вывести таблицу на экран                \n"
            "14. Меню итератора              \n"
            "15. Меню для тестов                  \n"
            "0.  Выход                       \n"
            "\n"
            "Введите >>>  ";
    }
    else {
        cout << "MENU\n"
            "1. Инициализировать второй итератор      \n"
            "2. Записать (*)            \n"
            "3. Считать (*)             \n"
            "4. Операция (++)             \n"
            "5. Check equality              \n"
            "0.  Выход                       \n"
            "\n"
            "Введите >>> ";
    }
}




int main() {
    srand(time(0));
    setlocale(0, "");
    HashTable<TYPE, TYPE>* hashTable = nullptr;
    HashTable<TYPE, TYPE>::Iterator* iterator = nullptr;
    HashTable<TYPE, TYPE>::Iterator* iterator1 = nullptr;
    cout << "Выберите форму 1 - цепочки 2 - адресация\n Введите >>> ";
    int ans, size;
    cin >> ans;
    if (ans == 1) {
        cout << "Введите размер таблицы: ";
        cin >> size;
        hashTable = new HashChain<>(size);
    }
    else if (ans == 2) {
        cout << "Введите размер таблицы: ";
        cin >> size;
        hashTable = new HashOpen<>(size);
    }
    else {
        cout << "Форма не установлена!\n";
    }
    bool exit = true;
    while (exit) {
        showMenu();
        int x;
        cin >> x;
        switch (x) {
        case 1: {
            //clearConsole();
            if (hashTable) {
                cout << hashTable->getSize() << endl;
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 2: {
            //clearConsole();
            if (hashTable) {
                cout << hashTable->getCount() << endl;
            }
            else {
                cout << "Выберите форму\n";
            }
            break;
        }
        case 3: {
            //clearConsole();
            if (hashTable) {
                cout << boolalpha << hashTable->isEmpty() << endl;
            }
            else {
                cout << "Выберите форму\n";
            }
            break;
        }
        case 4: {
            //clearConsole();
            if (hashTable) {
                hashTable->clear();
            }
            else {
                cout << "Выберите форму\n";
            }
            break;
        }
        case 5: {
            //clearConsole();
            if (hashTable) {
                TYPE key = cinKey();
                try {
                    cout << hashTable->search(key) << endl;
                }
                catch (runtime_error e) {
                    cout << e.what() << endl;
                }
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 6: {
            //clearConsole();
            if (hashTable) {
                TYPE data, key = cinKey();
                cout << "Введите значение:";
                cin >> data;
                cout << boolalpha << hashTable->insert(key, data) << endl;
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 7: {
            //clearConsole();
            if (hashTable) {
                TYPE key = cinKey();
                cout << boolalpha << hashTable->remove(key) << endl;
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 8: {
            //clearConsole();
            cout << "Введите размер таблицы: ";
            int size;
            cin >> size;
            delete hashTable;
            hashTable = new HashChain<>(size);
            break;
        }
        case 9: {
            //clearConsole();
            cout << "Введите размер таблицы: ";
            int size;
            cin >> size;
            delete hashTable;
            hashTable = new HashOpen<>(size);
            break;
        }
        case 10: {
            //clearConsole();
            if (hashTable) {
                hashTable->showMode();
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 11: {
            //clearConsole();
            if (hashTable) {
                try {
                    iterator = hashTable->begin();
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 12: {
            //clearConsole();
            if (hashTable) {
                try {
                    iterator = hashTable->end();
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 13: {
            //clearConsole();
            if (hashTable) {
                hashTable->printHash();
            }
            else {
                cout << "Выберите форму!\n";
            }
            break;
        }
        case 14: {
            //clearConsole();
            if (iterator) {
                bool exit1 = true;
                while (exit1) {
                    showMenu(false);
                    int xx;
                    cin >> xx;
                    switch (xx) {
                    case 1: {
                        //clearConsole();
                        try {
                            cout << " begin(1) or end(2): ";
                            int value;
                            cin >> value;
                            if (value == 1) {
                                iterator1 = hashTable->begin();
                            }
                            else if (value == 2) {
                                iterator1 = hashTable->end();
                            }
                            else cout << "Неверный ввод!.\n";
                        }
                        catch (runtime_error error) {
                            cout << error.what() << endl;
                        }
                        break;
                    }
                    case 2: {
                        //clearConsole();
                        try {
                            if (iterator1) {
                                cout << "first(1) or second(2): ";
                                int it;
                                cin >> it;
                                cout << "Введите новое значение: ";
                                TYPE value;
                                cin >> value;
                                if (it == 1) {
                                    **iterator = value;
                                }
                                else if (it == 2) {
                                    **iterator1 = value;
                                }
                                else cout << "Неверный ввод!.\n";
                            }
                            else {
                                cout << "Введите новое значение: ";
                                TYPE value;
                                cin >> value;
                                **iterator = value;
                            }
                        }
                        catch (runtime_error error) {
                            cout << error.what() << endl;
                        }
                        break;
                    }
                    case 3: {
                        //clearConsole();
                        try {
                            if (iterator1) {
                                cout << "first(1) or second(2): ";
                                int it;
                                cin >> it;
                                if (it == 1) {
                                    cout << **iterator << endl;
                                }
                                else if (it == 2) {
                                    cout << **iterator1 << endl;
                                }
                                else cout << "Неверный ввод!.\n";
                            }
                            else {
                                cout << **iterator << endl;
                            }
                        }
                        catch (runtime_error error) {
                            cout << error.what() << endl;
                        }
                        break;
                    }
                    case 4: {
                        //clearConsole();
                        try {
                            if (iterator1) {
                                cout << "first(1) or second(2): ";
                                int it;
                                cin >> it;
                                if (it == 1) {
                                    ++* iterator;
                                }
                                else if (it == 2) {
                                    ++* iterator1;
                                }
                                else cout << "Неверный ввод!.\n";
                            }
                            else {
                                ++* iterator;
                            }
                        }
                        catch (runtime_error error) {
                            cout << error.what() << endl;
                        }
                        break;
                    }
                    case 5: {
                        //clearConsole();
                        try {
                            cout << boolalpha << (*iterator == iterator1) << endl;
                        }
                        catch (runtime_error error) {
                            cout << error.what() << endl;
                        }
                        break;
                    }
                    case 0: {
                        clearConsole();
                        exit1 = false;
                        break;
                    }
                    default: {
                        cout << "Неккоректное значение!\n";
                        break;
                    }
                    }
                }
            }
            else {
                cout << "Для начала установите итератор!\n";
            }
            break;
        }
        case 15: {
            //clearConsole();
            bool test = true;
            int in;
            while (test) {
                cout << "MENU\n"
                    "1. Тест хеш функции          \n"
                    "2. Тест таблицы             \n"
                    "0.  Выход                       \n"
                    "\n"
                    "Введите >>> ";
                cin >> in;
                switch (in) {
                case 1: {
                    //clearConsole();
                    cout << "Введите размер: ";
                    int size;
                    cin >> size;
                    TestHashFunc(size);
                    break;
                }
                case 2: {
                    //clearConsole();
                    cout << "Введите альфа: ";
                    double alpha;
                    cin >> alpha;
                    cout << "Выберите форму: (1) - цепочки (0) - адресация : ";
                    bool form;
                    cin >> form;
                    cout << "Введите размер: ";
                    int size;
                    cin >> size;
                    TestHashTable(alpha, form, size);
                    break;
                }
                case 0: {
                    //clearConsole();
                    test = false;
                    break;
                }
                default: {
                    //clearConsole();
                    cout << "Неккоректный ввод!.\n";
                    break;
                }

                }
            }
            break;
        }
        case 0: {
            exit = false;
            break;
        }
        case 777: {
            //clearConsole();
            for (int i = 0; i < 5; ++i) {
                hashTable->insert(rand() % 200000000 + 100000000, i);
            }
            break;
        }
        case 999: {
            cout << hashTable->getViewCount() << endl;
            break;
        }

        default: {
            cout << "Неккоректное значение!\n";
            break;
        }

        }
    }
    return 0;
}

