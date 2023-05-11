//
// Created by bleppe on 10/05/23.
//

#ifndef LCDTEST_STATEMAINMENU_H
#define LCDTEST_STATEMAINMENU_H

#include "MVC/Model.h"
#include "MVC/ControllerInputEvent.h"


class StateMainMenu : public Model{
public:
    StateMainMenu();
    void on_event(ControllerInputEvent &evt) override;
    static StateMainMenu instance;
private:
    MenuMessagePacket stateData;

};


#endif //LCDTEST_STATEMAINMENU_H
