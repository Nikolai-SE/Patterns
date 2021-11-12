//
// Created by Nikolai on 11.11.2021.
//

#ifndef ARDUINOPROJECT_HARDWAREDEVICEFACTORY_HPP
#define ARDUINOPROJECT_HARDWAREDEVICEFACTORY_HPP

#include <DeviceFactory.hpp>
#include <GetDigitalPinValue.hpp>
#include <SetDigitalPinValue.hpp>

//#define DEBUG
#ifdef DEBUG

#include "DeviceFactory.hpp"
#include "../SmartHomeIGetValue/GetDigitalPinValue.hpp"
#include "../SmartHomeISetValue/SetDigitalPinValue.hpp"
#include "../SmartHomeSwitch/ISwitchBase.hpp"
#include "../SmartHomeTools/List.hpp"
#endif

class HardwareDeviceFactory : public DeviceFactory{
public:
    // name, pin : int, default state : int
    Switch* &makeSwitch(const String name, List<void*> args) override;
};


#endif //ARDUINOPROJECT_HARDWAREDEVICEFACTORY_HPP
