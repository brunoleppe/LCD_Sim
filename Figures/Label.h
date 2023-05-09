//
// Created by bleppe on 08/05/23.
//

#ifndef LCDTEST_LABEL_H
#define LCDTEST_LABEL_H


#include "Figure.h"
#include "lcd.h"
#include <string>

enum TextAlignment{
    Text_Center,
    Text_Left,
    Text_Right,
};

class Label : public Figure{
public:
    Label(int x, int y, uint8_t back, uint8_t fore, const char *str, LCD_Fonts font);
    void draw() override;
    void crop_to_width(int width);
private:
    std::string s;
    LCD_Fonts font;
public:

};


#endif //LCDTEST_LABEL_H
