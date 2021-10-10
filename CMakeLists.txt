cmake_minimum_required(VERSION 3.17)
project(mallocworld C)

set(CMAKE_C_STANDARD 11)

add_executable(mallocworld sources/main.c sources/character/character.c sources/character/character.h sources/main.h sources/test.c sources/test.h sources/character/test/testCharacter.c sources/character/test/testCharacter.h sources/map/map.c sources/map/map.h sources/map/test/testMap.c sources/map/test/testMap.h sources/zone/zone.c sources/zone/zone.h sources/map/grid_values.h sources/bag/bag_objects.h)