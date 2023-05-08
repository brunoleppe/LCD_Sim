//
// Created by bleppe on 08/05/23.
//

#include "label.h"
#include <cstring>
label::label(int x, int y, uint8_t back, uint8_t fore, char *str, LCD_Fonts font) : figure(x, y, back, fore), str(str),
                                                                                    font(font)
{
    height = LCD_get_font(font)->rows;
    width = strlen(str) * (LCD_get_font(font)->cols + 1);
}

void label::draw() {
    LCD_draw_fill(x,y,height,width,backColor);
    LCD_draw_string(x,y,str,font,foreColor);
}
