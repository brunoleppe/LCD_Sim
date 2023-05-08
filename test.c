#include <SDL2/SDL.h>
#include <stdbool.h>
#include "lcd.h"
#include <pthread.h>


void* draw_task(void* args){
    
    SDL_Renderer *renderer = (SDL_Renderer*)args;
    // Set the color of the screen to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    LCD_init(renderer);

    // Event loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
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
    return NULL;
}


void *input_task(void *arg) {
    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                LCD_clear();
                printf("Key pressed: scan code %d, event code %d\n",
                       event.key.keysym.scancode, event.key.keysym.sym);
                switch(event.key.keysym.scancode){
                    case 4: LCD_draw_string(0,0, "Hola", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 5: LCD_draw_string(0,0, "Mundo", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 6: LCD_draw_string(0,0, "Hola Mundo", LCD_FONT_SMALL, LCD_COLOR_GRAY); break;
                    case 7:
                        LCD_draw_fill(10,10,20,60,LCD_COLOR_BLACK);
                        LCD_draw_string(10,10,"hola", LCD_FONT_MEDIUM, LCD_COLOR_WHITE);
                        break;
                    default: LCD_draw_string(0,0, "Chao Mundo", LCD_FONT_SMALL, LCD_COLOR_BLACK);
                }    
            } 
            else if (event.type == SDL_QUIT) {
                break;
            }
        }
    }
    return NULL;
}


int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window and a renderer
    SDL_Window* window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 256, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    
    // Create a thread for the draw loop
    pthread_t drawThread;
    pthread_create(&drawThread, NULL, draw_task, renderer);

    pthread_t inputThread;
    pthread_create(&inputThread, NULL, input_task, renderer);

    // Wait for the draw thread to finish
    pthread_join(drawThread, NULL);
    pthread_cancel(inputThread);
    

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}