#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "lcd.h"
#include <iostream>
#include "input.h"
#include "Test_MVC/Input/input_cpp.h"
#include "Test_MVC/TestStateMachine.h"

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
    SDL_Thread *eventThread;



    if(LCD_init() != 0)
        return 1;

    std::cout << "SDL iniciado" << std::endl;

    TestStateMachine machine;
    input_register(&machine);

#ifdef __linux__
    eventThread = SDL_CreateThread(input_task, "EventThread", nullptr);
    if (eventThread == nullptr)
    {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        running = false;
    }
    std::cout << "hilo de eventos creado" << std::endl;



    // Wait for event handling thread to exit
    SDL_WaitThread(eventThread, nullptr);
    std::cout << "Hilos finalizados" << std::endl;
#elif defined(_WIN32)
    {
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
        }
    }
#endif
    LCD_deinit();
    machine.stop_all();
    return 0;
}