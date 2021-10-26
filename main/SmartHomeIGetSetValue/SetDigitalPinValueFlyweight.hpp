//
// Created by Nikolai on 26.10.2021.
//

#ifndef ARDUINOPROJECT_SETDIGITALPINVALUEFLYWEIGHT_HPP
#define ARDUINOPROJECT_SETDIGITALPINVALUEFLYWEIGHT_HPP
#include <ISetValue.hpp>
#include <SetDigitalPinValue.hpp>

class SetDigitalPinValueFlyweight: public ISetValue<int> {
protected:
    int _pin = 0;
    SetDigitalPinValue* setDigitalPinValue = 0;
public:
    SetDigitalPinValueFlyweight(int pin, SetDigitalPinValue* setDigitalPinValue){
        _pin = pin;
        this->setDigitalPinValue = setDigitalPinValue;
    };
    void setValue(int value) override
    {
        setDigitalPinValue->setPin(_pin);
        setDigitalPinValue->setValue(value);
    };
};


#endif //ARDUINOPROJECT_SETDIGITALPINVALUEFLYWEIGHT_HPP
