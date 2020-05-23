# DwarfDefenseClone
Simple Dwarf Defense Clone console game.

How to build: 

- Install Boost library on your system, preferably on the default install path
- Please check the CMakeList.txt file. If you installed boost on default path, comment out the ${CMAKE_INCLUDE_PATH} and ${CMAKE_INCLUDE_LIBRARY}.
- Lines 11 and 12 are paths to Boost libraries this project is using
			SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "MyPathToBoostFolder")
			SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "MyPathToBoostFolder/libs")

- Change MyPathToBoostFolder to path where you installed Boost. Check my CMakeList.txt for an example.

![Gameplay](https://imgur.com/h09oJVj)

How to play:
- You are P(Green)
- Enemies are E(Red)
- Treasure chests are T
- !, @, # are impassable objects (Tree, Water, Mountain)
- W -> Weapons, A -> Armor, Q -> Consumable (HP Potion)
- Enemies are walking randomly. I will add A* pathfinding so they are chasing you. Run into enemies to start a fight.
- Use potion by entering its ordinal number in inventory (Beware, you can enter numbers from 1 to 9, use them wisely :P)
- Levels are generated randomly. Your board is n by m large. It can vary between 10x10 and 40x40.