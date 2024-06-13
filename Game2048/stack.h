#pragma once

#include "vector.h"

template <class T>
class stack : public vector<T> {
public:
    T top() {
        return this->_tail->value();
    }

    
};