//
// Created by bruno on 23/05/23.
//

#ifndef LCDTEST_ITEMVIEW_H
#define LCDTEST_ITEMVIEW_H


#include "View.h"
#include "MVC/ViewModels/ItemViewModel.h"

class ItemView : public View {
private:
    ItemViewModel* vm;
    int currentItemIndex = 0;
public:
    ItemView(ItemViewModel *vm) : View(vm), vm(vm) {

    }
    void draw() override{

        LCD_clear();
        LCD_draw_rect(0,0,LCD_HEIGHT,LCD_WIDTH,LCD_COLOR_BLACK);
        LCD_draw_fill(0,0,16,240,LCD_COLOR_BLACK);

        // Clear the LCD display
// Draw the title string
        LCD_draw_string(4, 2, "Title", LCD_FONT_SMALL, LCD_COLOR_WHITE);

// Calculate the vertical position for each item
        int yOffset = 30;

// Draw the menu items
        for (size_t i = 0; i < vm->get_items()->size(); ++i) {
            // Calculate the y-coordinate for the current item
            int y = yOffset + (i * 20);

            // Draw the textbox for the item
            LCD_draw_fill(0, y, 20, 240, LCD_COLOR_WHITE);

            // If the item is currently selected, invert the colors
            if (i == currentItemIndex) {
                LCD_draw_fill(0, y, 20, 240, LCD_invert_color(LCD_COLOR_WHITE));
                LCD_draw_string(10, y+4, (*vm->get_items())[i], LCD_FONT_SMALL, LCD_invert_color(LCD_COLOR_BLACK));
            } else {
                LCD_draw_string(10, y+4, (*vm->get_items())[i], LCD_FONT_SMALL, LCD_COLOR_BLACK);
            }
        }


    }
    bool set_input(ControllerInputEvent &evt) override{
        if(evt.type == INPUT_EVENT_TYPE_CONTROL && evt.event == INPUT_EVENT_PRESSED){
            if(evt.code == CONTROL_TYPE_DOWN){
                if(++currentItemIndex >= vm->get_items()->size())
                    currentItemIndex = 0;
            }
            else if(evt.code == CONTROL_TYPE_UP){
                if(--currentItemIndex < 0)
                    currentItemIndex = vm->get_items()->size()-1;
            }
        }
        return false;
    }
};


#endif //LCDTEST_ITEMVIEW_H
