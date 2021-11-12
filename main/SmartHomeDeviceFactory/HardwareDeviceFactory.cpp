//
// Created by Nikolai on 11.11.2021.
//

#include "HardwareDeviceFactory.hpp"

Switch* &HardwareDeviceFactory::makeSwitch(const String name, List<void*> args)
// argv { pin : int, [default state : int], [pin for get state : int]  }
{
    int defaultState = 0;
    if(args.size() >= 2)
    {
        defaultState = *(int*)args[1];
    }
    Switch* pSwitch = new Switch(name, defaultState);

    int setPin = 0;
    if(args.size() >= 1)
    {
        setPin = *(int*)args[0];
        pSwitch->setISetValue(new SetDigitalPinValue(setPin));
    }

    int getPin = 0;
    if(args.size() >= 3)
    {
        getPin = *(int*)args[2];
        pSwitch->setIGetValue(new GetDigitalPinValue(getPin));
    }

    return pSwitch;
}
