cmake_minimum_required(VERSION 3.17)
project(mallocworld C)

set(CMAKE_C_STANDARD 11)

add_executable(mallocworld
        sources/main.c sources/main.h
        sources/tests/test.c sources/tests/test.h
        sources/player/player.c sources/player/player.h sources/player/tests/test_player.c sources/player/tests/test_player.h
        sources/map/map.c sources/map/map.h sources/map/test/testMap.c sources/map/test/testMap.h
        sources/map/cell.c sources/map/cell.h
        sources/zone/zone.c sources/zone/zone.h
        sources/bag/bag.c sources/bag/bag.h sources/bag/tests/test_bag.c sources/bag/tests/test_bag.h
        sources/config/config.c sources/config/config.h
        sources/movement/movement.c sources/movement/movement.h
        sources/movement/tests/test_movement.c sources/movement/tests/test_movement.h
        sources/movement/location.h sources/movement/location.c
        sources/movement/direction.h
        sources/npc/npc.c sources/npc/npc.h sources/npc/tests/test_npc.c sources/npc/tests/test_npc.h
        sources/chest/chest.c sources/chest/chest.h
        sources/chest/tests/testChest.c sources/chest/tests/testChest.h
        sources/save/save.c sources/save/save.h
        sources/turn_based/turn_based.c sources/turn_based/turn_based.h
        sources/turn_based/tests/test_turn_based.c sources/turn_based/tests/test_turn_based.h
        sources/cli/cli.c sources/cli/cli.h
        sources/collect_resources/collect_resources.c sources/collect_resources/collect_resources.h sources/collect_resources/tests/test_collect_resources.c sources/collect_resources/tests/test_collect_resources.h
        sources/item/item_id.h
        sources/item/item.c sources/item/item.h sources/item/tests/test_item.c sources/item/tests/test_item.h
        sources/item/material.h
        sources/item/tool/tool_family.h
        sources/item/tool/tool.c sources/item/tool/tool.h
        sources/item/item_type.h
        sources/item/craft_resource/craft_resource.c sources/item/craft_resource/craft_resource.h
        sources/item/weapon/weapon.c sources/item/weapon/weapon.h
        sources/item/heal/heal.c sources/item/heal/heal.h
        sources/craft/craft.c sources/craft/craft.h sources/craft/tests/test_craft.c sources/craft/tests/test_craft.h
        sources/monster/monster.c sources/monster/monster.h sources/monster/test_monster/test_monster.c sources/monster/test_monster/test_monster.h
        sources/random/random.c sources/random/random.h
        sources/perlin_noise/perlin_noise.c sources/perlin_noise/perlin_noise.h
        sources/start/start.c sources/start/start.h
        sources/resources_reappearance/resources_reappearance.c sources/resources_reappearance/resources_reappearance.h sources/resources_reappearance/tests/test_resouces_reappearance.c sources/resources_reappearance/tests/test_resouces_reappearance.h)