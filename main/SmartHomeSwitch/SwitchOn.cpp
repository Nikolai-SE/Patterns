//
// Created by Nikolai on 18.11.2021.
//

#include "SwitchOn.hpp"
#include "SwitchOff.h"

SwitchOn::SwitchOn() {}
SwitchOn::SwitchOn(Switch* pSwitch) : SwitchState(pSwitch){};

void SwitchOn::turnOn(){};

void SwitchOn::turnOff(){
    pSwitch->setVal(const_isOff);
    pSwitch->setState(new SwitchOff(this->pSwitch));
}
bool SwitchOn::state(){
    return const_isOn;
}

