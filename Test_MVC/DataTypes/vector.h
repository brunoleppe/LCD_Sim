//
// Created by bruno on 18/05/23.
//

#ifndef LCDTEST_VECTOR_H
#define LCDTEST_VECTOR_H

#include <vector>

namespace bru {

template <typename T>
class vector {
private:
    T* buffer;
    int capacity = 1;
    int count;
    void reserve(){
        T *newData = new T[capacity];
        for(int i=0; i<count; i++){
            newData[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newData;
    }
public:

    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const {
            return *ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return *this != other;
        }

    private:
        pointer ptr_;
    };

    vector() : buffer(nullptr), count(0){
        buffer = new T[capacity];
    }

    virtual ~vector() {
        delete[] buffer;
    }

    int size(){
        return count;
    }

    bool empty(){
        return count == 0;
    }

    void push_back(T &&a){
        if(count == capacity){
            capacity *= 2;
            reserve();
        }
        buffer[count++] = a;
    }

    void pop_back(){
        if(count > 0)
            count--;
    }

    T operator[](int index){
        return buffer[index];
    }

    Iterator begin() {
        return Iterator(buffer);
    }

    Iterator end() {
        return Iterator(buffer + count);
    }

};

} // bru

#endif //LCDTEST_VECTOR_H
