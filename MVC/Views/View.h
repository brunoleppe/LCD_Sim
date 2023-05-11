//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Figures/MainWindow.h"

class View {
public:
    virtual void draw() = 0;
    virtual ~View() = default;
private:

};

class MenuView : public View{
public:
    MenuView() : window("")
    {

    }

    void draw() override {
        window.draw();
    }

    void set_title(const char *str){
        window.set_title(str);
    }

private:
    MainWindow window;
};


#endif //LCDTEST_VIEW_H
