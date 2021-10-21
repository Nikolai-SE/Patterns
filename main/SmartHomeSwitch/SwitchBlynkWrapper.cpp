//
// Created by Nikolai on 18.10.2021.
//

#include "SwitchBlynkWrapper.hpp"

SwitchBlynkWrapper::SwitchBlynkWrapper(ISwitchBase* switchBase) : ISwitchBase("blynkWrapper_" + switchBase->getName()){
    _switch = switchBase;
};

bool SwitchBlynkWrapper::state() {
    Serial.println("*** write state to Blynk");
    //Blynk.virtualWrite(virtualPinNumber, _switch->state());
    return _switch->state();
}

void SwitchBlynkWrapper::turnOn() {
    _switch->turnOn();
    Serial.println("*** write turn ON to Blynk");
    //_blynk->virtualWrite(virtualPinNumber, _switch->state());
    //Blynk.virtualWrite(virtualPinNumber, _switch->state());
}

void SwitchBlynkWrapper::turnOff() {
    _switch->turnOff();
    Serial.println("*** write turn OFF to Blynk");
    //_blynk->virtualWrite(virtualPinNumber, _switch->state());
    //Blynk.virtualWrite(virtualPinNumber, _switch->state());
}

void SwitchBlynkWrapper::setVirtualPinNumber(int virtualPinNumber) {
    this->virtualPinNumber = virtualPinNumber;
}

/*
void SwitchBlynkWrapper::setBlynk(BlynkContriller* blynkController){
    this->_blynk = blynk;
}
 */

String SwitchBlynkWrapper::makeWebPage() {
    return _switch->makeWebPage();
}
