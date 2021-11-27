//
// Created by Nikolai on 18.11.2021.
//

#ifndef ARDUINOPROJECT_SWITCHOFF_H
#define ARDUINOPROJECT_SWITCHOFF_H

#include <SwitchState.hpp>
//#define DEBUG
#ifdef DEBUG
#include "SwitchState.hpp"
#endif

class SwitchOff : public SwitchState{
public:
    SwitchOff();
    SwitchOff(Switch* pSwitch);
    void turnOn() override;
    void turnOff() override;
    bool state() override;
};



#endif //ARDUINOPROJECT_SWITCHOFF_H
