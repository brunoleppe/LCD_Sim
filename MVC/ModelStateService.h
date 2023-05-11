//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_MODELSTATESERVICE_H
#define LCDTEST_MODELSTATESERVICE_H

#include "Model.h"

class ModelStateService : public StateMachine {
public:
    void on_event(ControllerInputEvent& evt){
        ((Model *) state)->on_event(evt);
    }
    MessagePacket* get_data(){
        return ((Model*)state)->get_data();
    }
};


#endif //LCDTEST_MODELSTATESERVICE_H
