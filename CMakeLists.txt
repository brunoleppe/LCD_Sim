cmake_minimum_required(VERSION 3.25)
project(LCDTest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include_directories(.)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(LCDTest
        lcd.c
        lcd.h
#        test.c
        Figures/figure.cpp Figures/figure.h Figures/label.cpp Figures/label.h main.cpp)

target_link_libraries(LCDTest ${SDL2_LIBRARIES})
target_link_libraries(LCDTest pthread)