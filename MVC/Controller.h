//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_CONTROLLER_H
#define LCDTEST_CONTROLLER_H


#include "Input/input.h"

enum Command {
    COMMAND_ENTER = 0,
    COMMAND_RETURN,
    COMMAND_CANCEL,
    COMMAND_OPTION,
    COMMAND_MOVE_UP,
    COMMAND_MOVE_DOWN
};

enum EventType {
    TYPE_CHAR,
    TYPE_COMMAND
};

enum EventState {
    PRESSED,
    RELEASED,
    CLICKED,
};

struct InputEvent {
    EventType type;
    union {
        char ch;
        Command command;
    } data;
    EventState state;
};

class Model;
class View;

class Controller : public Observer{
public:
    void update(Subject *subject) override;
    void set_model(Model &model);
private:
    void report_event(InputEvent &inputEvent);
    Model *model;
};


#endif //LCDTEST_CONTROLLER_H
