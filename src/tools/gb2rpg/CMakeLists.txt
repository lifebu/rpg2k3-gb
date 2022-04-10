cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(gb2rpg VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy rom to map/database rom/ram")

add_executable(gb2rpg gb2rpg.cpp)

target_link_libraries(gb2rpg PRIVATE tinyxml2)

include_directories(${CMAKE_SOURCE_DIR})
target_compile_features(gb2rpg PUBLIC cxx_std_17)