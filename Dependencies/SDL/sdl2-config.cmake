set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")
set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/x64/SDL2main.lib")

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)