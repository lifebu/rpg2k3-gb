project(emu VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator written to run in RPG Maker 2003.")


### files
set(emu_header emu/EMUEntryPoint.h)

set(emu_source emu/EMUEntryPoint.cpp)

add_library(emu ${emu_header} ${emu_source})

target_include_directories(emu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(emu PRIVATE emu/pch.h)

### features
target_compile_features(emu PUBLIC cxx_std_17)
#target_set_warnings(emu ON)


### dependencies
target_link_libraries(emu PRIVATE core)