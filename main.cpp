#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "lcd.h"
#include <iostream>
#include "MVC/Controller.h"
#include "input.h"
#include "Test_MVC/TestStateMachine.h"
#include "Test_MVC/MVC/Process/StateMainLogo.h"
#include "MVC/Process/StateInputTest1.h"

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
    setlocale(LC_ALL, "es_EC.UTF-8");
    (void)argc;
    (void)argv;
    SDL_Thread *eventThread, *controllerThread;
    // Create a window
    SDL_Window* window = SDL_CreateWindow("My Window", 100, 100, 480, 256, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // Create renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // Set the color of the screen to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    LCD_init(renderer);

    std::cout << "SDL iniciado" << std::endl;

    TestStateMachine machine;
//    machine.set_state(new StateInputTest1());
    input_register(&machine);


    std::cout << "MVC iniciado" << std::endl;

    // Create event handling thread
    std::cout << "Creando hilo de eventos" << std::endl;

    eventThread = SDL_CreateThread(input_task, "EventThread", window);
    if (eventThread == nullptr)
    {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        running = false;
        goto CLEAN_UP;
    }
    std::cout << "hilo de eventos creado" << std::endl;



    // Wait for event handling thread to exit
    SDL_WaitThread(eventThread, nullptr);
    std::cout << "Hilos finalizados" << std::endl;

CLEAN_UP:
    LCD_deinit();
    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "SDL finalizado" << std::endl;

    machine.stop();
    return 0;
}