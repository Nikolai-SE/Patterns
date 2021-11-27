//
// Created by Nikolai on 18.11.2021.
//

#ifndef ARDUINOPROJECT_SWITCHON_HPP
#define ARDUINOPROJECT_SWITCHON_HPP

#include <SwitchState.hpp>
//#define DEBUG
#ifdef DEBUG
#include "SwitchState.hpp"
#endif

class SwitchOn : public SwitchState{
public:
    SwitchOn();
    SwitchOn(Switch* pSwitch);
    void turnOn() override;
    void turnOff() override;
    bool state() override;
};

#endif //ARDUINOPROJECT_SWITCHON_HPP
