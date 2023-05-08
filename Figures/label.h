//
// Created by bleppe on 08/05/23.
//

#ifndef LCDTEST_LABEL_H
#define LCDTEST_LABEL_H


#include "figure.h"
#include "lcd.h"

class label : figure{
public:
    label(int x, int y, uint8_t back, uint8_t fore, char *str, LCD_Fonts font);
    void draw() override;

private:
    char* str;
    LCD_Fonts font;
public:

};


#endif //LCDTEST_LABEL_H
