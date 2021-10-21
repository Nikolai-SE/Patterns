#pragma once

//#include "../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/WString.h"
#include <Arduino.h>
#include <ISetValue.hpp>
#include <IGetValue.hpp>

class IDevice {
  protected:
    String _name = "";
    void *iGetValue = nullptr;
    void *iSetValue = nullptr;
public:
    IDevice(String name);
    String getName();
    void setISetValue(void*);
    void setIGetValue(void*);
    virtual String makeWebPage() = 0;
};
