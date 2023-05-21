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

class TestStateMachine : public StateMachine, public Observer{

private:
     static StateEventSignal signals[10];
    ViewTest* view;
    StateType type;
public:

    TestStateMachine() : view(nullptr){
        auto state = new StateMainLogo();
        type = state->get_type();
        view = Factory::create(state);
        set_state(state);
    }

    void update(Subject *subject) override{
        auto evt = (ControllerInputEvent*)subject->get_data();

        if(view->set_input(*evt))
            return;

        if(evt->type == INPUT_EVENT_TYPE_CONTROL){
            if(state == nullptr)
                return;
            StateEvent stateEvt = {
                    .signal = signals[evt->code],
                    .value = evt->event,
            };
            if(state->on_event(&stateEvt) == STATUS_TRANSITION){
                if(state->get_type() != type){
                    type = state->get_type();
                    delete view;
                    view = Factory::create(state);
                }
                else{
                    view->get_viewModel()->set_state(state);
                }
            }
        }
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
