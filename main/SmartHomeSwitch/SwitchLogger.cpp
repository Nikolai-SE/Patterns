#include "SwitchLogger.hpp"

SwitchLogger::SwitchLogger(String name, ISwitchBase *pSwitch) : ISwitchBase(name) {
    _switch = pSwitch;
}

bool SwitchLogger::state() {
    printLog(_switch->getName() + ": state is " + ((_switch->state())? "ON" : "OFF" ) + ".");
    return _switch->state();
}

void SwitchLogger::turnOn() {
    _switch->turnOn();
    printLog(_switch->getName() + ": is turned ON.");
}

void SwitchLogger::turnOff() {
    _switch->turnOff();
    printLog(_switch->getName() + ": is turned OFF.");
}

void SwitchLogger::printLog(String log) {
    _serial->println(log);
};

void SwitchLogger::setSerial(HardwareSerial *serial) {
    _serial = serial;
}

String SwitchLogger::makeWebPage() {
    String webOfProx = _switch->makeWebPage();
    if( webOfProx.length() > 0 )
    {
        return webOfProx;
    }
    else
    {
        return ISwitchBase::makeWebPage();
    }
}
