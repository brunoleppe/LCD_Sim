cmake_minimum_required(VERSION 3.25)
project(LCDTest C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-unwind-tables -fno-rtti -Wno-write-strings -fpermissive -fdata-sections -ffunction-sections -Wall")
    set(SDL2_INCLUDE_DIRS "C:/Users/UsuarioPC/Documents/SDL2/include")
    set(SDL2_LIBRARIES "C:/Users/UsuarioPC/Documents/SDL2/lib")

    message("Hello, ${SDL2_INCLUDE_DIRS}!")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -flto -fno-unwind-tables -fno-rtti -Wno-write-strings -fpermissive -fdata-sections -ffunction-sections -Wall")

endif ()


include_directories(.)
include_directories(Test_MVC)
include_directories(FreeRTOS_mock)
include_directories(BSP)
if (UNIX)
find_package(SDL2 REQUIRED)
endif ()
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
        version.h FreeRTOS_mock/timers.cpp FreeRTOS_mock/timers.h FreeRTOS_mock/FreeRTOS.h FreeRTOS_mock/FreeRTOS_defs.h FreeRTOS_mock/queue.h FreeRTOS_mock/queue.cpp FreeRTOS_mock/task.cpp FreeRTOS_mock/task.h BSP/music.h BSP/music.cpp)

add_subdirectory(Test_MVC)

target_link_libraries(LCDTest MVC)
if (UNIX)
target_link_libraries(LCDTest ${SDL2_LIBRARIES})
target_link_libraries(LCDTest pthread)
else()
target_link_libraries(LCDTest -lmingw32 ${SDL2_LIBRARIES}/libSDL2main.a ${SDL2_LIBRARIES}/libSDL2.dll.a ${SDL2_LIBRARIES}/libSDL2.a)
endif ()

# Include the version script
include(version.cmake)
# Add an option to control whether the version should be updated or not
option(VERSION_UPDATE "Update the version during release build" OFF)
# Add a custom target to update the version header file
add_custom_target(update_version_header ALL
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/version.cmake version.txt)

# Add the custom target as a dependency for your target
add_dependencies(LCDTest update_version_header)

