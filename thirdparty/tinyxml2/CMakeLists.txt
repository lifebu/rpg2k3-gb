project(tinyxml2)


### files
set(tinyxml2_headers src/tinyxml2/tinyxml2.h)
set(tinyxml2_sources src/tinyxml2/tinyxml2.cpp)

add_library(tinyxml2 ${tinyxml2_headers} ${tinyxml2_sources})

target_include_directories(tinyxml2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


### features
set_target_properties(tinyxml2 PROPERTIES LINKER_LANGUAGE CXX)