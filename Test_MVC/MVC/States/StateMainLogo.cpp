//
// Created by bleppe on 16/05/23.
//

#include "StateMainLogo.h"
#include "input.h"
#include "debug_bsp.h"
#include "version.h"

Status StateMainLogo::on_event(StateEvent *evt) {
    Status status;
    if(evt->signal == EVENT_SIGNAL_SELECT && evt->value == INPUT_EVENT_CLICKED){
        DEBUG_PRINT("Logo State, %s\n", VERSION);
        status = STATUS_HANDLED;
    }
    else{
        status = StateLogo::on_event(evt);
    }
    return status;
}
