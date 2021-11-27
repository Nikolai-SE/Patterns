#pragma once
#include "ISwitchBase.hpp"
#include <ICloneable.hpp>
//class SwitchState;
//class Switch;
#include "SwitchState.hpp"
#include "../SmartHomeMaintain/ICloneable.hpp"

class Switch : public ISwitchBase {
protected:
    SwitchState* pState = nullptr;
public:
    static const int const_isOff = 0;
    static const int const_isOn = 1;
    Switch(String name, bool defaultState = const_isOff);
    Switch(Switch & aSwitch);

    ICloneable *clone() override;

    bool state() override;
    void turnOn() override;
    void turnOff() override;
    void setState(SwitchState* newState);
    void setVal(bool val);
};
