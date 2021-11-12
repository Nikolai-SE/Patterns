#pragma once
#include <Arduino.h>

template<class T>
class ISetValue {
protected:
    T _value = 0;
public:
    virtual void setValue(T) = 0;
    T getLastValue();
};

