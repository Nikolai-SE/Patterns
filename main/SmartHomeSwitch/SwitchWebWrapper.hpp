//
// Created by Nikolai on 18.10.2021.
//

#ifndef ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP
#define ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP

#include "ISwitchBase.hpp"
//#include "../SmartHomeMaintain/ISwitchBase.hpp"
class SwitchWebWrapper : public ISwitchBase{
protected:
    ISwitchBase *_switch;
    String _webName;
public:
    SwitchWebWrapper(ISwitchBase * switchBase);
    bool state() override;
    void turnOn() override;
    void turnOff() override;
    String makeWebPage() override;
    void setWebName(String webName);
};


#endif //ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP
