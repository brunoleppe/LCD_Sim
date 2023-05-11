//
// Created by bruno on 09/05/23.
//
#include "input_cpp.h"
#include "input.h"

static InputSubject input;

void input_register(Observer* observer)
{
    input.attach(observer);
}
bool input_report_key(int scancode, int eventType)
{
    InputEvent evt ={
            .code = scancode,
            .value = (enum INPUT_EVENTS)eventType
    };
    input.set_data(evt);
    input.notify();
    return true;
}