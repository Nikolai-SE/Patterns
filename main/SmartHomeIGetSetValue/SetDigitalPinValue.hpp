#pragma once
#include "ISetValue.hpp"

class SetDigitalPinValue : public ISetValue<int> {
protected:
    int _pin = 0;
public:
    SetDigitalPinValue();
    SetDigitalPinValue(int pin);
    void setPin(int pin);
    void setValue(int value) override;
};