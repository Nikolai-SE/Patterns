//
// Created by Nikolai on 11.11.2021.
//

#ifndef ARDUINOPROJECT_DEVICEFACTORY_HPP
#define ARDUINOPROJECT_DEVICEFACTORY_HPP
#include <Switch.hpp>
#include <List.hpp>

//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeSwitch/Switch.hpp"
#include "../SmartHomeTools/List.hpp"

#endif

class DeviceFactory {
public:
    virtual Switch* &makeSwitch(const String name, List<void*> args) = 0;
    //virtual IDetectorBase& makeDetector(const String name, List<void*>) = 0;
    //virtual IReferenceValueBase& makeReferenceValue(const String name, List<void*>) = 0;
};

#endif //ARDUINOPROJECT_DEVICEFACTORY_HPP
