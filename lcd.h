#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#ifndef LCD_H
#define LCD_H

typedef enum{
    LCD_FONT_EXTRA_SMALL = 0,
    LCD_FONT_SMALL,
    LCD_FONT_MEDIUM,
}LCD_Fonts;

typedef enum LCD_COLOR{
    LCD_COLOR_BLACK = 0,
    LCD_COLOR_GRAY  = 128,
    LCD_COLOR_WHITE = 255,
}LCD_COLOR;

typedef struct{
    uint8_t     bytes;      ///< Cantidad de bytes por caracter.
    uint8_t     bpr;        ///< Cantidad de bytes por fila. Un pixel es un bit.
    int         cols;
    int         rows;
    uint8_t     *font;      ///< Puntero a la tabla de caracteres.
    uint8_t     *special;   ///< Puntero a la tabla de caracteres especiales.
}LCD_Font;

/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void LCD_init(SDL_Renderer *renderer);

void LCD_deinit();

void LCD_draw_point(int x, int y, uint8_t color);

void LCD_draw_hline(int x, int y, int length, uint8_t color);

void LCD_draw_vline(int x, int y, int length, uint8_t color);

void LCD_draw_rect(int x, int y, int height, int width, uint8_t color);

void LCD_draw_fill(int x, int y, int height, int width, uint8_t color);

void LCD_draw_char(int x, int y, char c, LCD_Fonts font, uint8_t color);

void LCD_draw_string(int x, int y, const char *str, LCD_Fonts font, uint8_t color);

void LCD_draw_bitmap(int x, int y, const uint8_t *bitmap, size_t bitmap_size);

void LCD_clear();

void LCD_print();

const LCD_Font* LCD_get_font(LCD_Fonts font);

#ifdef __cplusplus
}
#endif

#endif //LCD_H