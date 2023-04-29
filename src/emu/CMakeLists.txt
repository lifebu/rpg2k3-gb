cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()


set(emu_header EMUEntryPoint.h)

set(emu_source EMUEntryPoint.cpp)

project(emu VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator written to run in RPG Maker 2003.")


add_library(emu ${emu_header} ${emu_source})

target_include_directories(emu PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(emu PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(emu PRIVATE ${CMAKE_SOURCE_DIR}/src)
    
target_link_libraries(emu PRIVATE core)

target_compile_features(emu PUBLIC cxx_std_17)