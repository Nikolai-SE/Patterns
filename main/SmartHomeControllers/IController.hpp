//
// Created by Nikolai on 10.11.2021.
//

#ifndef ARDUINOPROJECT_ICONTROLLER_HPP
#define ARDUINOPROJECT_ICONTROLLER_HPP

#include <ISerialDevice.hpp>
#include <List.hpp>
#include <Switch.hpp>
//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/ISerialDevice.hpp"
#include "../SmartHomeMaintain/IDevice.hpp"
#include "../SmartHomeTools/List.hpp"
#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
#endif

class IController {
protected:
    List<ISerialDevice*> listOfSerialDevices;
    int delSerialDevice(int number);
    int findDeviceIndex(String name);
public:
    IController(){};
    IController(IController &iController);
    void addSerialDevice(ISerialDevice* iSerialDevice);
    virtual void addSwitch(ISwitchBase* iSwitchBase) = 0;
    void delSerialDevice(String name);
    virtual int process() = 0;
    ~IController();
};

#endif //ARDUINOPROJECT_ICONTROLLER_HPP
