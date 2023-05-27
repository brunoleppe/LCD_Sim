#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "lcd.h"
#include <iostream>
#include "input.h"
#include "Test_MVC/Input/input_cpp.h"
#include "Test_MVC/TestStateMachine.h"
#include "FreeRTOS_mock/timers.h"
#include "music.h"

bool running = true;

int input_task(void *data) {
    SDL_Event event;
    unsigned int elapsed;
    unsigned int initialTime;
    unsigned int finalTime;
    while (running) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT)
            running = false;
        if(event.key.repeat != 0)
            continue;

        if (event.type == SDL_KEYDOWN) {
            initialTime = SDL_GetTicks();
            input_report_key(event.key.keysym.scancode, INPUT_EVENT_PRESSED);
        } else if (event.type == SDL_KEYUP) {
            finalTime = SDL_GetTicks();
            elapsed = finalTime - initialTime;
            input_report_key(event.key.keysym.scancode, INPUT_EVENT_RELEASED);
            if (elapsed <= 1000) {
                input_report_key(event.key.keysym.scancode, INPUT_EVENT_CLICKED);
            } else if (elapsed <= 2000) {
                input_report_key(event.key.keysym.scancode, INPUT_EVENT_LONG_CLICKED);
            } else {
                input_report_key(event.key.keysym.scancode, INPUT_EVENT_LONG_LONG_CLICKED);
            }
        }
        SDL_Delay(20);
    }
    return 0;
}

int state_machine_task(void *data){
    return 0;
}


int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    if(LCD_init() != 0)
        return 1;
    LCD_clear();
    LCD_draw_rect(10,10,10,10,LCD_COLOR_BLACK);
    LCD_print();

    music_initialize();

    std::cout << "SDL iniciado" << std::endl;

    TestStateMachine machine;
    input_register(&machine);
    timer_task();
#ifdef __linux__
//    SDL_Thread *eventThread = SDL_CreateThread(input_task, "EventThread", nullptr);
//    if (eventThread == nullptr)
//    {
//        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
//        running = false;
//    }
//    std::cout << "hilo de eventos creado" << std::endl;
//
//
//
//    // Wait for event handling thread to exit
//    SDL_WaitThread(eventThread, nullptr);
//    std::cout << "Hilos finalizados" << std::endl;
//#elif defined(_WIN32)
    {
        SDL_Event event;
        unsigned int elapsed;
        unsigned int initialTime;
        unsigned int finalTime;
        Uint32 framestart = SDL_GetTicks();
        while (running) {
            if(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    running = false;
                if (event.key.repeat != 0)
                    continue;

                if (event.type == SDL_KEYDOWN) {
                    initialTime = SDL_GetTicks();
                    input_report_key(event.key.keysym.scancode, INPUT_EVENT_PRESSED);
                } else if (event.type == SDL_KEYUP) {

                    finalTime = SDL_GetTicks();
                    elapsed = finalTime - initialTime;
                    input_report_key(event.key.keysym.scancode, INPUT_EVENT_RELEASED);
                    if (elapsed <= 1000) {
                        input_report_key(event.key.keysym.scancode, INPUT_EVENT_CLICKED);
                    } else if (elapsed <= 2000) {
                        input_report_key(event.key.keysym.scancode, INPUT_EVENT_LONG_CLICKED);
                    } else {
                        input_report_key(event.key.keysym.scancode, INPUT_EVENT_LONG_LONG_CLICKED);
                    }
                }
            }
            if((SDL_GetTicks() - framestart) >= 33 ){
                LCD_render();
                framestart = SDL_GetTicks();
            }
        }
    }
#endif
    machine.stop_all();
    LCD_deinit();
    timer_task_stop();
    music_deinit();
    return 0;
}