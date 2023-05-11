//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_MAINWINDOW_H
#define LCDTEST_MAINWINDOW_H

#include "Window.h"
#include "TextBox.h"

class MainWindow : public Window {
public:
    explicit MainWindow(const char *title);
    void set_title(const char *title);
private:
    TextBox titleBox;
//    Window area;
    Window optionBox;
};


#endif //LCDTEST_MAINWINDOW_H
