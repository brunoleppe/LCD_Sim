#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "lcd.h"
#include <iostream>
#include "Input/input.h"
#include "MVC/Controller.h"
#include "MVC/Model.h"
#include "MVC/States/StateMainMenu.h"

#include <pthread.h>
#include <signal.h>

bool running = true;

pthread_mutex_t controller_mutex = PTHREAD_MUTEX_INITIALIZER;

int draw_task(void* data){
    // Event loop
    SDL_Event event;
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        LCD_print();
        SDL_Delay(30);
    }
    return 0;
}
int input_task(void *data) {
    SDL_Event event;
    while (running) {
        if (SDL_PollEvent(&event)) {
//            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            if (event.type == SDL_KEYDOWN)
            {
                pthread_mutex_lock(&controller_mutex);
                input_report_key(event.key.keysym.scancode, event.type);
                pthread_mutex_unlock(&controller_mutex);
            }
            else if (event.type == SDL_QUIT) {
                running = false;
            }

        }
        SDL_Delay(10);
    }
    return 0;
}


int main(int argc, char** argv) {

    (void)argc;
    (void)argv;

    // Create a window
    SDL_Window* window = SDL_CreateWindow("My Window", 100, 100, 480, 256, SDL_WINDOW_SHOWN);
    // Create renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // Set the color of the screen to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    LCD_init(renderer);

    std::cout << "SDL iniciado" << std::endl;

    auto *v = new MenuView();
    auto *s = new GraphicalService();
    s->set_state(&StateMainMenu::instance);
    auto *c = new Controller(s, v);
    input_register(c);

    std::cout << "MVC iniciado" << std::endl;


    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create rendering thread
    std::cout << "Creando hilo de renderizado" << std::endl;

    SDL_Thread* renderThread = SDL_CreateThread(draw_task, "RenderThread", window);
//    pthread_t renderThread;
//    int res = pthread_create(&renderThread, nullptr, (void* (*)(void*))draw_task, window);
    if(renderThread == nullptr)
//    if (res != 0)
    {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    std::cout << "Hilo de renderizado creado" << std::endl;

    // Create event handling thread

    std::cout << "Creando hilo de eventos" << std::endl;

    SDL_Thread* eventThread = SDL_CreateThread(input_task, "EventThread", window);
//    pthread_t eventThread;
//    res = pthread_create(&eventThread, nullptr, (void* (*)(void*)) input_task, nullptr);
    if (eventThread == nullptr)
//    if(res != 0)
    {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        running = false;
        SDL_WaitThread(renderThread, nullptr);
//        pthread_join(renderThread,nullptr);
        LCD_deinit();
        // Clean up and quit SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    std::cout << "hilo de eventos creado" << std::endl;

    SDL_Thread* controllerThread = SDL_CreateThread(Controller::controller_task, "controllerTask", c);
//    pthread_t controllerThread;
//    res = pthread_create(&controllerThread, nullptr, (void* (*)(void*))controller_task, c);
//    if(res != 0)
//    {
//        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
//        running = false;
////        SDL_WaitThread(renderThread, nullptr);
//        pthread_join(eventThread,nullptr);
//        pthread_join(renderThread,nullptr);
//        LCD_deinit();
//        // Clean up and quit SDL
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }

    // Wait for event handling thread to exit
    SDL_WaitThread(eventThread, nullptr);
    SDL_WaitThread(renderThread, nullptr);
    c->Stop();
    SDL_WaitThread(controllerThread, nullptr);
//    pthread_join(renderThread,nullptr);
//    pthread_join(eventThread,nullptr);

    std::cout << "Hilos finalizados" << std::endl;

//    pthread_kill(SDL_ThreadID(), 0);
//    pthread_kill(controllerThread,0);
    // Cleanup


    LCD_deinit();
    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "SDL finalizado" << std::endl;

    delete c;
    delete v;
    delete s;
    return 0;
}