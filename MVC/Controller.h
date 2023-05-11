//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_CONTROLLER_H
#define LCDTEST_CONTROLLER_H


#include "Input/input.h"
#include "Model.h"
#include "Views/View.h"
#include "GraphicalService.h"
#include <queue>

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

class Controller : public Observer{
public:

    Controller(GraphicalService* s, MenuView* v);

    void Stop();

    void update(Subject *subject) override;
    static int controller_task(void *data);

    virtual ~Controller() = default;

private:
    GraphicalService *s;
    MenuView *v;

    std::queue<std::pair<int, int>> queue;

    bool running;
};


#endif //LCDTEST_CONTROLLER_H
