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
        LCD_draw_rect(0,112,16,240,LCD_COLOR_BLACK);

        LCD_draw_string(4, 2, vm->get_title()->c_str(), LCD_FONT_SMALL, LCD_COLOR_WHITE);

        int startPos = 20;
        int size = vm->get_items()->size();
        int startIndex = 0;
        int maxItems = 5;
        if(currentItemIndex >= maxItems){
            startIndex = currentItemIndex - maxItems + 1;
            size -= startIndex;
        }
        maxItems = size < maxItems ? size : maxItems;
        for(int i=0; i<maxItems; i++){
            char buffer[4];
            sprintf(buffer, "%-2d.", startIndex + 1);
            if(currentItemIndex == startIndex){
                LCD_draw_fill(2, startPos, 14, 236, LCD_COLOR_BLACK);
                LCD_draw_string(4,startPos+1,buffer, LCD_FONT_SMALL,LCD_COLOR_WHITE);
                LCD_draw_string(32,startPos+1,(*vm->get_items())[startIndex], LCD_FONT_SMALL,LCD_COLOR_WHITE);
            }
            else {
                LCD_draw_fill(2, startPos, 16, 236, LCD_COLOR_WHITE);
                LCD_draw_string(4, startPos + 2, buffer, LCD_FONT_SMALL, LCD_COLOR_BLACK);
                LCD_draw_string(32, startPos + 2, (*vm->get_items())[startIndex], LCD_FONT_SMALL, LCD_COLOR_BLACK);
            }
            startPos += 16;
            ++startIndex;
        }

    }
    bool set_input(ControllerInputEvent &evt) override{
        if(evt.type == INPUT_EVENT_TYPE_CONTROL){
            if(evt.code == CONTROL_TYPE_DOWN && evt.event == INPUT_EVENT_PRESSED){
                if(++currentItemIndex >= vm->get_items()->size()) {
                    currentItemIndex = 0;
                    return true;
                }
            }
            else if(evt.code == CONTROL_TYPE_UP && evt.event == INPUT_EVENT_PRESSED){
                if(--currentItemIndex < 0) {
                    currentItemIndex = vm->get_items()->size() - 1;
                    return true;
                }
            }
            else if(evt.code == CONTROL_TYPE_ENTER && evt.event == INPUT_EVENT_CLICKED){
                vm->set_selected_index(currentItemIndex);
                return false;
            }
        }
        return false;
    }
};


#endif //LCDTEST_ITEMVIEW_H
