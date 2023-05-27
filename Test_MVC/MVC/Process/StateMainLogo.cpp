//
// Created by bleppe on 16/05/23.
//

#include "StateMainLogo.h"
#include "debug_bsp.h"
#include "version.h"
#include "StateInputTest1.h"


Status StateMainLogo::on_event(StateEvent *evt) {
    Status status = STATUS_IGNORED;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            DEBUG_PRINT("Logo State, %s\n", VERSION);
            memset(bitmap,0xF0,LCD_WIDTH*LCD_HEIGHT/2);
            status = STATUS_HANDLED;
            break;
        case EVENT_SIGNAL_SELECT:
            if(evt->value == INPUT_EVENT_CLICKED){
                status = STATUS_TRANSITION;
                context->transition(new StateInputTest1());
            }
            break;
        default: status = StateLogo::on_event(evt);
    }
    return status;
}

StateMainLogo::StateMainLogo() {
    timer = xTimerCreate("timer1", 1000, true, this,
                         [](TimerHandle_t t)
    {
        static bool toggle = true;
        auto state = static_cast<StateMainLogo*>(pvTimerGetTimerID(t));
        if(toggle){
            memset(state->bitmap,0x00,LCD_WIDTH*LCD_HEIGHT/2);
        }
        else{
            memset(state->bitmap,0xF0,LCD_WIDTH*LCD_HEIGHT/2);
        }
        toggle = !toggle;
    });
    xTimerStart(timer, 0);
}

StateMainLogo::~StateMainLogo() {
    xTimerDelete(timer,0);
}
