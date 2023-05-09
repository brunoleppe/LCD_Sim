//
// Created by bleppe on 09/05/23.
//

#ifndef LCDTEST_MAKE_UNIQUE_H
#define LCDTEST_MAKE_UNIQUE_H

#include <memory>

template<class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif //LCDTEST_MAKE_UNIQUE_H
