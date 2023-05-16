//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATEMENU_H
#define LCDTEST_STATEMENU_H

#include "DataTypes/StateMachine.h"
#include <cstdio>

class StateMenu : public State{
public:
    Status on_event(StateEvent *evt) override;


};


#endif //LCDTEST_STATEMENU_H
