//
// Created by bruno on 17/05/23.
//

#ifndef LCDTEST_INPUTVIEWTEST_H
#define LCDTEST_INPUTVIEWTEST_H


#include "MVC/ViewModels/InputViewModel.h"
#include "MVC/ControllerInputEvent.h"
#include "debug_bsp.h"
class InputViewTest {
private:
    InputViewModel* viewModel;
public:



    void set_view_model(InputViewModel* vm){
        viewModel = vm;
    }
    bool set_input(ControllerInputEvent& evt){
        if(evt.type == INPUT_EVENT_TYPE_ALPHA && evt.event == INPUT_EVENT_PRESSED){
            viewModel->add_char((char)evt.code);
            ERROR_PRINT("%c",(char)evt.code);
            return true;
        }
        else if(evt.type == INPUT_EVENT_TYPE_CONTROL){
            if(evt.code == CONTROL_TYPE_RETURN && evt.event == INPUT_EVENT_PRESSED){
                viewModel->delete_char();
                return true;
            }
            else if(evt.code == CONTROL_TYPE_SPACE && evt.event == INPUT_EVENT_PRESSED){
                viewModel->add_char(' ');
                ERROR_PRINT("%c", ' ');
                return true;
            }
        }
        return false;
    }
};


#endif //LCDTEST_INPUTVIEWTEST_H
