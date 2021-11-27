//
// Created by Nikolai on 18.11.2021.
//

#include "SwitchOff.h"
#include "SwitchOn.hpp"

SwitchOff::SwitchOff() {};

SwitchOff::SwitchOff(Switch* pSwitch) : SwitchState(pSwitch){};

void SwitchOff::turnOn(){
    pSwitch->setVal(const_isOn);
    pSwitch->setState((SwitchState* )new SwitchOn(this->pSwitch));
}

void SwitchOff::turnOff(){};

bool SwitchOff::state(){
    return const_isOff;
}

