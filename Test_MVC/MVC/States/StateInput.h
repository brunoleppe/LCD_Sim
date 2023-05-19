//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_STATEINPUT_H
#define LCDTEST_STATEINPUT_H


#include "StateMachine.h"
#include "DataTypes/string.h"

class StateInput : public State{
protected:
    bru::string string;
    StateInput(){
        type = STATE_TYPE_INPUT;
    }
public:
    bru::string* get_string(){
        return &string;
    }
};


#endif //LCDTEST_STATEINPUT_H
