#include "Switch.hpp"
#include "SwitchOff.h"
#include "SwitchOn.hpp"

Switch::Switch(String name, bool defaultState) : ISwitchBase(name) {
    if(defaultState == const_isOn)
        pState =  (SwitchState*) new SwitchOn(this);
    else
        pState =  (SwitchState*) new SwitchOff(this);
}

bool Switch::state() {
    return pState->state();
}

void Switch::turnOn() {
    pState->turnOn();
}

void Switch::turnOff() {
    pState->turnOff();
}

Switch::Switch(Switch &aSwitch) : ISwitchBase(aSwitch){
    pState = (SwitchState*) new SwitchOff();
    pState->setSwitch(this);
}

ICloneable *Switch::clone() {
    return (ICloneable*) new Switch(*this);
}

void Switch::setVal(bool val) {
    ((ISetValue<int> *) iSetValue)->setValue(val);
}

void Switch::setState(SwitchState *newState) {
    if(pState)
        delete pState;
    pState = newState;
}


