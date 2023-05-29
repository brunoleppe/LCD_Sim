//
// Created by bruno on 21/05/23.
//

#ifndef LCDTEST_INPUTVIEW_H
#define LCDTEST_INPUTVIEW_H


#include "MVC/ViewModels/InputViewModel.h"
#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "debug_bsp.h"
#include "MVC/Views/View.h"


class InputView : public View{
private:
    InputViewModel* viewModel;
    bool cursorToggle = false;
    int cursorCounter = 0;
public:
    explicit InputView(InputViewModel *viewModel) : View(viewModel), viewModel(viewModel){}
    void draw() override{
        static int y = LCD_get_font(LCD_FONT_MEDIUM)->rows;

        LCD_clear();
        LCD_draw_rect(0,0,LCD_HEIGHT,LCD_WIDTH,LCD_COLOR_BLACK);
        LCD_draw_fill(0,0,16,240,LCD_COLOR_BLACK);
        LCD_draw_rect(0,112,16,240,LCD_COLOR_BLACK);

        LCD_draw_hline(20,64,200,LCD_COLOR_BLACK);
        LCD_draw_string(4,2,viewModel->get_title()->c_str(),LCD_FONT_SMALL, LCD_COLOR_WHITE);
        LCD_draw_string(20,40,viewModel->get_string()->c_str(),LCD_FONT_MEDIUM, LCD_COLOR_BLACK);
        LCD_draw_string(4,113, "OPT:     ENTER: aceptar", LCD_FONT_SMALL, LCD_COLOR_BLACK);

        int x = viewModel->get_string()->size() * (LCD_get_font(LCD_FONT_MEDIUM)->cols + 1);
        if(++cursorCounter == 31){
            cursorToggle = !cursorToggle;
            cursorCounter = 0;
        }
        if(cursorToggle){
            LCD_draw_fill(20 + x,40,y,2,LCD_COLOR_BLACK);
        }
    }
    bool set_input(ControllerInputEvent& evt) override{
        bool result = false;
        if(evt.type == INPUT_EVENT_TYPE_ALPHA){
            if(evt.event == INPUT_EVENT_PRESSED)
                viewModel->add_char((char)evt.code);
            else if(evt.event == INPUT_EVENT_CLICKED)
                viewModel->push_char((char)evt.code);
            ERROR_PRINT("%c",(char)evt.code);
            result = true;
        }
        else if(evt.type == INPUT_EVENT_TYPE_CONTROL){
            if(evt.code == CONTROL_TYPE_RETURN && evt.event == INPUT_EVENT_PRESSED){
                viewModel->delete_char();
                result = true;
            }
            else if(evt.code == CONTROL_TYPE_SPACE && evt.event == INPUT_EVENT_PRESSED){
                viewModel->add_char(' ');
                ERROR_PRINT("%c", ' ');
                result = true;
            }
        }
        if(result){
            cursorCounter = 0;
            cursorToggle = true;
        }
        return result;
    }
};


#endif //LCDTEST_INPUTVIEW_H
