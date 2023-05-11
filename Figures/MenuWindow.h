//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_MENUWINDOW_H
#define LCDTEST_MENUWINDOW_H

#include "Window.h"
#include "TextBox.h"

class MenuWindow : public Window {
public:
    explicit MenuWindow(const char *title);
    void set_title(const char *title);

    ~MenuWindow() override;

    void add_item(const char *str);

private:
    TextBox titleBox;
    Window area;
    Window optionBox;
    std::vector<Drawable*> items;
};


#endif //LCDTEST_MENUWINDOW_H
