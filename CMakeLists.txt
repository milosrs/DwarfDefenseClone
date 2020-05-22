# CMakeList.txt : CMake project for DwarfDefenseClone, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("DwarfDefenseClone")
set (CMAKE_CXX_STANDARD 17)

#Add boost to project
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Users/milos/Desktop/boost_1_73_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Users/milos/Desktop/boost_1_73_0/libs")

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(SYSTEM ${BOOST_INCLUDE})

#Add SDL to project

#Add this projects sources
add_executable (DwarfDefenseClone "DwarfDefenseClone.cpp" "DwarfDefenseClone.h" 
            "GameModels/Source/Player.cpp" "GameModels/Source/Item.cpp" "GameModels/Source/Enemy.cpp" "GameModels/Source/WorldObject.cpp" "GameModels/Source/Character.cpp" "GameModels/Source/World.cpp" 
           "WorldController/Headers/WorldController.h" "WorldController/Sources/WorldController.cpp" "GameModels/Source/Treasure.cpp" "AI/Sources/AStar.cpp" "AI/Sources/SearchCell.cpp")