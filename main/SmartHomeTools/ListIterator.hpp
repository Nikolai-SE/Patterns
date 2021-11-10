//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_ITTERATOR_HPP
#define ARDUINOPROJECT_ITTERATOR_HPP

#include "IIterator.hpp"
template <class T>
class ListIterator : public IIterator<T> {
protected:
    T* value = nullptr;
public:
    ListIterator<T>* _next = nullptr;
    ListIterator() {
        value = nullptr;
    }
    ListIterator(T value)
    {
        this->value = new T(value);
    }
    ListIterator(ListIterator<T>const &listIterator)
    {
        this->value = listIterator.value;
        this->_next = listIterator._next;
    }
    bool hasNext() override {
        return this->_next != nullptr;
    }
    ListIterator<T>& operator++(){
        this->value = this->_next->value;
        this->_next = this->_next->_next;
        return *this;
    }
    ListIterator<T> operator++(int i) {
        ListIterator<T>* it = new ListIterator<T>(*this);
        ++(*this);
        return *it;
    }
    T& operator*() override {
        return *(this->value);
    }
    bool operator!=(const ListIterator<T>& it) {
        return this->value != it.value;
    }
};

#endif //ARDUINOPROJECT_ITTERATOR_HPP
