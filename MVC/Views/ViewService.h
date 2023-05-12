//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_VIEWSERVICE_H
#define LCDTEST_VIEWSERVICE_H

#include "View.h"
#include "MVC/MessagePacket.h"
#include "MVC/ControllerInputEvent.h"
#include <cstdio>

class ViewService{
private:
    View *v;
    MessagePacket *mss = nullptr;
public:

    ViewService() : mss(nullptr){
        v = &MenuView::instance;
    }

    void update(){
        v->draw();
    }
    void set_message(MessagePacket *m){
        if(m->messageType == MESSAGE_TYPE_MENU) {
            MenuView::instance.set_title(m->title);
            MenuView::instance.set_items(m->items);
            v = &MenuView::instance;
        }
//        if(mss != m) {
//            v->draw();
//
//        }
//
//        mss = m;
    }
    void set_event(ControllerInputEvent &evt){
        if(evt.type == INPUT_EVENT_TYPE_ALPHA && evt.event == INPUT_EVENT_PRESSED){
            printf("Caracter: %c\n", evt.code);
        }
        else if(evt.type == INPUT_EVENT_TYPE_NUMERIC && evt.event == INPUT_EVENT_PRESSED){
            v->on_numeric_key(evt.event, (char)evt.code);
            v->draw();
            printf("Numero: %c\n", evt.code);
        }
        if(evt.type == INPUT_EVENT_TYPE_CONTROL && evt.event == INPUT_EVENT_PRESSED){
            printf("Control: %d\n", evt.code);
        }
    }
};


#endif //LCDTEST_VIEWSERVICE_H
