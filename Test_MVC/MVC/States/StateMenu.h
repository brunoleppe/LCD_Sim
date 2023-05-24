//
// Created by bleppe on 17/05/23.
//

#ifndef LCDTEST_STATEMENU_H
#define LCDTEST_STATEMENU_H


#include "StateMachine.h"
#include "DataTypes/vector.h"
#include "DataTypes/string.h"
#include "debug_bsp.h"

class StateMenu : public State{
protected:
    bru::string title;
    bru::vector<const char *> items;
    int index;
    State* nextState;
    StateMenu() : title("Title"), index(0), nextState(){
        type = STATE_TYPE_MENU;
    }
public:
    bru::vector<const char *>* get_items(){
        return &items;
    }

    void set_index(int i){
        index = i;
    }
    bru::string* get_title(){
        return &title;
    }
    Status on_event(StateEvent *evt) override{
        Status status = STATUS_IGNORED;
        switch(evt->signal){
            case EVENT_SIGNAL_SELECT:
                if(evt->value == INPUT_EVENT_CLICKED) {
                    DEBUG_PRINT("%s\n", items[index]);
                    if(nextState != nullptr)
                        context->transition(nextState);
                    status = STATUS_TRANSITION;
                }
                break;
            default: status = State::on_event(evt);
        }
        return status;
    }
};


#endif //LCDTEST_STATEMENU_H
