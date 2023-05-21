//
// Created by bruno on 20/05/23.
//

#ifndef LCDTEST_FACTORY_H
#define LCDTEST_FACTORY_H


#include "Test/Views/ViewTest.h"
#include "MVC/States/StateMachine.h"
#include "Test/Views/LogoViewTest.h"
#include "Test/Views/InputViewTest.h"

class Factory {
private:
    Factory() = default;
public:
    static ViewTest* create(State* state){
        ViewTest* view = nullptr;
        switch (state->get_type()) {
            case STATE_TYPE_BASE:
                view = nullptr;
                break;
            case STATE_TYPE_LOGO:
            {
                auto model = new LogoViewModel();
                model->set_state(state);
                view = new LogoViewTest(model);
            }
                break;
            case STATE_TYPE_MENU:
                break;
            case STATE_TYPE_INPUT:
            {
                auto model = new InputViewModel();
                model->set_state(state);
                view = new InputViewTest(model);
            }
                break;
            case STATE_TYPE_DATA:
                break;
            case STATE_TYPE_NETCONFIG:
                break;
        }
        return view;
    }
};


#endif //LCDTEST_FACTORY_H
