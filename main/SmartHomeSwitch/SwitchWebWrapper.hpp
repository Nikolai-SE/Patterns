//
// Created by Nikolai on 18.10.2021.
//

#ifndef ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP
#define ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP

#include "ISwitchBase.hpp"
#include "WebWrapperTemplate.hpp"

//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/WebWrapperTemplate.hpp"
#endif

class SwitchWebWrapper : public ISwitchBase{
protected:
    ISwitchBase *_switch;
    WebWrapperTemplate* _webWrapperTemplate;
    char* _webName = 0;
public:
    SwitchWebWrapper(ISwitchBase * switchBase, WebWrapperTemplate* webWrapperTemplate);
    bool state() override;
    void turnOn() override;
    void turnOff() override;
    String makeWebPage() override;

    void setWebName(String webName);
    ~SwitchWebWrapper();
};


#endif //ARDUINOPROJECT_SWITCHWEBWRAPPER_HPP
