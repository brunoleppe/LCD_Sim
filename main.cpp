#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include "lcd.h"
#include "Figures/TextBox.h"
#include "Figures/MainWindow.h"
#include <iostream>
#include "Input/input.h"
#include "MVC/Controller.h"
#include "MVC/Model.h"
bool running = true;


int draw_task(void* data){

    SDL_Window* window = static_cast<SDL_Window*>(data);

    // Create renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // Set the color of the screen to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    LCD_init(renderer);
    LCD_draw_string(20,40, "Hola Mundo", LCD_FONT_MEDIUM, LCD_COLOR_BLACK);
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


        // LCD_draw_string(0,0,"HOLA MUNDO",LCD_FONT_MEDIUM, LCD_COLOR_BLACK);


        LCD_print();
        SDL_Delay(30);
    }

    LCD_deinit();
    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


int input_task(void *data) {
    SDL_Event event;
    while (running) {
//        SDL_Delay(1000);
//        printf("Hola\n");
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_KEYDOWN) {
                input_report_key(event.key.keysym.scancode, event.type);
                LCD_clear();
                printf("Char: %c\n", SDL_GetKeyFromScancode(event.key.keysym.scancode));
                switch(event.key.keysym.scancode){
                    case 4: LCD_draw_string(0,0, "Hola", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 5: LCD_draw_string(0,0, "Mundo", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 6: LCD_draw_string(0,0, "Hola Mundo", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 7: {
                        TextBox t(0, 0, 240, 20, LCD_COLOR_GRAY, LCD_COLOR_BLACK, "Titulo 1", LCD_FONT_SMALL, Text_Left);
                        t.draw();
                    }
                        break;
                    case 8:{
                        MainWindow w("Titulo");
                        w.draw();
                        break;
                    }
                    default: LCD_draw_string(0,0, "Chao Mundo", LCD_FONT_SMALL, LCD_COLOR_BLACK);
                }
            }
            else if (event.type == SDL_QUIT) {
                running = false;
            }

        }
    }
    return 0;
}


int main(int argc, char** argv) {

    (void)argc;
    (void)argv;

    Controller controller;
    Model model;
    controller.set_model(model);
    input_register(&controller);



    // Create a window
    SDL_Window* window = SDL_CreateWindow("My Window", 100, 100, 480, 256, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create rendering thread
    SDL_Thread* renderThread = SDL_CreateThread(draw_task, "RenderThread", window);
    if (renderThread == nullptr) {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create event handling thread
    SDL_Thread* eventThread = SDL_CreateThread(input_task, "EventThread", window);
    if (eventThread == nullptr) {
        std::cerr << "SDL_CreateThread Error: " << SDL_GetError() << std::endl;
        running = false;
        SDL_WaitThread(renderThread, nullptr);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Wait for event handling thread to exit
    SDL_WaitThread(eventThread, nullptr);
    // Cleanup
    SDL_WaitThread(renderThread, nullptr);
    model.join();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}