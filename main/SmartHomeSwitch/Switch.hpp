#pragma once
#include "ISwitchBase.hpp"
//#include "../SmartHomeMaintain/ISwitchBase.hpp"

class Switch : public ISwitchBase {
protected:
    bool _state = false;
public:
    static const int const_isOff = 0;
    static const int const_isOn = 1;
    Switch(String name, bool defaultState = const_isOff);
    bool state() override;
    void turnOn() override;
    void turnOff() override;
};
