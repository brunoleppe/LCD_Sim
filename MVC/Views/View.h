//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Figures/MenuWindow.h"
#include "MVC/MessagePacket.h"
#include "input.h"

class View {
public:
    virtual void draw() = 0;
    virtual ~View() = default;

    virtual void on_alpha_key(INPUT_EVENTS evt) = 0;
    virtual void on_numeric_key(INPUT_EVENTS evt) = 0;
    virtual void on_symbol_key(INPUT_EVENTS evt) = 0;
    virtual void on_control_key(INPUT_EVENTS evt)=0;

    void set_message(MessagePacket *msg);

private:
    MessagePacket *msg;
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
    void set_items(std::vector<const char*>& items){

    }


    void on_alpha_key(INPUT_EVENTS evt) override {
        (void)evt;
    }

    void on_numeric_key(INPUT_EVENTS evt) override {

    }

    void on_symbol_key(INPUT_EVENTS evt) override {
        (void)evt;
    }

    void on_control_key(INPUT_EVENTS evt) override {

    }


    static MenuView instance;
private:
    MenuWindow window;
};


#endif //LCDTEST_VIEW_H
