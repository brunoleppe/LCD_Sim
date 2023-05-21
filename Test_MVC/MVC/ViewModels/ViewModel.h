//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_VIEWMODEL_H
#define LCDTEST_VIEWMODEL_H


#include "MVC/States/StateMachine.h"

class ViewModel {
protected:
    ViewModel() = default;
public:
    virtual ~ViewModel() = default;

    virtual void set_state(State *state) = 0;
};


#endif //LCDTEST_VIEWMODEL_H
