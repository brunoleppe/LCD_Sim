//
// Created by bleppe on 11/05/23.
//

#ifndef LCDTEST_ITEMBOX_H
#define LCDTEST_ITEMBOX_H

#include <vector>
#include "Figure.h"

class Item{
private:
    int index;
    bool selected;
public:
    int get_index(){
        return index;
    }
    bool get_selected(){
        return selected;
    }
    void set_selected(bool s){
        selected = s;
    }
};

class ItemBox : public Figure{
protected:
    std::vector<Item*> items;
public:
    ItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore);

public:
    ~ItemBox() override;
    void add(Item* i);
};

class ListItemBox : public ItemBox{
public:
    void draw() override;

    ListItemBox(int x, int y, int width, int height, uint8_t back, uint8_t fore);
private:
    int count;
    int maxItemsInView;
    int startIndex;
};

#endif //LCDTEST_ITEMBOX_H
