project(emu VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator written to run in RPG Maker 2003.")

set(emu_header EMUEntryPoint.h)

set(emu_source EMUEntryPoint.cpp)

add_library(emu ${emu_header} ${emu_source})

target_include_directories(emu PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(emu PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(emu PRIVATE ${CMAKE_SOURCE_DIR}/src)
    
target_link_libraries(emu PRIVATE core)

target_compile_features(emu PUBLIC cxx_std_17)