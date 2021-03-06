#pragma once

#include <iostream>
#include "HashTable.h"

using namespace std;

template<class Key = int, class Data = int>
class HashChain : public HashTable<Key, Data> {
private:
    const int mars[13] = { 7,13,31,61,127,251,509,1021,2039,4093,8191,16381,32749 };
    class Chain {
        friend class Iterator;

    public:
        class Node {
        public:
            Key key;
            Data data;
            Node* next;

            Node(Key key1, Data data1, Node* node = nullptr);
        };

        Node* head;
        Node* last;
        int size;
        int view_count;

        Chain();

        Chain(Chain& chain);

        ~Chain();

        int getSize();

        int getViewCount();

        bool add(Key key, Data data);

        bool del(Key key);

        Data get(Key key);

        void show();
        
    };

    Chain** arr;
    

    int nearPow2(int x);

    class Iterator : public HashTable<Key, Data>::Iterator {
    public:
        HashChain<Key, Data>* table;
        typename Chain::Node* current;

        explicit Iterator(HashTable<Key, Data>* ch);

        void checkException() override;

        void toBegin() override;

        void toEnd() override;

        Data& operator*() override;

        void operator++() override;

        void operator++(int) override;

        //        bool operator==(typename ChainHash<Key, Data>::Iterator *it);

        bool operator==(typename HashTable<Key, Data>::Iterator* it) override;

    };

public:
    explicit HashChain(int _size);

    HashChain(HashChain<Key, Data>& ch);

    ~HashChain() override;

    bool insert(Key key, Data data) override;

    bool remove(Key key) override;

    Data search(Key key) override;

    void clear() override;

    void printHash() override;

    typename HashTable<Key, Data>::Iterator* begin() override;

    typename HashTable<Key, Data>::Iterator* end() override;

};

template<class Key, class Data>
HashChain<Key, Data>::Iterator::Iterator(HashTable<Key, Data>* ch) {
    this->table = (HashChain<Key, Data> *) ch;
    this->current = nullptr;
    this->index = 0;
}

template<class Key, class Data>
Data& HashChain<Key, Data>::Iterator::operator*() {
    checkException();
    if (!current) throw runtime_error("EXCEPTION!");
    return current->data;
}

template<class Key, class Data>
void HashChain<Key, Data>::Iterator::checkException() {
    if (!table || !current) throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
void HashChain<Key, Data>::Iterator::toBegin() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = 0; i < table->size; ++i) {
        if (table->arr[i]) {
            this->current = table->arr[i]->head;
            this->index = i;
            return;
        }
    }

}

template<class Key, class Data>
void HashChain<Key, Data>::Iterator::toEnd() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = table->size - 1; i >= 0; --i) {
        if (table->arr[i]) {
            typename Chain::Node* tmp = table->arr[i]->head;
            while (tmp->next) {
                tmp = tmp->next;
            }
            this->current = tmp;
            this->index = i;
            return;
        }
    }

}

template<class Key, class Data>
void HashChain<Key, Data>::Iterator::operator++() {
    checkException();
    if (current->next) {
        current = current->next;
        return;
    }
    for (int i = this->index + 1; i < table->size; ++i) {
        if (table->arr[i]) {
            this->current = table->arr[i]->head;
            this->index = i;
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}

template<class Key, class Data>
void HashChain<Key, Data>::Iterator::operator++(int) {
    checkException();
    if (current->next) {
        current = current->next;
        return;
    }
    for (int i = this->index + 1; i < table->size; ++i) {
        if (table->arr[i]) {
            this->current = table->arr[i]->head;
            this->index = i;
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}


template<class Key, class Data>
bool HashChain<Key, Data>::Iterator::operator==(typename HashTable<Key, Data>::Iterator* it) {
    return this->current == static_cast<HashChain<>::Iterator*>(it)->current;
}


template<class Key, class Data>
int HashChain<Key, Data>::nearPow2(int x) {
    if (x == 0) return 1;
    int res = 1;
    while (x > 0) {
        res <<= 1;
        x >>= 1;
    }
    return res >>= 1;
}

template<class Key, class Data>
HashChain<Key, Data>::HashChain(int _size) {
    this->isChain = 1; 
    
    int sz1 = (int)((float)_size / 2);
    int steps = 0;
    while (sz1) {
        sz1 /= 2;
        steps++;
    }
    steps -= 3;
    if (steps < 1) {
        steps = 1;
    }
    this->size = mars[steps - 1];


    arr = new Chain * [this->size];
    for (int i = 0; i < this->size; ++i) {
        arr[i] = nullptr;
    }
    this->count = 0;
    this->view_count = 0;
}

template<class Key, class Data>
HashChain<Key, Data>::HashChain(HashChain<Key, Data>& ch) {
    this->isChain = 1;
    this->size = ch.size;
    arr = new Chain * [this->size];
    for (int i = 0; i < this->size; ++i) {
        arr[i] = ch.arr[i];
    }
    this->count = ch.count;
    this->view_count = 0;
}

template<class Key, class Data>
HashChain<Key, Data>::~HashChain() {
    clear();
}

template<class Key, class Data>
void HashChain<Key, Data>::clear() {
    if (this->isEmpty()) return;
    for (int i = 0; i < this->size; ++i) {
        arr[i] = nullptr;
    }
    
    this->count = 0;
}

template<class Key, class Data>
bool HashChain<Key, Data>::insert(Key key, Data data) {
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) {
        arr[hashKey] = new Chain();
    }
    bool flag = arr[hashKey]->add(key, data);
    this->view_count += arr[hashKey]->getViewCount();
    if (!flag) return flag;
    this->count++;
    return flag;
}

template<class Key, class Data>
bool HashChain<Key, Data>::remove(Key key) {
    if (this->isEmpty()) return false;
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) return false;
    bool flag = arr[hashKey]->del(key);
    this->view_count += arr[hashKey]->getViewCount();
    if (!flag) return flag;
    if (!arr[hashKey]->getSize()) {
        delete arr[hashKey];
        arr[hashKey] = nullptr;
    }
    this->count--;
    return flag;
}

template<class Key, class Data>
Data HashChain<Key, Data>::search(Key key) {
    if (this->isEmpty()) throw runtime_error("EXCEPTION");
    int hashKey = this->hash(this->convert(key));
    if (arr[hashKey] == nullptr) throw runtime_error("EXCEPTION");
    int data;
    try {
        data = arr[hashKey]->get(key);
        this->view_count += arr[hashKey]->getViewCount();
    }
    catch (runtime_error e) {
        throw e;
    }
    return data;
}

template<class Key, class Data>
void HashChain<Key, Data>::printHash() {
    if (this->isEmpty()) {
        for (int i = 0; i < this->size; i++) {
            cout << i << ": \n";
        }
        return;
    }
    cout << "Table:\n";
        for (int i = 0; i < this->size; ++i) {
            if (arr[i]) {
                cout << i << ": ";
                arr[i]->show();
            }
            else {
                cout << i << ": \n";
            }
        }  
}

template<class Key, class Data>
typename HashTable<Key, Data>::Iterator* HashChain<Key, Data>::begin() {
    HashTable<>::Iterator* iterator = new HashChain<>::Iterator(this);
    iterator->toBegin();
    return iterator;
}

template<class Key, class Data>
typename HashTable<Key, Data>::Iterator* HashChain<Key, Data>::end() {
    HashTable<>::Iterator* iterator = new HashChain<>::Iterator(this);
    iterator->toEnd();
    return iterator;
}

template<class Key, class Data>
HashChain<Key, Data>::Chain::Node::Node(Key key1, Data data1, HashChain::Chain::Node* node) {
    key = key1;
    data = data1;
    next = node;
}

template<class Key, class Data>
HashChain<Key, Data>::Chain::Chain() {
    head = nullptr;
    size = 0;
    view_count = 0;
}

template<class Key, class Data>
HashChain<Key, Data>::Chain::Chain(HashChain::Chain& chain) {
    if (chain.head) {
        Node* tmp = chain.head;
        head = new Node(tmp->key, tmp->data);
        Node* p = head;
        tmp = tmp->next;
        while (tmp) {
            Node* newNode = new Node(tmp->key, tmp->data);
            p->next = newNode;
            tmp = tmp->next;
            p = p->next;
        }
        size = chain.size;
        view_count = chain.view_count;
    }
}

template<class Key, class Data>
HashChain<Key, Data>::Chain::~Chain() {
    Node* p = head;
    while (p) {
        Node* prev = p;
        p = p->next;
        delete prev;
    }
    size = 0;
    view_count = 0;
}

template<class Key, class Data>
int HashChain<Key, Data>::Chain::getSize() {
    return size;
}

template<class Key, class Data>
int HashChain<Key, Data>::Chain::getViewCount() {
    int tmp = view_count;
    view_count = 0;
    return tmp;
}

template<class Key, class Data>
bool HashChain<Key, Data>::Chain::add(Key key, Data data) {
    if (!head) {
        head = new Node(key, data);
        size++;
        view_count++;
        return true;
    }
    Node* tmp = head;
    while (tmp) {
        view_count++;
        if (tmp->key == key) return false;
        if (!tmp->next) break;
        tmp = tmp->next;
    }
    Node* node = new Node(key, data);
    tmp->next = node;
    size++;
    return true;
}

template<class Key, class Data>
bool HashChain<Key, Data>::Chain::del(Key key) {
    if (!head) return false;
    Node* tmp = head;
    Node* prev = nullptr;
    while (tmp) {
        view_count++;
        if (tmp->key == key)
            break;
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp) return false;
    if (tmp == head)
        head = head->next;
    else
        prev->next = tmp->next;
    delete tmp;
    size--;
    return true;
}

template<class Key, class Data>
Data HashChain<Key, Data>::Chain::get(Key key) {
    if (!head) throw runtime_error("EXCEPTION");
    Node* tmp = head;
    while (tmp) {
        view_count++;
        if (tmp->key == key)
            break;
        tmp = tmp->next;
    }
    if (!tmp) throw runtime_error("EXCEPTION");
    return tmp->data;
}

template<class Key, class Data>
void HashChain<Key, Data>::Chain::show() {
    if (!head) return;
        Node* tmp = head;
        while (tmp) {
            cout << tmp->key << " (" << tmp->data << ") ";
            tmp = tmp->next;
        }
        cout << endl;
    
}
