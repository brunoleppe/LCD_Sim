//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_LOGOVIEWTEST_H
#define LCDTEST_LOGOVIEWTEST_H


#include "MVC/ViewModels/LogoViewModel.h"
#include "MVC/ControllerInputEvent.h"
#include "debug_bsp.h"

class LogoViewTest {
private:
    LogoViewModel* viewModel;
public:
    void set_view_model(LogoViewModel* vm){
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


#endif //LCDTEST_LOGOVIEWTEST_H
