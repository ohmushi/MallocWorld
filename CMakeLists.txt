cmake_minimum_required(VERSION 3.17)
project(mallocworld C)

set(CMAKE_C_STANDARD 11)

add_executable(mallocworld sources/main.c sources/character/character.c sources/character/character.h sources/main.h sources/test.c sources/test.h sources/character/test/testCharacter.c sources/character/test/testCharacter.h sources/map/map.c sources/map/map.h sources/map/test/testMap.c sources/map/test/testMap.h sources/zone/zone.c sources/zone/zone.h sources/map/grid_values.h sources/bag/item_id.h sources/bag/bag.c sources/bag/bag.h sources/bag/item_types.h sources/bag/armor/armor.c sources/bag/armor/armor.h sources/bag/heal/heal.c sources/bag/heal/heal.h sources/bag/resource/resource.c sources/bag/resource/resource.h sources/bag/tool/tool.c sources/bag/tool/tool.h sources/bag/weapon/weapon.c sources/bag/weapon/weapon.h sources/config/config.c sources/config/config.h)