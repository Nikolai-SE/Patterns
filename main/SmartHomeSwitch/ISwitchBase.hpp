#pragma once
#include <IDevice.hpp>

//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/IDevice.hpp"
#endif

#define TYPE_OF_SWITCH 1000
class ISwitchBase : public IDevice {
  public:
    ISwitchBase(const String &name);
    ISwitchBase(ISwitchBase &iSwitchBase);
    virtual bool state() = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    ICloneable *clone() override;

    int getTypeOfDevice() override;
};
