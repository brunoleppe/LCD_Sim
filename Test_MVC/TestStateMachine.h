//
// Created by bleppe on 16/05/23.
//

#ifndef LCDTEST_TESTSTATEMACHINE_H
#define LCDTEST_TESTSTATEMACHINE_H


#include "DataTypes/Observer.h"
#include "Test_MVC/MVC/States/StateMachine.h"
#include "MVC/ControllerInputEvent.h"
#include "InputViewTest.h"
#include "MVC/Process/StateInputTest1.h"

class TestStateMachine : public StateMachine, public Observer{

private:
     static StateEventSignal signals[10];
    InputViewTest view;
    InputViewModel viewModel;

public:

    TestStateMachine() : view(), viewModel(){
        auto state = new StateInputTest1();
        view.set_view_model(&viewModel);
        viewModel.set_state(state);
        set_state(state);
    }

    void update(Subject *subject) override{
        auto evt = (ControllerInputEvent*)subject->get_data();

        if(view.set_input(*evt))
            return;

        if(evt->type == INPUT_EVENT_TYPE_CONTROL){
            if(state == nullptr)
                return;
            StateEvent stateEvt = {
                    .signal = signals[evt->code],
                    .value = evt->event,
            };
            if(state->on_event(&stateEvt) == STATUS_TRANSITION){
                viewModel.set_state((StateInput*)state);
            }
        }
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
