//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_STATEINPUT_H
#define LCDTEST_STATEINPUT_H


#include <string>
#include "StateMachine.h"

class StateInput : public State{
protected:
    std::string string;
    StateInput(){
        type = STATE_TYPE_INPUT;
    }
public:
    std::string* get_string(){
        return &string;
    }
};


#endif //LCDTEST_STATEINPUT_H
