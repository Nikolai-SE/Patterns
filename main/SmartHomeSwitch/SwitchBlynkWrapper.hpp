//
// Created by Nikolai on 18.10.2021.
//
#pragma once

//#include <BlynkSimpleEsp8266.h>
#include "ISwitchBase.hpp"
//#include "../SmartHomeMaintain/ISwitchBase.hpp"
class SwitchBlynkWrapper : public ISwitchBase{
protected:
    ISwitchBase *_switch;
    //BlynkController * _blynk;
    int virtualPinNumber = 0;
public:
    SwitchBlynkWrapper(ISwitchBase * switchBase);
    bool state() override;
    void turnOn() override;
    void turnOff() override;
    String makeWebPage() override;
    void setVirtualPinNumber(int virtualPinNumber);
    //void setBlynk(Blynk* blynk);
};

