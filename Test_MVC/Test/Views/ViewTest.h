//
// Created by bruno on 20/05/23.
//

#ifndef LCDTEST_VIEWTEST_H
#define LCDTEST_VIEWTEST_H


#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "MVC/ViewModels/ViewModel.h"

class ViewTest {
protected:
    ViewTest(ViewModel *viewModel) : vm(viewModel){}
    ViewModel* vm;
public:
    virtual ~ViewTest(){
        delete vm;
    }
    ViewModel* get_viewModel(){
        return vm;
    }
    virtual bool set_input(ControllerInputEvent& evt) = 0;
};


#endif //LCDTEST_VIEWTEST_H
