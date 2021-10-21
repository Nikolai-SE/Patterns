#pragma once
#include "IDevice.hpp"
class ISwitchBase : public IDevice {
  public:
    ISwitchBase(const String &name);
    virtual bool state() = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    String makeWebPage() override;
};
