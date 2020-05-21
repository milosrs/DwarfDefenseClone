# DwarfDefenseClone
Simple Dwarf Defense Clone console game for the testing phase of Playrix.

How to build: 

- Install Boost library on your system, preferably on the default install path
- If you installed Boost on any other path, like I did, please check the CMakeList.txt file.
- Lines 11 and 12 are paths to Boost libraries this project is using
			SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "MyPathToBoostFolder")
			SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "MyPathToBoostFolder/libs")

- Change MyPathToBoostFolder to path where you installed Boost. Check my CMakeList.txt for an example.

