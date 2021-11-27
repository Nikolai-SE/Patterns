//
// Created by Nikolai on 18.11.2021.
//

#include "SwitchState.hpp"

SwitchState::SwitchState() {;}

SwitchState::SwitchState(Switch* pSwitch) {
    this->pSwitch = pSwitch;
}

void SwitchState::setSwitch(Switch* pSwitch) {
    this->pSwitch = pSwitch;
}

SwitchState::~SwitchState() {
    this->pSwitch = 0;
}

