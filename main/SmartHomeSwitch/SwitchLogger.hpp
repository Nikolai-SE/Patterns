#pragma once
#include "ISwitchBase.hpp"
//#include "../SmartHomeMaintain/ISwitchBase.hpp"
#include "Switch.hpp"

class SwitchLogger : public ISwitchBase {
protected:
    ISwitchBase *_switch;
    HardwareSerial *_serial;
    void printLog(String log);
public:
    SwitchLogger(String name, ISwitchBase *pSwitch);
    bool state() override;
    void turnOn() override;
    void turnOff() override;
    String makeWebPage() override;
    void setSerial(HardwareSerial *serial);
};
