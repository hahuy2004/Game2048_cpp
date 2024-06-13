#pragma once

#include <iostream>
#include "node.h"

template <class T>
class vector {
protected:
    int _size;
    node<T>* _head;
    node<T>* _tail;
public:
    // constructor
    vector() : _size(0), _head(nullptr), _tail(nullptr) {}
    vector(const T& value) : _size(1) {
        node<T>* p = new node<T>(value);
        this->_head = p;
        this->_tail = p;
    }
    // operation
    virtual void push_back(const T& value) {
        node<T>* p = new node<T>(value);

        if (0 == _size) {
            this->_head = p; 
        }
        else {
            this->_tail->setNext(p);
        }
        this->_tail = p;
        this->_size++;
    }

    virtual void pop() {
        if (0 == this->_size) {
            return;
        }
        else if (1 == this->_size) {
            node<T>* p = this->_head;
            this->_head = nullptr;
            this->_tail = nullptr;
            delete p;
            this->_size--;
            return;
        } 

        node<T>* p = this->_head;
        while (p->next() != _tail) {
            p = p->next();
        }
        
        delete _tail;
        this->_tail = p;
        this->_size--;
    }

    T& at(const int& index) {
        if (index >= this->_size) {
            throw "Out of range";
        }

        node<T>* p = this->_head;
        int i = 0;
        while(i != index) {
            p = p->next();
            i++;
        }

        return p->value();
    }
    
    T& operator[] (const int& index) {
        return at(index);
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        if (0 == this->_size) {
            return true;
        }
        return false;
    }

    int size() const {
        return this->_size;
    }

    void insert(const T& value, const int& index) {
        if (index < 0 || index > _size) {
            throw "Out of range";
        }
        if (_size == index) {
            push_back(value);
            return;
        }
        if (0 == index) {
            node<T>* n = new node<T>(value);
            n->setNext(this->_head);
            this->_head = n;
            this->_size++;
            return;
        }
        
        int i = 0;
        node<T>* p = this->_head;
        while (i != index - 1) {
            p = p->next();
            i++;
        }
        node<T>* n = new node<T>(value);
        n->setNext(p->next());
        p->setNext(n);
        this->_size++;
        return;
    }

    void erase(const int& index) {
        if (empty()) {
            throw "Empty vector";
        }
        if (index < 0 || index > this->_size - 1) {
            throw "Out of range";
        }
        if (index == this->_size - 1) {
            pop();
        }
        if (index == 0) {
            node<T>* p = this->_head;
            this->_head = p->next();
            if (this->_size == 1) {
                this->_tail = nullptr;
            }
            this->_size--;
            return;
        }

        int i = 0;
        node<T>* p = this->_head;
        while (i != index - 1) {
            p = p->next();
            i++;
        }
        node<T>* d = p->next();
        p->setNext(d->next());
        delete d;
        this->_size--;
        return;
    }
};