cmake_minimum_required(VERSION 3.29)
project(snake)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "/pathto/g++")
set(CMAKE_C_COMPILER "/pathto/gcc")



add_executable(snake
        src/main.cpp
        inc/snake.cpp
        inc/snake.h)
