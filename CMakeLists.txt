cmake_minimum_required(VERSION 3.16)
project(8085_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add executable
add_executable(8085_emulator
    gui.cpp
    cpu8085.cpp
    cpu8085.h
)

# Link Qt5
target_link_libraries(8085_emulator Qt5::Widgets)
