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
        main.cpp
        input.h

        Figures/Figure.cpp
        Figures/Figure.h
        Figures/Label.cpp
        Figures/Label.h
        Figures/Drawable.h
        Figures/Composite.h
        Figures/Box.cpp Figures/Box.h
        Figures/TextBox.cpp
        Figures/TextBox.h
        Figures/Window.h
        Figures/MenuWindow.cpp
        Figures/MenuWindow.h
        Figures/make_unique.h
        Figures/ItemBox.cpp
        Figures/ItemBox.h

        Input/input_cpp.h
        Input/input.cpp
        Input/virtual_term.h
        Input/virtual_term.cpp
        MVC/Controller.cpp
        MVC/Controller.h
        MVC/Model.cpp MVC/Model.h
        MVC/Views/View.h
        MVC/ModelStateService.h
        MVC/States/StateMainMenu.cpp
        MVC/States/StateMainMenu.h
        MVC/States/StateOptionMenu.cpp
        MVC/States/StateOptionMenu.h
        MVC/MessagePacket.h
        MVC/StateMachine.h
        MVC/Views/ViewService.h
        MVC/Views/View.cpp
        MVC/ControllerInputEvent.h
        DataTypes/Item.cpp
        DataTypes/Item.h
        DataTypes/Observer.h
        MVC/Views/ViewService.cpp
        MVC/Views/ViewService.cpp

        DataTypes/ItemList.cpp DataTypes/ItemList.h DataTypes/LabelItem.cpp DataTypes/LabelItem.h DataTypes/Bitmap.cpp DataTypes/Bitmap.h DataTypes/BitmapItem.cpp DataTypes/BitmapItem.h DataTypes/ItemList.cpp MVC/States/StateLogoScreen.cpp MVC/States/StateLogoScreen.h MVC/Views/MenuView.cpp MVC/Views/MenuView.h MVC/Views/LogoView.cpp MVC/Views/LogoView.h DataTypes/LogoItem.cpp DataTypes/LogoItem.h)

target_link_libraries(LCDTest ${SDL2_LIBRARIES})
target_link_libraries(LCDTest pthread)