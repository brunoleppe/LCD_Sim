//
// Created by bleppe on 10/05/23.
//

#include "StateMainMenu.h"
#include "StateOptionMenu.h"
#include "MVC/ControllerInputEvent.h"
#include "input.h"

StateMainMenu::StateMainMenu() : Model(&stateData)
{
    stateData.title = "Main Menu";
}

void StateMainMenu::on_event(ControllerInputEvent &evt) {

    if(evt.event == INPUT_EVENT_CLICKED)
        context->transition(&StateOptionMenu::instance);

}

StateMainMenu StateMainMenu::instance;
