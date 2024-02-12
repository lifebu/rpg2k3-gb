project(emu VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy emulator written to run in RPG Maker 2003.")


### files
set(emu_header 
    emu/EMUEntryPoint.h
    emu/def/EmuState.h
    emu/io/MMIO.h
    emu/memory/MMU.h
    emu/memory/MBC.h
    emu/util/DebugUtil.h)

set(emu_source 
    emu/EMUEntryPoint.cpp
    emu/io/MMIO.cpp
    emu/memory/MMU.cpp
    emu/memory/MBC.cpp
    emu/util/DebugUtil.cpp)

add_library(emu ${emu_header} ${emu_source})

target_include_directories(emu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(emu PRIVATE emu/pch.h)

### features
target_compile_features(emu PUBLIC cxx_std_17)
#target_set_warnings(emu OFF)


### dependencies
target_link_libraries(emu PRIVATE core)