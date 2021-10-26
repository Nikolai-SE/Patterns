//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_ISERIALADAPTER_HPP
#define ARDUINOPROJECT_ISERIALADAPTER_HPP

#include <ISerialDevice.hpp>

template <class T>
class ISerialAdapter : public ISerialDevice{
protected:
    T* device;
public:
    ISerialAdapter(String name, T* device) : ISerialDevice(name)
    {
        this->device = device;
    };
};

#endif //ARDUINOPROJECT_ISERIALADAPTER_HPP
