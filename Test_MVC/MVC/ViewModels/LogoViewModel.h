//
// Created by bleppe on 19/5/2023.
//

#ifndef LCDTEST_LOGOVIEWMODEL_H
#define LCDTEST_LOGOVIEWMODEL_H


#include "ViewModel.h"
#include "MVC/States/StateLogo.h"
#include "DataTypes/Bitmap.h"

class LogoViewModel : public ViewModel {
private:
    StateLogo* state;
    Bitmap bmp;
public:
    void set_state(State *s) override{
        state = (StateLogo*)state;
        bmp.bitmap = state->get_bitmap();
        bmp.height = 128;
        bmp.width = 240;
    }

    Bitmap* bitmap(){
        return &bmp;
    }

};


#endif //LCDTEST_LOGOVIEWMODEL_H
