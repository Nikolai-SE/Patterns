#include "Switch.hpp"
Switch::Switch(String name, bool defaultState) : ISwitchBase(name) {
    _state = defaultState;
}

bool Switch::state() {
    return _state;
}

void Switch::turnOn() {
    ((ISetValue<int> *) iSetValue)->setValue(const_isOn);
    _state = true;
}

void Switch::turnOff() {
    ((ISetValue<int> *) iSetValue)->setValue(const_isOff);
    _state = false;
}

Switch::Switch(Switch &aSwitch) : ISwitchBase(aSwitch){
    _state = aSwitch._state;
}

ICloneable *Switch::clone() {
    return new Switch(*this);
}

