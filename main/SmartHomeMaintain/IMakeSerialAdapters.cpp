//
// Created by Nikolai on 23.11.2021.
//

#include "IMakeSerialAdapters.hpp"

ISerialAdapter<IDevice> &IMakeSerialAdapters::makeSerialAdapter(IDevice *iDevice) {
    return *(ISerialAdapter<IDevice>*)nullptr;
}
