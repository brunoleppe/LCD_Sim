//
// Created by bruno on 14/05/23.
//

#include "StateLogoScreen.h"
#include "DataTypes/LogoItem.h"
#include "StateMainMenu.h"

StateLogoScreen::StateLogoScreen() {
    data.messageType = MESSAGE_TYPE_LOGO;
    data.items.add(new LogoItem(0, 1,1, nullptr));
}

bool StateLogoScreen::on_event(ControllerInputEvent &evt) {
    if(evt.event == INPUT_EVENT_CLICKED && evt.code == CONTROL_TYPE_ENTER) {
        context->transition(&StateMainMenu::instance);
        return true;
    }
    else if(evt.event == INPUT_EVENT_CLICKED && evt.code == CONTROL_TYPE_RETURN){
        return true;
    }
    return false;
}



void StateLogoScreen::on_enter() {
    running = true;
    thread = SDL_CreateThread(task, "logo_task", this);
}

void StateLogoScreen::on_exit() {
    running = false;
    SDL_WaitThread(thread, nullptr);
}

int StateLogoScreen::task(void *data) {
    auto state = (StateLogoScreen*)data;
    int counter = 0;
    bool change = false;
    while(state->running){
        SDL_Delay(10);
        if(++counter == 100){
            counter = 0;
            auto item = (LogoItem*)state->data.items.items.front();
            if(!change){
                item->width = 1;
                item->height = 2;
                change = true;
            }
            else{
                item->width = 1;
                item->height = 1;
                change = false;
            }
            input_report_key(SDL_SCANCODE_BACKSPACE, INPUT_EVENT_CLICKED);
        }
    }
}

StateLogoScreen StateLogoScreen::instance;