//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_ITTERATOR_HPP
#define ARDUINOPROJECT_ITTERATOR_HPP

template <class T>
class Iterator {
protected:
    T* value;
    Iterator<T>* next = nullptr;
public:
    Iterator(T *value)
    {
        this->value = value;
    }
    static Iterator<T> begin(){
        return -1;
    }
    static Iterator<T> end(){
        return nullptr;
    }

    Iterator<T> operator++()
    {
        return this->next;
    }
    bool hasNext()
    {
        return next != nullptr;
    }
    T operator*(){
        return value;
    }
};


#endif //ARDUINOPROJECT_ITTERATOR_HPP
