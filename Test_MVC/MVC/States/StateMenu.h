//
// Created by bleppe on 17/05/23.
//

#ifndef LCDTEST_STATEMENU_H
#define LCDTEST_STATEMENU_H


#include <vector>
#include "StateMachine.h"


class StateMenu : public State{
protected:
    std::vector<const char *> items;
    int index;
    StateMenu() : index(0){
        type = STATE_TYPE_MENU;
    }
public:
    std::vector<const char *>* get_items(){
        return &items;
    }

    void set_index(int i){
        index = i;
    }
};


#endif //LCDTEST_STATEMENU_H
