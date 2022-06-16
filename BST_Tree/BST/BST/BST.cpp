#include <iostream>
#include "BST_Tree.cpp"
#include "menu.hpp"
#include <ctime>
#include <random>
#include <cmath>

typedef unsigned long long INT_64;

using namespace std;

// вариант 4 (Алгоритмы операций поиска, вставки и удаления реализуются в
//итеративной форме.
// Вывод на экран последовательности ключей при обходе узлов дерева по схеме t → Lt → Rt.
// Дополнительная операция : определение в дереве количества узлов с ключами, бо´льшими заданного значения.Трудоёмкость операции – O(log n).)

static INT_64 RRand = 15750;
const  INT_64 mRand = (1 << 63) - 1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

void sRand() {
    srand(time(0));
    RRand = (INT_64)rand();
}

INT_64 LineRand()
{
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

void test_rand(int n) {
    BST_Tree<INT_64, int> tree;
    int q = 1;
    INT_64* array = new INT_64[n];

    sRand();

    for (int i = 0; i < n; i++) {
        array[i] = LineRand();
        tree.insert(array[i], q);
    }

    cout << "items count:" << tree.getSize() << endl;

    double I = 0;
    double D = 0;
    double S = 0;
    tree.clearCountNodes();
    for (int i = 0; i < n / 2; i++) 
        if (i % 10 == 0) {
            tree.clearCountNodes();
            tree.remove(LineRand());
            D += tree.getCountNodes();
            tree.clearCountNodes();
            tree.insert(array[rand() % n], q);
            I += tree.getCountNodes();
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(LineRand());
                S += tree.getCountNodes();
            }
            catch (const exception ex) {
                S += tree.getCountNodes();
            }


        }
    
        else {
            int ind = rand() % n;
            tree.clearCountNodes();
            tree.remove(array[ind]);
            D += tree.getCountNodes();
            INT_64 key = LineRand();
            tree.clearCountNodes();
            tree.insert(key, q);
            I += tree.getCountNodes();
            array[ind] = key;
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(array[rand() % n]);
                S += tree.getCountNodes();

            }
            catch (const exception ex) {
                S += tree.getCountNodes();
            }
        }

        cout << "items count: " << tree.getSize() << endl;

        cout << "1.39 * log2(n) = " << 1.39 * (log((double)n) / log(2.0)) << endl;

        cout << "Count insert: " << I / (n / 2) << endl;
        cout << "Count delete: " << D / (n / 2) << endl;
        cout << "Count search: " << S / (n / 2) << endl;

        delete[] array;

}


void test_ord(int n) {
    BST_Tree<INT_64, int> tree;

    INT_64* arr = new INT_64[n];
    int q = 1;
    //заполнение дерева и массива элементами 
// с возрастающими чётными ключами 
//на интервале [0, 10000, 20000, ... ,10000*n] 
    for (int i = 0; i < n; i++) {
        arr[i] = i * 10000;
        tree.insert(arr[i], q);
    }
    //вывод размера дерева до теста 
    cout << "items count:" << tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, 
    // удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;

    //установка первого случайного числа 
    sRand();
    //генерация потока операций, 10% - промахи операций
    tree.clearCountNodes();
    for (int i = 0; i < n / 2; i++)
    {
        if (i % 10 == 0) //10% промахов
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); //случайный нечётный ключ
            tree.clearCountNodes();
            tree.remove(k);
            D += tree.getCountNodes();
            tree.clearCountNodes();
            tree.insert(arr[rand() % n], q);
            I += tree.getCountNodes();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); // случайный нечётный ключ
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(k);
                S += tree.getCountNodes();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception ex) { S += tree.getCountNodes(); }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.clearCountNodes();
            tree.remove(arr[ind]);
            D += tree.getCountNodes();
            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.clearCountNodes();
            tree.insert(k, q);
            I += tree.getCountNodes();
            arr[ind] = k;
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(arr[rand() % n]);
                S += tree.getCountNodes();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception ex) { S += tree.getCountNodes(); }
        }
    }
    //вывод результатов: 
    // вывод размера дерева после теста
    cout << "items count:" << tree.getSize() << endl;

    //теоретической оценки трудоёмкости операций BST 
    cout << "n/2 =" << n / 2 << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[] 
    delete[] arr;
}





int main() {
    setlocale(0, "");
    int choice = -1;
    BST_Tree<int, int> tree;
    BST_Tree<int, int>::Iterator it(tree);
    BST_Tree<int, int>::reverseIterator rit(tree);
    BST_Tree<int, int>::Iterator b;
    BST_Tree<int, int>::reverseIterator rb;
    BST_Tree<int, int>::Iterator end;
    BST_Tree<int, int>::reverseIterator rend;

    menu();
    int value, key, newValue, treeSize;
    int key2 = 0;
    while (choice != 0) {
        
        cout << endl;
        cout << endl;
        cout << ">>>  ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            treeSize = tree.getSize();
            cout << treeSize << endl;
            break;
        case 2:
            cout << tree.clear_tree();
            
            break;
        case 3:
            cout << tree.is_clear_tree() << endl;
            break;
        case 4:
            cin >> key;
            try
            {
                cout << tree.getByWriteAndRead(key) << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 5:
            cin >> key >> newValue;
            try
            {
                tree.getByWriteAndRead(key) = newValue;
                //tree.insert(key, value);
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 6:
            cin >> key;
            cin >> value;
            cout << tree.insert(key, value) << endl;
            break;
        case 7:
            cin >> key;
            cout << tree.remove(key) << endl;
            break;
        case 8:
            tree.printTree();
            cout << endl;
            break;
        case 9:
            cin >> value;
            cout << tree.getCountKeysHigherThanInserted(value) << endl;
            tree.setCounterKey(0);
            break;
        case 10:
            it = tree.begin();
            break;
        case 11:
            it = tree.end();
            break;
        case 12:
            try
            {
                cout << *it << endl;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 13:
            cin >> newValue;
            try
            {
                *it = newValue;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 14:
            try
            {
                ++it;
            }
            catch (const exception e)
            {
                cerr << e.what();
            }
            break;
        case 15:
            b = tree.begin();
            cout << (b == it) << endl;
            break;
        case 16:
            end = tree.end();
            cout << (it == end) << endl;
            break;
        case 17:
            b = tree.begin();
            cout << (b != it) << endl;
            break;
        case 18:
            end = tree.end();
            cout << (it != end) << endl;
            break;
        case 19:
            rit = tree.rbegin();
            break;
        case 20:
            rit = tree.rend();
            break;
        case 21:
            try {
                cout << *rit << endl;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 22:
            try {
                cin >> *rit;
                
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 23:
            try {
                ++rit;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 24:
            rb = tree.rbegin();
            cout << (rb == rit) << endl;
            break;
        case 25:
            rend = tree.rend();
            cout << (rit == rend) << endl;
            break;
        case 26:
            rb = tree.rbegin();
            cout << (rb != rit) << endl;
            break;
        case 27:
            rend = tree.rend();
            cout << (rit != rend) << endl;
            break;
        case 28:
            test_rand(5000);
            
            cout << endl;
            break;
        case 29:
            //test_ord(100);
            //test_ord(500);
            //test_ord(1000);
            //test_ord(1500);
            //test_ord(2000);
            //test_ord(3000);
            //test_ord(5000);
            //test_ord(10000);
            //test_ord(15000);
            test_ord(5000);
            break;
        case 30:
            choice = 0;
            break;
        case 31:
            menu();
            break;
        }
        
    }
    return 0;
}