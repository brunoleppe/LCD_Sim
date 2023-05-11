//
// Created by bleppe on 09/05/23.
//

#include "MainWindow.h"

MainWindow::MainWindow(const char *title) :
        titleBox(0,0,w,20,foreColor,backColor,title,LCD_FONT_SMALL, Text_Left, false),
        optionBox(w,20,WindowHor_Center, WindowVer_Bottom)
{

    add(&titleBox);
    add(&optionBox);
}

void MainWindow::set_title(const char *title) {
    titleBox.set_text(title);
}
