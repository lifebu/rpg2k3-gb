cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

set(lcf_headers lcf/Switch.h)
set(lcf_source lcf/Switch.cpp)

set(serializer_headers lcf_serializers/SwitchSerializer.h)
set(serializer_source lcf_serializers/SwitchSerializer.cpp)

set(utility_headers utilities/RPGHelper.h)

set(core_headers MemorySizes.h RPGMaker.h VarMapping.h)


project(core VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Core files for the other tools of the project")


add_library(core 
    ${lcf_headers} ${serializer_headers} ${utility_headers} ${core_headers}
    ${lcf_source} ${serializer_source})

target_include_directories(core PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
include_directories(${CMAKE_SOURCE_DIR})

target_link_libraries(core PRIVATE tinyxml2)

target_compile_features(core PUBLIC cxx_std_17)