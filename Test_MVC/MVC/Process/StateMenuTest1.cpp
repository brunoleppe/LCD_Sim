//
// Created by bruno on 23/05/23.
//

#include "StateMenuTest1.h"
#include "debug_bsp.h"
#include "input.h"
#include "StateMainLogo.h"

StateMenuTest1::StateMenuTest1() {
    nextState = new StateMainLogo();
    items.push_back("Item 1");
    items.push_back("Item 2");
    items.push_back("Item 3");
    items.push_back("Item 4");
    items.push_back("Item 5");
    items.push_back("Item 6");
    items.push_back("Item 7");
    items.push_back("Item 8");
    items.push_back("Item 9");
    items.push_back("Item 10");
    items.push_back("Item 11");
}
