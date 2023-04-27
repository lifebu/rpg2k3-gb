cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(rapidxml)

add_library(rapidxml rapidxml.hpp rapidxml_utils.hpp rapidxml_print.hpp rapidxml_iterators.hpp rapidxml_ext.hpp)

# to add include directory when building.
target_include_directories(rapidxml PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_compile_features(rapidxml INTERFACE cxx_std_11)
set_target_properties(rapidxml PROPERTIES LINKER_LANGUAGE CXX)