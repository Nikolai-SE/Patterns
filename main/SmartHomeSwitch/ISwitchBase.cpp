#include "ISwitchBase.hpp"

ISwitchBase::ISwitchBase(const String &name) : IDevice(name) {}

ISwitchBase::ISwitchBase(ISwitchBase &iSwitchBase) : IDevice(iSwitchBase) {
}

