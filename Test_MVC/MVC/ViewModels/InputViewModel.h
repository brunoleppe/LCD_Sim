//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_INPUTVIEWMODEL_H
#define LCDTEST_INPUTVIEWMODEL_H


#include "MVC/States/StateInput.h"
#include "ViewModel.h"

class InputViewModel : public ViewModel{
private:
    StateInput* model;
public:
    void set_state(State* state) override{
        model = (StateInput*)state;
    }

    void add_char(char a){
        if(model == nullptr)
            return;
        model->get_string()->push_back(a);
    }

    void delete_char(){
        if(!model->get_string()->empty())
            model->get_string()->pop_back();
    }

};


#endif //LCDTEST_INPUTVIEWMODEL_H
