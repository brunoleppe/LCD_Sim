//
// Created by bruno on 14/05/23.
//

#ifndef LCDTEST_STATELOGOSCREEN_H
#define LCDTEST_STATELOGOSCREEN_H


#include "MVC/Model.h"
#include "SDL2/SDL.h"

class StateLogoScreen : public Model{
public:
    StateLogoScreen();
    bool on_event(ControllerInputEvent &evt) override;
    static StateLogoScreen instance;
    void on_enter() override;
    void on_exit() override;

    bool running;
    static int task(void *data);
    SDL_Thread* thread;
};


#endif //LCDTEST_STATELOGOSCREEN_H
