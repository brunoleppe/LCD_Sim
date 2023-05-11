//
// Created by bleppe on 11/05/23.
//

#include "ItemBox.h"

ItemBox::~ItemBox() {
    for(auto i : items)
        delete i;
}

void ItemBox::add(Item *i) {
    items.push_back(i);
}

ItemBox::ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        Figure(x, y, width, height, back, fore)
{}

void ListItemBox::draw() {

}

ListItemBox::ListItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore) :
        ItemBox(x, y, width, height, back, fore)
{}
