//
// Created by bleppe on 09/05/23.
//

#include "MenuWindow.h"

MenuWindow::MenuWindow(const char *title) :
        titleBox(0,0,w,20,foreColor,backColor,title,LCD_FONT_SMALL, Text_Left, false),
        area(w,88),
        optionBox(w,20,WindowHor_Center, WindowVer_Bottom)
{

    add(&titleBox);
    add(&optionBox);
    add(&area);
}

void MenuWindow::set_title(const char *title) {
    titleBox.set_text(title);
}

MenuWindow::~MenuWindow() {

}

void MenuWindow::add_item(const char *str) {
    auto l = new Label(0,0,LCD_COLOR_WHITE, LCD_COLOR_BLACK, str, LCD_FONT_MEDIUM);

}
