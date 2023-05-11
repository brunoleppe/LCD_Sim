//
// Created by bleppe on 10/05/23.
//
#include "StateMainMenu.h"
#include "StateOptionMenu.h"

StateOptionMenu::StateOptionMenu() : Model(&stateData)
{
    stateData.title = "Option Menu";
}

void StateOptionMenu::on_event() {
    context->transition(&StateMainMenu::instance);
}

StateOptionMenu StateOptionMenu::instance;
