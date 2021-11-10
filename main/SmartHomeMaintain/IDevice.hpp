#pragma once

#include <Arduino.h>
#include <ICloneable.hpp>
#include <ISetValue.hpp>
#include <IGetValue.hpp>

//#define DEBUG
#ifdef DEBUG
#include "ICloneable.hpp"
#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/WString.h"
#endif

class IDevice : public ICloneable {
  protected:
    String _name = "";
    void *iGetValue = nullptr;
    void *iSetValue = nullptr;
public:
    IDevice(String name);
    IDevice(IDevice& iDevice);

    virtual ICloneable *clone() override;

    String getName();
    void setISetValue(void*);
    void setIGetValue(void*);
    virtual String makeWebPage();
};
