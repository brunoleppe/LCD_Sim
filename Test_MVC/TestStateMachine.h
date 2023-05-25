//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_TESTSTATEMACHINE_H
#define LCDTEST_TESTSTATEMACHINE_H


#include "DataTypes/Observer.h"
#include "Test_MVC/MVC/States/StateMachine.h"
#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "Test_MVC/Test/Views/InputViewTest.h"
#include "MVC/Process/StateInputTest1.h"
#include "Factory.h"
#include "MVC/Process/StateMainLogo.h"

#include "FreeRTOS.h"
#include "queue.h"

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#else
#include "task.h"
#endif

class TestStateMachine : public StateMachine, public Observer{

private:
    static StateEventSignal signals[10];
    View* view;
    StateType type;

    bool running = true;
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
//    bru::queue<ControllerInputEvent> queue;
    QueueHandle_t queue;
    SDL_Thread* thread;
#else
    QueueHandle_t queue;
#endif

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    static int
#else
    static void
#endif
    task(void *data){
        LCD_configure();
        auto machine = (TestStateMachine*)data;
        ControllerInputEvent evt = {};
        while(machine->running){
            if(xQueueReceive(machine->queue,&evt,10)){
                if(machine->view->set_input(evt))
                    continue;

                if(evt.type == INPUT_EVENT_TYPE_CONTROL){
                    if(machine->state == nullptr)
                        continue;
                    StateEvent stateEvt = {
                            .signal = signals[evt.code],
                            .value = evt.event,
                    };
                    if(machine->state->on_event(&stateEvt) == STATUS_TRANSITION){
                        if(machine->state->get_type() != machine->type){
                            machine->type = machine->state->get_type();
                            delete machine->view;
                            machine->view = Factory::create(machine->state);
                        }
                        else{
                            machine->view->get_viewModel()->set_state(machine->state);
                        }
                    }
                }
            }
            machine->view->draw();
            LCD_print();
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
            SDL_Delay(16);
#endif
        }
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
        return 0;
#endif
    }

public:

    TestStateMachine() : view(nullptr){
        auto state = new StateMainLogo();
        type = state->get_type();
        view = Factory::create(state);
        set_state(state);
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
        running = true;
        thread = SDL_CreateThread(TestStateMachine::task, "controller_task", this);
#else
        xTaskCreate(task,"controller_task",1024,this,2, nullptr);
#endif
        queue = xQueueCreate(2,sizeof(ControllerInputEvent));


    }

    void update(Subject *subject) override{
        auto evt = *(ControllerInputEvent*)subject->get_data();
        xQueueSend(queue,&evt,10);
    }

    void stop_all(){

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
        running = false;
        SDL_WaitThread(thread, nullptr);
#endif
        stop();
        delete view;
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
