//
// Created by bleppe on 10/05/23.
//

#include "StateMainMenu.h"
#include "StateOptionMenu.h"

StateMainMenu::StateMainMenu() : Model(&stateData)
{
    stateData.title = "Main Menu";
}

void StateMainMenu::on_event(){
    context->transition(&StateOptionMenu::instance);
}

StateMainMenu StateMainMenu::instance;
