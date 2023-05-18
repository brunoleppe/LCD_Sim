//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_INPUTVIEWMODEL_H
#define LCDTEST_INPUTVIEWMODEL_H


#include "MVC/States/StateInput.h"

class InputViewModel {
private:
    StateInput* model;
public:
    void set_state(StateInput* state){
        model = state;
    }

    void add_char(char a){
        if(model == nullptr)
            return;
        model->get_string()->push_back(a);
    }

    void delete_char(){
        model->get_string()->pop_back();
    }

};


#endif //LCDTEST_INPUTVIEWMODEL_H
