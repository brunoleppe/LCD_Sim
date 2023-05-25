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
#include "task.h"


class TestStateMachine : public StateMachine, public Observer{

private:
    static StateEventSignal signals[10];
    View* view;
    StateType type;
    QueueHandle_t queue;
    bool running = true;

    TaskHandle_t stateMachineTask = {};

    static void
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
            vTaskDelay(16);
        }
    }

public:

    TestStateMachine() : view(nullptr){
        auto state = new StateMainLogo();
        type = state->get_type();
        view = Factory::create(state);
        set_state(state);
        running = true;
        xTaskCreate(task,"controller_task",1024,this,2, &stateMachineTask);
        queue = xQueueCreate(2,sizeof(ControllerInputEvent));
    }

    void update(Subject *subject) override{
        auto evt = *(ControllerInputEvent*)subject->get_data();
        xQueueSend(queue,&evt,10);
    }

    void stop_all(){
        running = false;
        vTaskDelete(stateMachineTask);
        stop();
        delete view;
    }
};


#endif //LCDTEST_TESTSTATEMACHINE_H
