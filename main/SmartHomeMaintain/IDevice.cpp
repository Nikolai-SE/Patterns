#include "IDevice.hpp"

IDevice::IDevice(String name)
{
    _name = name;
}

String IDevice::getName()
{
  return _name;
}

void IDevice::setISetValue(void* iSetValue) {
    this->iSetValue = iSetValue;
}

void IDevice::setIGetValue(void* iGetValue) {
    this->iGetValue = iGetValue;
}

IDevice::IDevice(IDevice &iDevice) {
    _name = iDevice.getName();
    iSetValue = iDevice.iSetValue;
    iGetValue = iDevice.iGetValue;
}

String IDevice::makeWebPage() {
    return String();
}

ICloneable *IDevice::clone() {
    return new IDevice(*this);
}

