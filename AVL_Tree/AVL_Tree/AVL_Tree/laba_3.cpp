#include <iostream>
#include "BST_Tree.cpp"
#include "AVL.cpp"
#include "menu.hpp"
#include <ctime>
#include <random>
#include <cmath>

typedef unsigned long long INT_64;

using namespace std;

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
    AVL_Tree<INT_64, int> avl_tree;
    int q = 1;
    INT_64* array = new INT_64[n];
    INT_64 key;
    int ind;
    sRand();

    for (int i = 0; i < n; i++) {
        array[i] = LineRand();
        tree.insert(array[i], q);
        avl_tree.insert(array[i], q);
    }

    cout << "items count(BST):" << tree.getSize() << endl;
    cout << "items count(AVL):" << avl_tree.getSize() << endl;
    double I = 0;
    double D = 0;
    double S = 0;
    double I2 = 0;
    double D2 = 0;
    double S2 = 0;
    tree.clearCountNodes();
    avl_tree.clearCountNodes();
    for (int i = 0; i < n / 2; i++)
        if (i % 10 == 0) {
            key = LineRand();

            tree.clearCountNodes();
            tree.remove(key);
            D += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.remove(key);
            D2 += avl_tree.getCountNodes();

            ind = rand() % n;

            tree.clearCountNodes();
            tree.insert(array[ind], q);
            I += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.insert(array[ind], q);
            I2 += avl_tree.getCountNodes();

            key = LineRand();

            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(LineRand());
                S += tree.getCountNodes();
            }
            catch (const exception ex) {
                S += tree.getCountNodes();
            }
            try {
                avl_tree.clearCountNodes();
                avl_tree.getByWriteAndRead(LineRand());
                S2 += avl_tree.getCountNodes();
            }
            catch (const exception ex) {
                S2 += avl_tree.getCountNodes();
            }


        }

        else {
            ind = rand() % n;
            tree.clearCountNodes();
            tree.remove(array[ind]);
            D += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.remove(array[ind]);
            D2 += avl_tree.getCountNodes();

            key = LineRand();

            tree.clearCountNodes();
            tree.insert(key, q);
            I += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.insert(key, q);
            I2 += avl_tree.getCountNodes();

            array[ind] = key;
            ind = rand() % n;
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(array[ind]);
                S += tree.getCountNodes();

            }
            catch (const exception ex) {
                S += tree.getCountNodes();
            }

            try {
                avl_tree.clearCountNodes();
                avl_tree.getByWriteAndRead(array[ind]);
                S2 += avl_tree.getCountNodes();
            }
            catch (const exception ex) {
                S2 += avl_tree.getCountNodes();
            }
        }

    cout << "items count(BST): " << tree.getSize() << endl;
    cout << "items count(AVL): " << avl_tree.getSize() << endl;

    cout << "1.39 * log2(n) = " << 1.39 * (log((double)n) / log(2.0)) << endl;
    cout << "0.25 + log2(n) = " << 0.25 + (log((double)n) / log(2.0)) << endl;

    cout << "Count insert(BST): " << I / (n / 2) << endl;
    cout << "Count insert(AVL): " << I2 / (n / 2) << endl;

    cout << "Count delete(BST): " << D / (n / 2) << endl;
    cout << "Count delete(AVL): " << D2 / (n / 2) << endl;

    cout << "Count search(BST): " << S / (n / 2) << endl;
    cout << "Count search(AVL): " << S2 / (n / 2) << endl;

    delete[] array;

}


void test_ord(int n) {
    BST_Tree<INT_64, int> tree;
    AVL_Tree<INT_64, int> avl_tree;
    INT_64* arr = new INT_64[n];
    int q = 1;
    //заполнение дерева и массива элементами 
// с возрастающими чётными ключами 
//на интервале [0, 10000, 20000, ... ,10000*n] 
    for (int i = 0; i < n; i++) {
        arr[i] = i * 10000;
        tree.insert(arr[i], q);
        avl_tree.insert(arr[i], q);
    }
    //вывод размера дерева до теста 
    cout << "items count(BST):" << tree.getSize() << endl;
    cout << "items count(AVL):" << avl_tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, 
    // удаления и поиска
    double I = 0, I2 = 0;
    double D = 0 , D2 = 0;
    double S = 0 , S2 = 0;

    //установка первого случайного числа 
    sRand();
    //генерация потока операций, 10% - промахи операций
    tree.clearCountNodes();
    avl_tree.clearCountNodes();
    for (int i = 0; i < n / 2; i++)
    {
        if (i % 10 == 0) //10% промахов
        {
            int k = LineRand() % (10000 * n);
            k = k + !(k % 2); //случайный нечётный ключ
            tree.clearCountNodes();
            tree.remove(k);
            D += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.remove(k);
            D2 += avl_tree.getCountNodes();

            int ind = rand() % n;

            tree.clearCountNodes();
            tree.insert(arr[ind], q);
            I += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.insert(arr[ind], q);
            I2 += avl_tree.getCountNodes();
            k = LineRand() % (10000 * n);
            k = k + !(k % 2); // случайный нечётный ключ
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(k);
                S += tree.getCountNodes();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception ex) { S += tree.getCountNodes(); }

            try {
                avl_tree.clearCountNodes();
                avl_tree.getByWriteAndRead(k);
                S2 += avl_tree.getCountNodes();
            }
            catch (const exception ex) {
                S2 += avl_tree.getCountNodes();
            }
        }
        else //90% успешных операций
        {
            int ind = rand() % n;
            tree.clearCountNodes();
            tree.remove(arr[ind]);
            D += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.remove(arr[ind]);
            D2 += avl_tree.getCountNodes();


            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            tree.clearCountNodes();
            tree.insert(k, q);
            I += tree.getCountNodes();

            avl_tree.clearCountNodes();
            avl_tree.insert(k, q);
            I2 += avl_tree.getCountNodes();


            arr[ind] = k;
            ind = rand() % n;
            try {
                tree.clearCountNodes();
                tree.getByWriteAndRead(arr[ind]);
                S += tree.getCountNodes();
            }
            //обработка исключения при ошибке операции поиска
            catch (const exception ex) { S += tree.getCountNodes(); }

            try {
                avl_tree.clearCountNodes();
                avl_tree.getByWriteAndRead(arr[ind]);
                S2 += avl_tree.getCountNodes();
            }
            catch (const exception ex) {
                S2 += avl_tree.getCountNodes();
            }

        }
    }
    //вывод результатов: 
    // вывод размера дерева после теста
    cout << "items count(BST):" << tree.getSize() << endl;
    cout << "items count(AVL):" << avl_tree.getSize() << endl;

    //теоретической оценки трудоёмкости операций BST 
    cout << "n/2 =" << n / 2 << endl;
    cout << "0.25 + log2(n) = " << 0.25 + (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert(BST): " << I / (n / 2) << endl;
    cout << "Count insert(AVL): " << I2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete(BST): " << D / (n / 2) << endl;
    cout << "Count delete(AVL): " << D2 / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search(BST): " << S / (n / 2) << endl;
    cout << "Count search(AVL): " << S2 / (n / 2) << endl;
    //освобождение памяти массива m[] 
    delete[] arr;
}





int main() {
    setlocale(0, "ru");
   
    AVL_Tree<int, int> avl_tree;
    AVL_Tree<int, int>::Iterator avl_tree_pr_it(avl_tree);
    AVL_Tree<int, int>::reverseIterator avl_tree_rv_it(avl_tree);
    AVL_Tree<int, int>::Iterator avl_begin;
    AVL_Tree<int, int>::reverseIterator avl_rbegin;
    AVL_Tree<int, int>::Iterator avl_end;
    AVL_Tree<int, int>::reverseIterator avl_rend;
    int choice = 111;
    int key, value = 0;
    int newValue = 0;
    int k = 0;
    menu();
    while (choice != 0) {
        cout << endl;
        cout << ">>> ";
        cin >> k;
        switch (k)
        {
        case 1:
            cout << "Размер дерева: " << endl;
            cout << avl_tree.getSize();
            break;
        case 2:
            cout << avl_tree.clear_tree() << endl;
            break;
        case 3:
            cout << avl_tree.is_clear_tree() << endl;
            break;
        case 4:
            cin >> key;
            cout << avl_tree.getByWriteAndRead(key) << endl;
            break;
        case 5:
            cin >> key >> value;
            avl_tree.getByWriteAndRead(key) = value;
            break;
        case 6:
            cin >> key >> value;
            cout << avl_tree.insert(key, value) << endl;
            break;
        case 7:
            cin >> key;
            cout << avl_tree.remove(key) << endl;
            break;
        case 8:
            avl_tree.print();
            break;
        case 9:
            avl_tree_pr_it = avl_tree.begin();
            break;
        case 10:
            avl_tree_pr_it = avl_tree.end();
            break;
        case 11:
            try {
                cout << *avl_tree_pr_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 12:
            try {
                cin >> *avl_tree_pr_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 13:
            try {
                ++avl_tree_pr_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 14:
            avl_begin = avl_tree.begin();
            cout << (avl_begin == avl_tree_pr_it) << endl;
            break;
        case 15:
            avl_end = avl_tree.end();
            cout << (avl_end == avl_tree_pr_it) << endl;
            break;
        case 16:
            avl_begin = avl_tree.begin();
            cout << (avl_begin != avl_tree_pr_it) << endl;
            break;
        case 17:
            avl_end = avl_tree.end();
            cout << (avl_end != avl_tree_pr_it) << endl;
            break;
        case 18:
            avl_tree_rv_it = avl_tree.rbegin();
            break;
        case 19:
            avl_tree_rv_it = avl_tree.rend();
            break;
        case 20:
            try {
                cout << *avl_tree_rv_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 21:
            try {
                cin >> *avl_tree_rv_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 22:
            try {
                ++avl_tree_rv_it;
            }
            catch (const std::exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 23:
            avl_rbegin = avl_tree.rbegin();
            cout << (avl_rbegin == avl_tree_rv_it) << endl;
            break;
        case 24:
            avl_rend = avl_tree.rend();
            cout << (avl_rend == avl_tree_rv_it) << endl;
            break;
        case 25:
            avl_rbegin = avl_tree.rbegin();
            cout << (avl_rbegin != avl_tree_rv_it) << endl;
            break;
        case 26:
            avl_rend = avl_tree.rend();
            cout << (avl_rend != avl_tree_rv_it) << endl;
            break;
        case 27:
            cout << "test_rand(): " << endl;
            test_rand(5000);
            break;
        case 28:
            cout << "test_ord(): " << endl;
            test_ord(5000);
            break;
        case 29:
            menu();
            break;
        case 30:
            choice = 0;
            return 0;
            break;
        default:
            cout << "неккоректный ввод" << endl;
            break;
        }
    }
    return 0;
}


//int choice = -1;
//BST_Tree<int, int> tree;
//BST_Tree<int, int>::Iterator it(tree);
//BST_Tree<int, int>::reverseIterator rit(tree);
//BST_Tree<int, int>::Iterator b;
//BST_Tree<int, int>::reverseIterator rb;
//BST_Tree<int, int>::Iterator end;
//BST_Tree<int, int>::reverseIterator rend;
//
//menu();
//int value, key, newValue, treeSize;
//int key2 = 0;
//while (choice != 0) {
//
//    cout << endl;
//    cout << endl;
//    cout << ">>>  ";
//    cin >> choice;
//    switch (choice)
//    {
//    case 1:
//        treeSize = tree.getSize();
//        cout << treeSize << endl;
//        break;
//    case 2:
//        cout << tree.clear_tree();
//        cout << "Дерево очищено" << endl;
//        break;
//    case 3:
//        cout << tree.is_clear_tree() << endl;
//        break;
//    case 4:
//        cin >> key;
//        try
//        {
//            cout << tree.getByWriteAndRead(key) << endl;
//        }
//        catch (const exception e)
//        {
//            cerr << e.what();
//        }
//        break;
//    case 5:
//        cin >> key >> newValue;
//        try
//        {
//            tree.getByWriteAndRead(key) = newValue;
//            //tree.insert(key, value);
//        }
//        catch (const exception e)
//        {
//            cerr << e.what();
//        }
//        break;
//    case 6:
//        cin >> key;
//        cin >> value;
//        cout << tree.insert(key, value) << endl;
//        break;
//    case 7:
//        cin >> key;
//        cout << tree.remove(key) << endl;
//        break;
//    case 8:
//        tree.printTree();
//        cout << endl;
//        break;
//    case 9:
//        cin >> value;
//        cout << tree.getCountKeysHigherThanInserted(value) << endl;
//        tree.setCounterKey(0);
//        break;
//    case 10:
//        it = tree.begin();
//        break;
//    case 11:
//        it = tree.end();
//        break;
//    case 12:
//        try
//        {
//            cout << *it << endl;
//        }
//        catch (const exception e)
//        {
//            cerr << e.what();
//        }
//        break;
//    case 13:
//        cin >> newValue;
//        try
//        {
//            *it = newValue;
//        }
//        catch (const exception e)
//        {
//            cerr << e.what();
//        }
//        break;
//    case 14:
//        try
//        {
//            ++it;
//        }
//        catch (const exception e)
//        {
//            cerr << e.what();
//        }
//        break;
//    case 15:
//        b = tree.begin();
//        cout << (b == it) << endl;
//        break;
//    case 16:
//        end = tree.end();
//        cout << (it == end) << endl;
//        break;
//    case 17:
//        b = tree.begin();
//        cout << (b != it) << endl;
//        break;
//    case 18:
//        end = tree.end();
//        cout << (it != end) << endl;
//        break;
//    case 19:
//        rit = tree.rbegin();
//        break;
//    case 20:
//        rit = tree.rend();
//        break;
//    case 21:
//        try {
//            cout << *rit << endl;
//        }
//        catch (const std::exception& ex) {
//            cout << ex.what() << endl;
//        }
//        break;
//    case 22:
//        try {
//            cin >> *rit;
//
//        }
//        catch (const std::exception& ex) {
//            cout << ex.what() << endl;
//        }
//        break;
//    case 23:
//        try {
//            ++rit;
//        }
//        catch (const std::exception& ex) {
//            cout << ex.what() << endl;
//        }
//        break;
//    case 24:
//        rb = tree.rbegin();
//        cout << (rb == rit) << endl;
//        break;
//    case 25:
//        rend = tree.rend();
//        cout << (rit == rend) << endl;
//        break;
//    case 26:
//        rb = tree.rbegin();
//        cout << (rb != rit) << endl;
//        break;
//    case 27:
//        rend = tree.rend();
//        cout << (rit != rend) << endl;
//        break;
//    case 28:
//        test_rand(1000);
//        cout << endl;
//        break;
//    case 29:
//        test_ord(500);
//        cout << endl;
//        break;
//    case 30:
//        choice = 0;
//        break;
//    case 31:
//        menu();
//        break;
//    }
//
//}