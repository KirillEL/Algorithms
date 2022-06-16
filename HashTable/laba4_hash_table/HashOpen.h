#pragma once

#include <iostream>
#include "HashTable.h"
using namespace std;
enum Status {
    FREE, BUSY, DELETED
};

template<class Key = int, class Data = int>
class HashOpen : public HashTable<Key, Data> {
private:
    const int mars[13] = { 7,13,31,61,127,251,509,1021,2039,4093,8191,16381,32749 };
    class Cell {
    public:
        Key key;
        Data data;
        Status status;
        Cell();
    };
    Cell* array;
    int hashKey = 0;
    int upperPow2(int x);
    double squadZond(int key, int i);
public:
    
    class Iterator : public HashTable<Key, Data>::Iterator {
    public:
        HashOpen<Key, Data>* table;

        Cell* current;

        explicit Iterator(HashTable<Key, Data>* ch);

        void checkException() override;

        void toBegin() override;

        void toEnd() override;

        Data& operator*() override;

        void operator++() override;

        void operator++(int) override;

        bool operator==(typename HashTable<Key, Data>::Iterator* it) override;

    };

    explicit HashOpen(int _size);

    HashOpen(HashOpen<Key, Data>& ch);

    ~HashOpen() override;

    bool insert(Key key, Data data) override;

    bool remove(Key key) override;

    Data search(Key key) override;

    void clear() override;

    void printHash() override;

    

    typename HashTable<Key, Data>::Iterator* begin() override;

    typename HashTable<Key, Data>::Iterator* end() override;
};
template<class Key, class Data>
HashOpen<Key, Data>::Iterator::Iterator(HashTable<Key, Data>* ch) {
    this->table = (HashOpen<Key, Data> *) ch;
    this->current = nullptr;
    this->index = 0;
}
template<class Key, class Data>
void HashOpen<Key, Data>::Iterator::checkException() {
    if (!table || !current) throw runtime_error("EXCEPTION!");
}
template<class Key, class Data>
void HashOpen<Key, Data>::Iterator::toBegin() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = 0; i < table->size; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
}

template<class Key, class Data>
void HashOpen<Key, Data>::Iterator::toEnd() {
    if (!table) throw runtime_error("EXCEPTION!");
    for (int i = table->size - 1; i >= 0; --i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
}
template<class Key, class Data>
Data& HashOpen<Key, Data>::Iterator::operator*() {
    checkException();
    if (!current) throw runtime_error("EXCEPTION!");
    return current->data;
}
template<class Key, class Data>
void HashOpen<Key, Data>::Iterator::operator++() {
    checkException();
    if (this->index == table->size-1) throw runtime_error("EXCEPTION!");
    for (int i = this->index+1; i < table->size; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}
template<class Key, class Data>
void HashOpen<Key, Data>::Iterator::operator++(int) {
    checkException();
    if (this->index == table->size-1) throw runtime_error("EXCEPTION!");
    for (int i = this->index; i < table->size+1; ++i) {
        if (table->array[i].status == BUSY) {
            this->index = i;
            this->current = &table->array[i];
            return;
        }
    }
    throw runtime_error("EXCEPTION!");
}
template<class Key, class Data>
bool HashOpen<Key, Data>::Iterator::operator==(typename HashTable<Key, Data>::Iterator* it) {
    return this->current == static_cast<HashOpen<>::Iterator*>(it)->current;
}
template<class Key, class Data>
int HashOpen<Key, Data>::upperPow2(int x) {
    x--;
    for (int p = 1; p < 32; p <<= 1) x |= (x >> p);
    return ++x;
}
template<class Key, class Data>
double HashOpen<Key, Data>::squadZond(int key, int i) { // Квадратичное зондирование
    float c1 = 0.1;    
    float c2 = 0.9;
    return ((int)(this->hash(key) + c1 * i + c2 * i * i) % this->size);
    
}

template<class Key, class Data>
HashOpen<Key, Data>::HashOpen(int _size) {
    this->isChain = 0;
    int sz1 = (int)((float)_size / 0.5f);
    int steps = 0;
    while (sz1) {
        sz1 /= 2;
        steps++;
    }
    steps -= 3;
    if (steps < 0) {
        steps = 0;
    }
    this->size = mars[steps];

    array = new Cell[this->size];
    for (int i = 0; i < this->size; ++i) {
        array[i].status = FREE;
    }
    this->count = 0;
    this->view_count = 0;
}
template<class Key, class Data>
void HashOpen<Key, Data>::clear() {
    if (this->isEmpty()) return;
    for (int i = 0; i < this->size; i++) {
        array[i].data = 0;
        array[i].key = 0;
        array[i].status = FREE;
    }
    this->count = 0;
}
template<class Key, class Data>
HashOpen<Key, Data>::~HashOpen() {
    delete[] array;
}
template<class Key, class Data>
HashOpen<Key, Data>::HashOpen(HashOpen<Key, Data>& ch) {
    this->isChain = 0;
    this->size = ch.size;
    array = new Cell[this->size];
    for (int i = 0; i < this->size; ++i) {
        array[i] = ch.array[i];
    }
    this->count = ch.count;
    this->view_count = ch.view_count;
}
template<class Key, class Data>
bool HashOpen<Key, Data>::insert(Key key, Data data) {
   this->view_count = 0; 
    for (int i = 0; i < this->size-1; ++i) {
        this->view_count++;
        hashKey = squadZond(this->convert(key), i);
        // квадратичное зондирование
        if (array[hashKey].status == BUSY && array[hashKey].key == key) break;
        if (array[hashKey].status == BUSY) continue;
        array[hashKey].key = key;
        array[hashKey].data = data;
        array[hashKey].status = BUSY;
        this->count++;
        return true;
    }
    return false;
}
template<class Key, class Data>
bool HashOpen<Key, Data>::remove(Key key) {
    this->view_count = 0;
    if (this->isEmpty()) return false;
    for (int i = 0; i < this->size - 1; ++i) {
        this->view_count++;
        int hashKey = squadZond(this->convert(key), i); // квадратичное зондирование
        if (array[hashKey].status == FREE) break;
        if (array[hashKey].key == key && array[hashKey].status == BUSY) {
            array[hashKey].status = DELETED;
            this->count--;
            return true;
        }
    }
    return false;
}
template<class Key, class Data>
Data HashOpen<Key, Data>::search(Key key) {
    this->view_count = 0;
    if (this->isEmpty()) throw runtime_error("EXCEPTION");
    for (int i = 0; i < this->size-1; ++i) {
        this->view_count++;
        int hashKey = squadZond(this->convert(key), i); // квадратичное зондирование
        this->view_count++;
        if (array[hashKey].status == FREE) break;
        if (array[hashKey].key == key && array[hashKey].status == BUSY) {
            return array[hashKey].data;
        }
    }
    
    throw runtime_error("EXCEPTION");
}
template<class Key, class Data>
void HashOpen<Key, Data>::printHash() {
    if (this->isEmpty()) {
        for (int i = 0; i < this->size; i++) {
            cout << i << ": " << "FREE" << endl;
        }
        return;
    }
    else {
        cout << "Table:\n";
        for (int i = 0; i < this->size; ++i) {
            if (array[i].status == BUSY) {
                cout << i << ": " << array[i].key << "(" << array[i].data << ") - BUSY" << endl;
            }
            else if (array[i].status == DELETED) {
                cout << i << ": " << array[i].key << "(" << array[i].data << ") - DELETED" << endl;
            }
            else if (array[i].status == FREE) {
                //cout << i << ": " << array[i].key << "(" << array[i].data << ") - FREE" << endl;
                cout << i << ": " << "FREE" << endl;
            }
        }
    }
}
template<class Key, class Data>
typename HashTable<Key, Data>::Iterator* HashOpen<Key, Data>::begin() {
    HashTable<>::Iterator* iterator = new HashOpen<>::Iterator(this);
    iterator->toBegin();
    return iterator;
}
template<class Key, class Data>
typename HashTable<Key, Data>::Iterator* HashOpen<Key, Data>::end() {
    HashTable<>::Iterator* iterator = new HashOpen<>::Iterator(this);
    iterator->toEnd();
    return iterator;
}
template<class Key, class Data>
HashOpen<Key, Data>::Cell::Cell() {
    key = 0;
    data = 0;
    status = FREE;
}
