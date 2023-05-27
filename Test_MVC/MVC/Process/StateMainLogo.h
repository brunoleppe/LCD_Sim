//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_STATEMAINLOGO_H
#define LCDTEST_STATEMAINLOGO_H


#include "Test_MVC/MVC/States/StateLogo.h"
#include "FreeRTOS.h"
#include "timer.h"

class StateMainLogo : public StateLogo{
private:
    TimerHandle_t timer;
public:
    StateMainLogo();

    ~StateMainLogo() override;

    Status on_event(StateEvent *evt) override;
};


#endif //LCDTEST_STATEMAINLOGO_H
