cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(rpg2k3-gb VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator for RPG Maker 2003")

# core
add_subdirectory(src/core)

# tools
add_subdirectory(src/tools/gb2rpg)

# thirdparty
add_subdirectory(thirdparty/tinyxml2)
add_subdirectory(thirdparty/liblcf)
file(COPY "build/thirdparty/liblcf/lcf2xml" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/tools/gb2rpg/gp2rpg")