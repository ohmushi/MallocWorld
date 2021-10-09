cmake_minimum_required(VERSION 3.17)
project(mallocworld C)

set(CMAKE_C_STANDARD 11)

add_executable(mallocworld sources/main.c sources/character/character.c sources/character/character.h sources/main.h)