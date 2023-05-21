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
#include "DataTypes/queue.h"

class TestStateMachine : public StateMachine, public Observer{

private:
    static StateEventSignal signals[10];
    View* view;
    StateType type;

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    bru::queue<ControllerInputEvent> queue;
    bool running = true;
    SDL_Thread* thread;

    static int task(void *data){
        LCD_configure();
        auto machine = (TestStateMachine*)data;

        while(machine->running){
            if(!machine->queue.empty()){
                ControllerInputEvent evt = machine->queue.front();
                machine->queue.pop();

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
            SDL_Delay(16);
        }

        return 0;
    }
#endif


public:

    TestStateMachine() : view(nullptr){
        auto state = new StateMainLogo();
        type = state->get_type();
        view = Factory::create(state);
        set_state(state);
#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
        running = true;
        thread = SDL_CreateThread(TestStateMachine::task, "controller_task", this);
#endif


    }

    void update(Subject *subject) override{
        auto evt = *(ControllerInputEvent*)subject->get_data();
        queue.push(evt);
//        if(view->set_input(*evt))
//            return;
//
//        if(evt->type == INPUT_EVENT_TYPE_CONTROL){
//            if(state == nullptr)
//                return;
//            StateEvent stateEvt = {
//                    .signal = signals[evt->code],
//                    .value = evt->event,
//            };
//            if(state->on_event(&stateEvt) == STATUS_TRANSITION){
//                if(state->get_type() != type){
//                    type = state->get_type();
//                    delete view;
//                    view = Factory::create(state);
//                }
//                else{
//                    view->get_viewModel()->set_state(state);
//                }
//            }
//        }
    }

    void stop_all(){
        stop();

#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
        running = false;
        SDL_WaitThread(thread, nullptr);
#endif

        delete view;
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
