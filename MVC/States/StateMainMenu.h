//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_STATEMAINMENU_H
#define LCDTEST_STATEMAINMENU_H

#include "MVC/Model.h"


class StateMainMenu : public Model{
public:
    StateMainMenu();
    void on_event() override;
    static StateMainMenu instance;
private:
    MenuMessagePacket stateData;

};


#endif //LCDTEST_STATEMAINMENU_H
