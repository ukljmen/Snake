cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})

find_package(SFML 2 COMPONENTS window graphics audio REQUIRED)

add_compile_options(-Wall -Wextra)

add_executable(snake main.cpp Field.h SnakePart.h SnakeBoard.cpp SnakeBoard.h SnakeView.cpp SnakeView.h Welcome.cpp Welcome.h)

target_link_libraries(snake sfml-system sfml-window sfml-graphics sfml-audio)