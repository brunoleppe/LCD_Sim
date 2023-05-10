//
// Created by bruno on 09/05/23.
//

#include "Controller.h"
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include "Model.h"

void Controller::update(Subject *subject) {

    auto type = subject->get_type();
    auto input = (InputSubject *) subject;
    InputEvent event{};

    if(type == SUBJECT_TYPE_INPUT) {

//        printf("Event: %d, %d\n", input->get_data().first, input->get_data().second);
        if ((input->get_data().first >= 4) && (input->get_data().first <= 29)) {

            event.type = TYPE_CHAR;
            event.data.ch = (char) SDL_GetKeyFromScancode((SDL_Scancode) input->get_data().first);

        } else {
            event.type = TYPE_COMMAND;
            switch (input->get_data().first) {
                case 81:
                    event.data.command = COMMAND_MOVE_DOWN;
                    break;
                case 82:
                    event.data.command = COMMAND_MOVE_UP;
                    break;
                case 42:
                    event.data.command = COMMAND_RETURN;
                    break;
                case 40:
                    event.data.command = COMMAND_ENTER;
                    break;
                case 41:
                    event.data.command = COMMAND_CANCEL;
                    break;
                case 58:
                    event.data.command = COMMAND_OPTION;
                    break;

            }
        }
        event.state = input->get_data().second == (int) SDL_KEYDOWN ? PRESSED : RELEASED;
    }
    model->update_state(event);
//    report_event(event);
}

void Controller::set_model(Model &model_) {
    model = &model_;
}
