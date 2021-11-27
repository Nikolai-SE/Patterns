//
// Created by Nikolai on 18.11.2021.
//

#ifndef ARDUINOPROJECT_SWITCHSTATE_HPP
#define ARDUINOPROJECT_SWITCHSTATE_HPP
class SwitchState;
class Switch;
#include "Switch.hpp"

class SwitchState {
protected:
    Switch* pSwitch;
    static const int const_isOff = 0;
    static const int const_isOn = 1;
public:
    SwitchState();
    SwitchState(Switch* pSwitch);
    void setSwitch(Switch* pSwitch);
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual bool state() = 0;
    ~SwitchState();
};

#endif //ARDUINOPROJECT_SWITCHSTATE_HPP
