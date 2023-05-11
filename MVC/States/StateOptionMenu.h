//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_STATEOPTIONMENU_H
#define LCDTEST_STATEOPTIONMENU_H

#include "MVC/Model.h"

class StateOptionMenu : public Model{
public:
    StateOptionMenu();
    static StateOptionMenu instance;
    void on_event() override;
private:
    MenuMessagePacket stateData;
};


#endif //LCDTEST_STATEOPTIONMENU_H
