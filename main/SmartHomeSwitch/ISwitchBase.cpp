#include "ISwitchBase.hpp"

ISwitchBase::ISwitchBase(const String &name) : IDevice(name) {}

ISwitchBase::ISwitchBase(ISwitchBase &iSwitchBase) : IDevice(iSwitchBase) {
}

ICloneable *ISwitchBase::clone() {
    return IDevice::clone();
}

int ISwitchBase::getTypeOfDevice() {
    return TYPE_OF_SWITCH;
}

