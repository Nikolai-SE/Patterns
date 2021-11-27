//
// Created by Nikolai on 23.11.2021.
//

#ifndef ARDUINOPROJECT_IMAKESERIALADAPTERS_HPP
#define ARDUINOPROJECT_IMAKESERIALADAPTERS_HPP

#include "ISerialAdapter.hpp"
#include "IDevice.hpp"

class IMakeSerialAdapters {
public:
    virtual ISerialAdapter<IDevice> &makeSerialAdapter(IDevice* iDevice);
};


#endif //ARDUINOPROJECT_IMAKESERIALADAPTERS_HPP
