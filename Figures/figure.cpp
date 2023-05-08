//
// Created by bleppe on 08/05/23.
//

#include "figure.h"

figure::figure(int x, int y, uint8_t back, uint8_t fore) {
    this->x = x;
    this->y = y;
    this->backColor = back;
    this->foreColor = fore;
}
