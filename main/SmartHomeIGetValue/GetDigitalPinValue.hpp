#pragma once
#include "IGetValue.hpp"

class GetDigitalPinValue : public IGetValue<int> {
protected:
    int _pin = -1;
public:
    GetDigitalPinValue(int pin);
    int getValue() override;
    void updateValue() override;
};
