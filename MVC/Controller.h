//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_CONTROLLER_H
#define LCDTEST_CONTROLLER_H


#include "Input/input_cpp.h"
#include "Model.h"
#include "ModelStateService.h"
#include "MVC/Views/ViewService.h"
#include <queue>

class Controller : public Observer{
public:

    Controller(ModelStateService* s, ViewService* v);

    void Stop();

    void update(Subject *subject) override;
    static int controller_task(void *data);

private:
    ModelStateService *model;
    ViewService *view;

    std::queue<InputEvent> queue;

    bool running;
};


#endif //LCDTEST_CONTROLLER_H
