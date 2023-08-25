project(gb2rpg VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy rom to RPG Maker")

set(gb2rpg_cli_headers cli/CLI.h)
set(gb2rpg_cli_sources cli/CLI.cpp)

set(gb2rpg_def_headers def/Globals.h)

set(gb2rpg_file_headers file/Database.h file/GBFile.h file/Map.h file/MapTree.h)
set(gb2rpg_file_sources file/Database.cpp file/GBFile.cpp file/Map.cpp file/MapTree.cpp)

set(gb2rpg_project_headers project/ProjectGenerator.h)
set(gb2rpg_project_sources project/ProjectGenerator.cpp)

add_executable(gb2rpg gb2rpg.cpp 
    ${gb2rpg_cli_headers} ${gb2rpg_cli_sources}
    ${gb2rpg_def_headers}
    ${gb2rpg_file_headers} ${gb2rpg_file_sources}
    ${gb2rpg_project_headers} ${gb2rpg_project_sources})

target_include_directories(gb2rpg PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(gb2rpg PRIVATE core)

target_compile_features(gb2rpg PUBLIC cxx_std_17)