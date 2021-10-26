//
// Created by Nikolai on 26.10.2021.
//

#ifndef ARDUINOPROJECT_SERIALCONTROLLER_HPP
#define ARDUINOPROJECT_SERIALCONTROLLER_HPP

#include <ISerialDevice.hpp>
//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/ISerialDevice.hpp"
#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
#endif

class SerialController {
protected:
    HardwareSerial *_serial;
    const static int maxSize = 20;
    int size = 0;
    ISerialDevice* listOfDevices[maxSize];
    int delSerialDevice(int number)
    {
        if(number < size){
            for(int i = number; i < size - 1; i++)
            {
                listOfDevices[i] = listOfDevices[i+1];
            }
            listOfDevices[size--] = 0;
            return 0;
        }
        return 1;
    }
    int findDeviceIndex(String name)
    {
        for(int index = 0; index < size; index++)
        {
            if(listOfDevices[index]->getName() == name)
                return index;
        }
        return -1;
    }
public:
    SerialController(HardwareSerial* serial)
    {
        _serial = serial;
    }
    void addSerialDevice(ISerialDevice* iSerialDevice)
    {
        if(size < maxSize)
        {
            listOfDevices[size++] = iSerialDevice;
        }
    };
    void delSerialDevice(String name)
    {
        int indexToDel = findDeviceIndex(name);
        if(indexToDel > -1)
            delSerialDevice(indexToDel);
    };

    /// Syntax of the command assumes:
    /// nameOfDevice.internalDeviceName
    /// nameOfDevice?returnedValueName
    /// nameOfDevice:setValueName
    /// \param command
    /// \return answer of device if it's requared

    String handle(String command)
    {
        String answer = "";
        int indexOfRequestSign = command.indexOf('?'); // 1 mode
        int indexOfSetSign = command.indexOf(':'); // 2 mode
        int mode = -1;
        int modeIndex = 2048;

        if(indexOfRequestSign >= 0){
            if(modeIndex > indexOfRequestSign)
            {
                modeIndex = indexOfRequestSign;
                mode = 1;
            }
        }
        if(indexOfSetSign >= 0){
            if(modeIndex > indexOfSetSign)
            {
                modeIndex = indexOfSetSign;
                mode = 2;
            }
        }

        int deviceIndex = findDeviceIndex(command.substring(0, modeIndex));

        if(deviceIndex == -1){
            answer += "Device \"";
            answer += findDeviceIndex(command.substring(0, modeIndex)) + "\" wasn't found";
        }

        ISerialDevice* device = listOfDevices[deviceIndex];

        switch (mode) {
            case 1:
                _serial->println(device->get(command.substring(modeIndex + 1)));
                break;
            case 2:
                {
                    int indexOfEq = command.indexOf('=');
                    device->set(command.substring(modeIndex + 1,
                                                  indexOfEq), command.substring(indexOfEq + 1));
                }
                break;
            default:
                break;
        }
        return answer;
    }
    int process()
    {
        if(_serial && _serial->available())
        {
            handle(_serial->readStringUntil('\n'));
        }
    }
};


#endif //ARDUINOPROJECT_SERIALCONTROLLER_HPP
