#pragma once

#include "vector.h"

template <class T>
class queue : public vector<T> {
public:
    // constructor
    queue(const T& value) : vector<T>(value) { }
    // operation
    T front() {
        return this->_head->value();
    }

    T back() {
        return this->_tail->value();
    }

    void push_back(const T& value) override {
        if (0 == this->_size) {
            vector<T>::push_back(value);
            return;
        }

        node<T>* p = new node<T>(value);
        p->next() = this->_head;
        this->_head = p;
        this->_size++;
        return;
    }

    void pop() override {
        if (0 == this->_size) {
            return;
        }

        node<T>* p = this->_tail;
        this->_head = p->next();
        delete p;
        this->_size--;
    }
};  