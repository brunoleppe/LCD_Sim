//
// Created by bleppe on 08/05/23.
//

#ifndef LCDTEST_FIGURE_H
#define LCDTEST_FIGURE_H

#include <cstdint>
#include <list>
#include "Drawable.h"

class Composite;

class Figure : public Drawable{

public:
    friend class Composite;

protected:
    Figure(int x, int y, uint8_t back, uint8_t fore);
    Figure(int x, int y, int width, int height, uint8_t back, uint8_t fore);

public:
    void set_position(int x, int y) override;

    Position get_position() override;

    Size get_size() override;

    void invert_colors() override;

    ~Figure() override;
};


#endif //LCDTEST_FIGURE_H
