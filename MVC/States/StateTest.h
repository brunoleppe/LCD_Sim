//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATETEST_H
#define LCDTEST_STATETEST_H


#include "DataTypes/StateMachine.h"
#include <cstdio>

class StateTest : public State{
public:
    Status on_event(StateEvent *evt) override;


};


#endif //LCDTEST_STATETEST_H
