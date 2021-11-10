//
// Created by Nikolai on 26.10.2021.
//

#ifndef ARDUINOPROJECT_SERIALCONTROLLER_HPP
#define ARDUINOPROJECT_SERIALCONTROLLER_HPP

#include <ISerialDevice.hpp>
#include <IController.hpp>
#include <Switch.hpp>
#include <SwitchSerialAdapter.hpp>
//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/ISerialDevice.hpp"
#include "../SmartHomeMaintain/IDevice.hpp"
#include "IController.hpp"
#include "../../../../../../../Downloads/Installetion/IDE/Arduino/arduino-1.8.15-windows/arduino-1.8.15/hardware/arduino/avr/cores/arduino/HardwareSerial.h"
#include "../SmartHomeSwitch/Switch.hpp"
#include "../SmartHomeSwitch/SwitchSerialAdapter.hpp"

#endif

#define REQUEST_MODE 1
#define SET_MODE 2

class SerialController : public IController{
protected:
    HardwareSerial *_serial;
public:
    SerialController(HardwareSerial* serial) : IController()
    {
        _serial = serial;
    }
    SerialController(SerialController& serialController) : IController(serialController)
    {
        _serial = serialController._serial;
    }

    /*void addSwitch(Switch *aSwitch)
    {
        Serial.println(" add switch ");
        addSerialDevice( (ISerialDevice*) new SwitchSerialAdapter("adapter", aSwitch) );
    }

    void addDevice(IDevice *iDevice) override {
        if(typeDevice(iDevice) == 1)
            addSwitch((Switch *)(iDevice));
    }*/

    /// Syntax of the command assumes:
    /// nameOfDevice.internalDeviceName
    /// nameOfDevice?returnedValueName
    /// nameOfDevice:setValueName
    /// \param command
    /// \return answer of device if it's requared

    String handle(String command)
    {
        String answer = "";
        int indexOfRequestSign = command.indexOf('?'); // 1 REQUEST_MODE
        int indexOfSetSign = command.indexOf(':'); // 2 SET_MODE
        int mode = -1;
        int modeIndex = 2048;
        if(indexOfRequestSign >= 0){
            if(modeIndex > indexOfRequestSign)
            {
                modeIndex = indexOfRequestSign;
                mode = REQUEST_MODE;
            }
        }
        if(indexOfSetSign >= 0){
            if(modeIndex > indexOfSetSign)
            {
                modeIndex = indexOfSetSign;
                mode = SET_MODE;
            }
        }
        int deviceIndex = findDeviceIndex(command.substring(0, modeIndex));

        ISerialDevice* serialDevice = nullptr;

        if(deviceIndex == -1){
            answer += "Device \"";
            answer += findDeviceIndex(command.substring(0, modeIndex)) + "\" wasn't found";
        }
        else
        {
            serialDevice = listOfSerialDevices[deviceIndex];
        }

        switch (mode) {
            case REQUEST_MODE:
                answer += serialDevice->get(command.substring(modeIndex + 1));
                _serial->println(answer);
                break;
            case SET_MODE:
                {
                    int indexOfEq = command.indexOf('=');
                    serialDevice->set(command.substring(modeIndex + 1,
                                                        indexOfEq), command.substring(indexOfEq + 1));
                }
                break;
            default:
                break;
        }
        return answer;
    }

    int process() override {
        if(_serial && _serial->available())
        {
            handle(_serial->readStringUntil('\n'));
        }
        return 0;
    }
};


#endif //ARDUINOPROJECT_SERIALCONTROLLER_HPP
