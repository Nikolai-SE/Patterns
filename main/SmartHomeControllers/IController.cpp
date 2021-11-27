//
// Created by Nikolai on 10.11.2021.
//

#include "IController.hpp"

IController::IController(IController &iController) {
    ListIterator<ISerialDevice*> it = iController.listOfSerialDevices.begin();
    while (it.hasNext())
        this->listOfSerialDevices.insert(*(it++));
}

void IController::addSerialDevice(ISerialDevice *iSerialDevice)
{
    listOfSerialDevices.insert(iSerialDevice);
}

void IController::delSerialDevice(String name){
    int indexToDel = findDeviceIndex(name);
    if(indexToDel > -1)
        delSerialDevice(indexToDel);
}

int IController::delSerialDevice(int number)
{
    listOfSerialDevices.remove(number);
}

int IController::findDeviceIndex(String name)
{
    for(int index = 0; index < listOfSerialDevices.size(); index++)
    {
        if(listOfSerialDevices[index]->getName() == name)
            return index;
    }
    return -1;
};

IController::~IController() {
    for(int index = 0; index < listOfSerialDevices.size(); index++)
    {
        delete listOfSerialDevices[index];
    }
    listOfSerialDevices.clear();
}

