cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

set(lcf_headers 
    lcf/Database.h
    lcf/LCFType.h
    lcf/Item.h
    lcf/Character.h
    lcf/CommonEvent.h
    lcf/EventCommand.h
    lcf/MapInfo.h
    lcf/MapTree.h
    lcf/EventPage.h
    lcf/Event.h
    lcf/Map.h)
set(lcf_source 
    lcf/Database.cpp
    lcf/LCFType.cpp
    lcf/Item.cpp
    lcf/Character.cpp
    lcf/CommonEvent.cpp
    lcf/EventCommand.cpp
    lcf/MapInfo.cpp
    lcf/MapTree.cpp
    lcf/EventPage.cpp
    lcf/Event.cpp
    lcf/Map.cpp)

set(serializer_headers 
    lcf_serializers/Serializer.h
    lcf_serializers/DatabaseSerializer.h
    lcf_serializers/LCFTypeSerializer.h
    lcf_serializers/ItemSerializer.h 
    lcf_serializers/CharacterSerializer.h 
    lcf_serializers/CommonEventSerializer.h
    lcf_serializers/EventCommandSerializer.h
    lcf_serializers/MapInfoSerializer.h
    lcf_serializers/MapTreeSerializer.h
    lcf_serializers/EventSerializer.h
    lcf_serializers/EventPageSerializer.h
    lcf_serializers/MapSerializer.h)
set(serializer_source
    lcf_serializers/DatabaseSerializer.cpp
    lcf_serializers/LCFTypeSerializer.cpp
    lcf_serializers/ItemSerializer.cpp
    lcf_serializers/CharacterSerializer.cpp
    lcf_serializers/CommonEventSerializer.cpp
    lcf_serializers/EventCommandSerializer.cpp
    lcf_serializers/MapInfoSerializer.cpp
    lcf_serializers/MapTreeSerializer.cpp
    lcf_serializers/EventSerializer.cpp
    lcf_serializers/EventPageSerializer.cpp
    lcf_serializers/MapSerializer.cpp)

set(utility_headers utilities/RPGHelper.h)
set(utility_source utilities/RPGHelper.cpp)

set(core_headers MemorySizes.h RPGMaker.h VarMapping.h)


project(core VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Core files for the other tools of the project")


add_library(core 
    ${lcf_headers} ${lcf_source}
    ${serializer_headers} ${serializer_source}
    ${utility_headers} ${utility_source}
    ${core_headers})

target_include_directories(core PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(core PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(core PRIVATE tinyxml2)

target_compile_features(core PUBLIC cxx_std_17)