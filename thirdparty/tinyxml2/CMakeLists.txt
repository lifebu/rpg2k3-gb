cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(tinyxml2)

add_library(tinyxml2 src/tinyxml2/tinyxml2.h src/tinyxml2/tinyxml2.cpp)

target_include_directories(tinyxml2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(tinyxml2 PROPERTIES LINKER_LANGUAGE CXX)