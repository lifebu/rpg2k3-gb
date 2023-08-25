project(rapidxml VERSION 1.13 LANGUAGES CXX DESCRIPTION "Header-only library for C++11 to parse (read) XML data")


### files
set(rapidxml_headers 
    src/rapidxml/rapidxml.hpp 
    src/rapidxml/rapidxml_utils.hpp 
    src/rapidxml/rapidxml_print.hpp 
    src/rapidxml/rapidxml_iterators.hpp 
    src/rapidxml/rapidxml_ext.hpp)

add_library(rapidxml ${rapidxml_headers})

target_include_directories(rapidxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


### features
set_target_properties(rapidxml PROPERTIES LINKER_LANGUAGE CXX)