project(gb2rpg VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy rom to RPG Maker")

set(gp2rpg_headers
    src/CLI.h src/Database.h src/GBFile.h src/Map.h src/MapTree.h 
     src/ProjectGenerator.h src/Globals.h)

set(gp2rpg_source
    src/CLI.cpp src/Database.cpp src/GBFile.cpp src/Map.cpp src/MapTree.cpp
     src/ProjectGenerator.cpp) 

add_executable(gb2rpg gb2rpg.cpp ${gp2rpg_source} ${gp2rpg_headers})

target_include_directories(gb2rpg PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(gb2rpg PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(gb2rpg PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(gb2rpg PRIVATE core)

target_compile_features(gb2rpg PUBLIC cxx_std_17)