//
// Created by Nikolai on 23.11.2021.
//

#ifndef ARDUINOPROJECT_MAKECONCRETESERIALADAPTERS_HPP
#define ARDUINOPROJECT_MAKECONCRETESERIALADAPTERS_HPP

#include "IMakeSerialAdapters.hpp"
#include <Switch.hpp>
#include <SwitchSerialAdapter.hpp>

//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeSwitch/Switch.hpp"
#include "../SmartHomeSwitch/SwitchSerialAdapter.hpp"
#endif

class MakeConcreteSerialAdapters : public IMakeSerialAdapters{
public:
    ISerialAdapter<IDevice> &makeSerialAdapter(IDevice *iDevice) override;
    SwitchSerialAdapter &makeSerialAdapter(ISwitchBase *pSwitch);
};

#endif //ARDUINOPROJECT_MAKECONCRETESERIALADAPTERS_HPP
