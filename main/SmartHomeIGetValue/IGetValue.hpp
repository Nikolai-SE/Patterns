#pragma once
#include <Arduino.h>
//#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/USBAPI.h"

template<class T>
class IGetValue {
protected:
    T _value = (int) "";
public:
    virtual T getValue() = 0;
    T getLastValue();
    virtual void updateValue() = 0;
};

