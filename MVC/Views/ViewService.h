//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_VIEWSERVICE_H
#define LCDTEST_VIEWSERVICE_H

#include "View.h"
#include "MVC/MessagePacket.h"
#include "MVC/ControllerInputEvent.h"
#include "DataTypes/Observer.h"
#include <cstdio>

class ViewService{
private:
    View *v;
    MessagePacket *mss = nullptr;
    ViewService();
    Subject<InputEvent> subject;
public:

    static ViewService instance;

    void update();
    void set_message(MessagePacket *m);
    void set_event(InputEvent& evt);
    void attach(InputEventObserver* observer);
};


#endif //LCDTEST_VIEWSERVICE_H
