project(gb2rpg VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Gameboy rom to RPG Maker")

set(gb2rpg_cli_headers gb2rpg/cli/CLI.h)
set(gb2rpg_cli_sources gb2rpg/cli/CLI.cpp)

set(gb2rpg_def_headers gb2rpg/def/Globals.h)

set(gb2rpg_file_headers 
    gb2rpg/file/Database.h 
    gb2rpg/file/GBFile.h 
    gb2rpg/file/Map.h 
    gb2rpg/file/MapTree.h)
set(gb2rpg_file_sources 
    gb2rpg/file/Database.cpp 
    gb2rpg/file/GBFile.cpp 
    gb2rpg/file/Map.cpp 
    gb2rpg/file/MapTree.cpp)

set(gb2rpg_project_headers gb2rpg/project/ProjectGenerator.h)
set(gb2rpg_project_sources gb2rpg/project/ProjectGenerator.cpp)

add_executable(gb2rpg gb2rpg.cpp 
    ${gb2rpg_cli_headers} ${gb2rpg_cli_sources}
    ${gb2rpg_def_headers}
    ${gb2rpg_file_headers} ${gb2rpg_file_sources}
    ${gb2rpg_project_headers} ${gb2rpg_project_sources})

target_include_directories(gb2rpg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gb2rpg PRIVATE core)

target_compile_features(gb2rpg PUBLIC cxx_std_17)