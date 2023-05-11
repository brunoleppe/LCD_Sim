cmake_minimum_required(VERSION 3.25)
project(LCDTest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-unwind-tables -fno-rtti -Wno-write-strings -fpermissive -fdata-sections -ffunction-sections -Wall")

include_directories(.)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(LCDTest
        lcd.c
        lcd.h
#        test.c
        Figures/Figure.cpp Figures/Figure.h Figures/Label.cpp Figures/Label.h main.cpp Figures/Drawable.h
        Figures/Composite.h Figures/Box.cpp Figures/Box.h Figures/TextBox.cpp Figures/TextBox.h Figures/Window.h
        Figures/MainWindow.cpp Figures/MainWindow.h Figures/make_unique.h Input/input.h MVC/Controller.cpp
        MVC/Controller.h Input/input.cpp MVC/Model.cpp MVC/Model.h MVC/Views/View.h threads.cpp threads.h
        MVC/GraphicalService.h MVC/States/StateMainMenu.cpp MVC/States/StateMainMenu.h
        MVC/States/StateOptionMenu.cpp MVC/States/StateOptionMenu.h MVC/MessagePacket.h MVC/StateMachine.h)

target_link_libraries(LCDTest ${SDL2_LIBRARIES})
target_link_libraries(LCDTest pthread)