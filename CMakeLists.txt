# CMakeList.txt : CMake project for DwarfDefenseClone, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("DwarfDefenseClone")

# Add source to this project's executable.
add_executable (DwarfDefenseClone "DwarfDefenseClone.cpp" "DwarfDefenseClone.h" "GameModels/Source/Player.cpp" "GameModels/Source/Item.cpp" "GameModels/Source/Enemy.cpp" "GameModels/Source/WorldObject.cpp" "GameModels/Source/Character.cpp")

# TODO: Add tests and install targets if needed.
