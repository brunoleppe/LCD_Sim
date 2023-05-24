//
// Created by bruno on 23/05/23.
//

#ifndef LCDTEST_STATEMENUTEST1_H
#define LCDTEST_STATEMENUTEST1_H


#include "MVC/States/StateMenu.h"

class StateMenuTest1 : public StateMenu{
public:
    StateMenuTest1(){
        items.push_back("Item 1");
        items.push_back("Item 2");
        items.push_back("Item 3");
        items.push_back("Item 4");
        items.push_back("Item 5");
        items.push_back("Item 6");
        items.push_back("Item 7");
    }
};


#endif //LCDTEST_STATEMENUTEST1_H
