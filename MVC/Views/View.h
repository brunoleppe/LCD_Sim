//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_VIEW_H
#define LCDTEST_VIEW_H


#include "Figures/MenuWindow.h"
#include "MVC/MessagePacket.h"
#include "input.h"
#include "DataTypes/Item.h"
#include "MVC/ControllerInputEvent.h"

class View {
public:
    virtual void draw() = 0;
    virtual ~View() = default;

    virtual void on_alpha_key(INPUT_EVENTS evt, char alpha) = 0;
    virtual void on_numeric_key(INPUT_EVENTS evt, char num) = 0;
    virtual void on_symbol_key(INPUT_EVENTS evt) = 0;
    virtual void on_control_key(INPUT_EVENTS evt, ControlType c)=0;

    virtual void clean() = 0;

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
    void set_items(std::vector<Item*>& items){
        window.add_item(items);


    }

    void clean() override {
        window.clear_items();
    }

    void on_alpha_key(INPUT_EVENTS evt, char alpha) override {
        (void)evt;
    }

    void on_numeric_key(INPUT_EVENTS evt, char num) override {
        window.focus(num - '0');
    }

    void on_symbol_key(INPUT_EVENTS evt) override {
        (void)evt;
    }

    void on_control_key(INPUT_EVENTS evt, ControlType c) override {

    }


    static MenuView instance;
private:
    MenuWindow window;
};


#endif //LCDTEST_VIEW_H
