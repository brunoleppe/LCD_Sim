cmake_minimum_required(VERSION 3.25)
project(LCDTest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -flto -fno-unwind-tables -fno-rtti -Wno-write-strings -fpermissive -fdata-sections -ffunction-sections -Wall")

include_directories(.)
include_directories(Test_MVC)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(LCDTest
        lcd.c
        lcd.h
        main.cpp
        input.h
        debug_bsp.h debug_bsp.cpp
        SDL_Queue.cpp SDL_Queue.h
        virtual_term.h
        virtual_term.cpp
        )

add_subdirectory(Test_MVC)

target_link_libraries(LCDTest MVC)
target_link_libraries(LCDTest ${SDL2_LIBRARIES})
target_link_libraries(LCDTest pthread)