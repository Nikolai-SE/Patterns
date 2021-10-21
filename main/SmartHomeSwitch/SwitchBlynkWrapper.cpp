//
// Created by Nikolai on 18.10.2021.
//

#include "SwitchWebWrapper.hpp"

SwitchWebWrapper::SwitchWebWrapper(ISwitchBase* switchBase) : ISwitchBase("wrapper_" + switchBase->getName()){
    _switch = switchBase;
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
    return "<div class = 'pomp' id='" + _name + "'>\
<div class='device_header'>" + _webName + "\
<div class='toggle-button-cover'>\
<div class='button r' id='nice_button'>\
<input type='checkbox' class='checkbox' id='" + _name + "_checkbox' onchange=\"send_request_to_Arduino('" + _name + "', 'state=' + ((this.checked)?'on':'off'))\">\
<div class='knobs'></div>\
<div class='layer'></div>\
</div>\
</div>\
</div>\
</div>";
}

void SwitchWebWrapper::setWebName(String webName) {
    _webName = webName;
}
