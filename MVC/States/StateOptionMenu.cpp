//
// Created by bleppe on 10/05/23.
//
#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"

StateOptionMenu::StateOptionMenu() : Model(&stateData)
{
    stateData.title = "Option Menu";
}

void StateOptionMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED)
        context->transition(&StateMainMenu::instance);

}

StateOptionMenu StateOptionMenu::instance;
