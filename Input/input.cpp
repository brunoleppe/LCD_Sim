//
// Created by bruno on 09/05/23.
//
#include "input.h"

static InputSubject input;

void input_register(Observer* observer)
{
    input.attach(observer);
}
void input_report_key(int scancode, int eventType)
{
    input.set_data({scancode, eventType});
    input.notify();
}