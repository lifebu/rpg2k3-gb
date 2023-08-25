cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(rapidxml VERSION 1.13 LANGUAGES CXX DESCRIPTION "Header-only library for C++11 to parse (read) XML data")

add_library(rapidxml src/rapidxml/rapidxml.hpp 
    src/rapidxml/rapidxml_utils.hpp 
    src/rapidxml/rapidxml_print.hpp 
    src/rapidxml/rapidxml_iterators.hpp 
    src/rapidxml/rapidxml_ext.hpp)

target_include_directories(rapidxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(rapidxml PROPERTIES LINKER_LANGUAGE CXX)