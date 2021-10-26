//
// Created by Nikolai on 18.10.2021.
//

#include "SwitchWebWrapper.hpp"

SwitchWebWrapper::SwitchWebWrapper(ISwitchBase* switchBase, WebWrapperTemplate* webWrapperTemplate) : ISwitchBase("webWrapper_" + switchBase->getName()){
    _switch = switchBase;
    _webWrapperTemplate = webWrapperTemplate;
};

bool SwitchWebWrapper::state() {
    return _switch->state();
}

void SwitchWebWrapper::turnOn() {
    _switch->turnOn();
}

void SwitchWebWrapper::turnOff() {
    _switch->turnOff();
}

String SwitchWebWrapper::makeWebPage()  {
    String webPage = "";
    /*char templateOfWebPage[] = "<div class = 'switch' id='%s'>\
                                <div class='device_header'>%s\
                                <div class='toggle-button-cover'>\
                                <div class='button r' id='nice_button'>\
                                <input type='checkbox' class='checkbox' id='%s_checkbox' onchange=\"send_request_to_Arduino('%s', 'state=' + ((this.checked)?'on':'off'))\">\
                                <div class='knobs'></div>\
                                <div class='layer'></div>\
                                </div>\
                                </div>\
                                </div>\
                                </div> \n";
                                */
    char *nameCharArray = new char[_name.length() + 1];
    _name.toCharArray(nameCharArray, _name.length() + 1);

    int len = strlen(_webWrapperTemplate->getTemplateOfWebPage()) + 3 * _name.length() + strlen(_webName) + 1;
    char *charArray = new char[len];
    sprintf(charArray, _webWrapperTemplate->getTemplateOfWebPage(), nameCharArray, _webName, nameCharArray, nameCharArray);

    webPage += charArray;

    delete charArray;
    delete nameCharArray;
    return webPage;
}

void SwitchWebWrapper::setWebName(String webName) {
    if(_webName != 0)
        delete _webName;
    int len = webName.length() + 1;
    _webName = new char[len];
    webName.toCharArray(_webName, len);
}

SwitchWebWrapper::~SwitchWebWrapper() {
    if(_webName != 0)
        delete _webName;
}
