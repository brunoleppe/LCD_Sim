//
// Created by bleppe on 18/05/23.
//

#ifndef LCDTEST_STRING_H
#define LCDTEST_STRING_H


namespace bru {

class string {
private:
    static const int MaxSize = 64;
    char* buffer;
    int count;
public:

    string() : count(0){
        buffer = new char[MaxSize + 1];
        buffer[0] = 0;
    }
    explicit string(const char *str) : count(0){
        buffer = new char[MaxSize + 1];
        buffer[0] = 0;
        assign(str);
    }

    virtual ~string() {
        delete[] buffer;
    }

    void assign(const char* str){
        count = 0;
        do{
            if(count < MaxSize)
                buffer[count++] = *str++;
        }while(*str);
        buffer[count] = '\0';
    }

    void push_back(char c){
        if(count < MaxSize) {
            buffer[count++] = c;
            buffer[count] = 0;
        }
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
