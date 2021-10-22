//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_SWITCHSERIALADAPTER_HPP
#define ARDUINOPROJECT_SWITCHSERIALADAPTER_HPP

//#include "../SmartHomeMaintain/ISerialAdapter.hpp"
#include "ISerialAdapter.hpp"
#include "ISwitchBase.hpp"
//#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/WString.h"

class SwitchSerialAdapter : public ISerialAdapter<ISwitchBase> {
protected:
public:
    SwitchSerialAdapter(String name, ISwitchBase *switchBase) : ISerialAdapter(name, switchBase){};

    String get(String key) override {
        key.toLowerCase();
        key.trim();
        if(key == "state")
        {
            return String(device->state());
        }
        else
        return "exception";
    }

    void set(String key, String value) override {
        key.toLowerCase();
        key.trim();
        value.toLowerCase();
        value.trim();
        if(key == "state")
        {
            if(value == "on" || value == "true" || value == "1")
            {
                device->turnOn();
            }else
            if(value == "off" || value == "false" || value == "0")
            {
                device->turnOff();
            }
        }
    }
};


#endif //ARDUINOPROJECT_SWITCHSERIALADAPTER_HPP
