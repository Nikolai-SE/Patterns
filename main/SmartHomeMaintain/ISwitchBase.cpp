#include "ISwitchBase.hpp"

ISwitchBase::ISwitchBase(const String &name) : IDevice(name) {}

String ISwitchBase::makeWebPage()  {
    return "";
}

