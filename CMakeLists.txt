cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
	# Use most recent policies, even for older cmake
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(rpg2k3-gb VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator for RPG Maker 2003")

# modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/tools/cmake/)
include(Dependencies)
include(Warnings)

# execute modules
add_cmake_graphviz_target()

# code
add_subdirectory(src)
add_subdirectory(thirdparty)