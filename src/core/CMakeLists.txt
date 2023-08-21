project(core VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Core files for the other tools of the project")

set(lcf_headers
    lcf/event/EventCommand.h
    lcf/event/EventCommandFactory.h
    lcf/event/EventCommandFactoryDef.h
    lcf/database/Character.h
    lcf/database/CommonEvent.h
    lcf/database/Item.h
    lcf/database/LCFType.h
    lcf/map/Event.h
    lcf/map/EventPage.h
    lcf/map_tree/MapInfo.h
    lcf/Database.h
    lcf/Map.h
    lcf/MapTree.h)

set(lcf_source 
    lcf/event/EventCommand.cpp
    lcf/event/EventCommandFactory.cpp
    lcf/database/Character.cpp
    lcf/database/CommonEvent.cpp
    lcf/database/Item.cpp
    lcf/database/LCFType.cpp
    lcf/map/Event.cpp
    lcf/map/EventPage.cpp
    lcf/map_tree/MapInfo.cpp
    lcf/Database.cpp
    lcf/Map.cpp
    lcf/MapTree.cpp)

set(emu_headers
    emu_interface/RPGEntryPoint.h
    emu_interface/RPGMakerInterface.h)

set(serializer_headers
    lcf_serializers/EventCommandSerializer.h
    lcf_serializers/EventCommandSerializerRAPID.h
    lcf_serializers/CommonEventSerializer.h
    lcf_serializers/DatabaseSerializer.h
    lcf_serializers/MapSerializer.h
    lcf_serializers/MapSerializerRAPID.h
    lcf_serializers/MapTreeSerializer.h
    lcf_serializers/Templates.h)

set(serializer_source
    lcf_serializers/EventCommandSerializer.cpp
    lcf_serializers/EventCommandSerializerRAPID.cpp
    lcf_serializers/CommonEventSerializer.cpp
    lcf_serializers/DatabaseSerializer.cpp
    lcf_serializers/MapSerializer.cpp
    lcf_serializers/MapSerializerRAPID.cpp
    lcf_serializers/MapTreeSerializer.cpp)

set(structure_headers
    structure/Logger.h
    structure/Singleton.h
    structure/StateMachine.h)

set(structure_source
    structure/Logger.cpp)

set(utility_headers utilities/RPGHelper.h)
set(utility_source utilities/RPGHelper.cpp)

set(def_headers 
    def/MemorySizes.h 
    def/RPGMaker.h 
    def/VarMapping.h)


add_library(core 
    ${lcf_headers} ${lcf_source}
    ${emu_headers}
    ${structure_headers} ${structure_source}
    ${serializer_headers} ${serializer_source}
    ${utility_headers} ${utility_source}
    ${def_headers})

target_include_directories(core PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(core PRIVATE 
        ${PROJECT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR})

include(CMakePrintHelpers)
cmake_print_variables(PROJECT_SOURCE_DIR) 


# third party
target_link_libraries(core PRIVATE tinyxml2)
target_link_libraries(core PRIVATE rapidxml)

target_compile_features(core PUBLIC cxx_std_17)