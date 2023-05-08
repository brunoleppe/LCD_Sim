//
// Created by bleppe on 08/05/23.
//

#ifndef LCDTEST_FIGURE_H
#define LCDTEST_FIGURE_H

#include "cstdint"

class figure{
public:
    virtual void draw() = 0;
protected:
    int width;
    int height;
    int x,y;
    uint8_t foreColor;
    uint8_t backColor;
    figure(int x, int y, uint8_t back, uint8_t fore);
};


#endif //LCDTEST_FIGURE_H
