//
// Created by Nikolai on 23.11.2021.
//

#include "MakeConcreteSerialAdapters.hpp"

ISerialAdapter<IDevice> &MakeConcreteSerialAdapters::makeSerialAdapter(IDevice *iDevice) {
    switch (iDevice->getTypeOfDevice()) {
        case TYPE_OF_SWITCH:
            return  *(ISerialAdapter<IDevice>*) ((void *)&(makeSerialAdapter((ISwitchBase *) iDevice)));
        default:
            //Serial.println("NO_TYPE method");
            break;
    }
    return *(ISerialAdapter<IDevice>*)nullptr;
}

SwitchSerialAdapter &MakeConcreteSerialAdapters::makeSerialAdapter(ISwitchBase *pSwitch) {
    SwitchSerialAdapter* switchSerialAdapter = new SwitchSerialAdapter(pSwitch->getName(), (ISwitchBase*)pSwitch);
    return *switchSerialAdapter;
}
