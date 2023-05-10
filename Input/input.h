//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_INPUT_H
#define LCDTEST_INPUT_H

#include <iostream>
#include <list>
#include <string>

// Forward declaration of the Subject class
class Subject;

// Observer abstract class
class Observer {
public:
    virtual void update(Subject* subject) = 0;
};

// Subject abstract class
enum SubjectType{
    SUBJECT_TYPE_INPUT,
};

class Subject {
private:
    std::list<Observer*> observers;
public:
    virtual ~Subject() {}
    virtual SubjectType get_type() = 0;
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    void detach(Observer* observer) {
        observers.remove(observer);
    }
    void notify() {
        for (auto observer : observers) {
            observer->update(this);
        }
    }
};

class InputSubject : public Subject{
private:
    std::pair<int, int> inputEvent;
public:
    void set_data(std::pair<int, int> event){
        inputEvent = event;
    }
    std::pair<int, int> get_data(){
        return inputEvent;
    }

    SubjectType get_type() override {
        return SUBJECT_TYPE_INPUT;
    }
};

void input_register(Observer* observer);
void input_report_key(int scancode, int eventType);



#endif //LCDTEST_INPUT_H
