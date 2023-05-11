//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_GRAPHICALSERVICE_H
#define LCDTEST_GRAPHICALSERVICE_H

#include "Model.h"

class GraphicalService : public StateMachine {
public:
    void on_event(){
        ((Model*)state)->on_event();
    }
    MessagePacket* get_data(){
        return ((Model*)state)->get_data();
    }
};


#endif //LCDTEST_GRAPHICALSERVICE_H
