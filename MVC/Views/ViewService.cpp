//
// Created by bleppe on 12/05/23.
//

#include "ViewService.h"

void ViewService::set_message(MessagePacket *m) {
    if(m->messageType == MESSAGE_TYPE_MENU) {
        MenuView::instance.set_title(m->title);
        MenuView::instance.set_items(m->items);
        v = &MenuView::instance;
        v->set_subject(&subject);
    }
}

ViewService::ViewService() : mss(nullptr){
    v = &MenuView::instance;
}

void ViewService::update() {
    v->draw();
}

ViewService ViewService::instance;

void ViewService::set_event(InputEvent &evt) {
    v->on_event(evt);
}

void ViewService::attach(InputEventObserver *observer) {
    observer->inputSubject = &subject;
    subject.attach(observer);
}
