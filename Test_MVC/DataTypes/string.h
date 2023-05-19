//
// Created by bleppe on 18/05/23.
//

#ifndef LCDTEST_STRING_H
#define LCDTEST_STRING_H

#include <cstring>

namespace bru {

class string {
private:
    char* buffer;
    int count;
    int capacity;

    void reserve(){
        char *newData = new char[capacity + 1];
        for(int i=0; i<count; i++){
            newData[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newData;
    }
public:

    string() : count(0), capacity(1){
        buffer = new char[capacity + 1];
        buffer[0] = 0;
    }
    explicit string(const char *str) : count(0){
        buffer = new char[capacity + 1];
        buffer[0] = 0;
        assign(str);
    }

    virtual ~string() {
        delete[] buffer;
    }

    void assign(const char* str){
        count = 0;
        int len = (int)strlen(str);
        if(capacity <= len){
            while(capacity < len){
                capacity *= 2;
            }
            reserve();
        }
        do{
//            if(count < MaxSize)
                buffer[count++] = *str++;
        }while(*str);
        buffer[count] = '\0';
    }

    void push_back(char c){

        if(count == capacity){
            capacity <<= 1;
            reserve();
        }

//        if(count < MaxSize) {
            buffer[count++] = c;
            buffer[count] = 0;
//        }
    }
    void pop_back(){
        if(count > 0)
            buffer[--count] = 0;
    }
    int size() const{
        return count;
    }
    const char* c_str(){
        return buffer;
    }

    char operator[](int index) {
        if(index < count)
            return buffer[index];
        return 0;
    }

    bool empty() const{
        return count == 0;
    }

};

} // bru

#endif //LCDTEST_STRING_H
