//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_VIEWSERVICE_H
#define LCDTEST_VIEWSERVICE_H

#include "View.h"
#include "Test_MVC/DataTypes/ControllerInputEvent.h"
#include "Test_MVC/DataTypes/Observer.h"
#include "DataTypes/queue.h"

#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
#include "FreeRTOS.h"
#include "queue.h"
#else

#include <cstdio>
#endif

class ViewService{
private:
    View *v;
    ViewService();
    Subject subject;

    static void task(void *);
#if defined(PIC32) || defined(__PIC32) || defined(__PIC32__)
    QueueHandle_t queue;
#else
    bru::queue<InputEvent> queue;
    bool running = true;
    SDL_Thread* thread;
#endif
public:

    static ViewService instance;

    void update();
    void set_event(InputEvent& evt);
    void attach(Observer* observer);



#if !defined(PIC32) && !defined(__PIC32) && !defined(__PIC32__)
    void start();
    void stop();
#endif
};


#endif //LCDTEST_VIEWSERVICE_H
