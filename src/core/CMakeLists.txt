project(core VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Core files for the other tools of the project")


### files
set(lcf_headers
    core/lcf/event/EventCommand.h
    core/lcf/event/EventCommandFactory.h
    core/lcf/event/EventCommandFactory.h
    core/lcf/database/Character.h
    core/lcf/database/CommonEvent.h
    core/lcf/database/Item.h
    core/lcf/database/LCFType.h
    core/lcf/map/Event.h
    core/lcf/map/EventPage.h
    core/lcf/map_tree/MapInfo.h
    core/lcf/Database.h
    core/lcf/Map.h
    core/lcf/MapTree.h)

set(lcf_source 
    core/lcf/event/EventCommand.cpp
    core/lcf/event/EventCommandFactory.cpp
    core/lcf/database/Character.cpp
    core/lcf/database/CommonEvent.cpp
    core/lcf/database/Item.cpp
    core/lcf/database/LCFType.cpp
    core/lcf/map/Event.cpp
    core/lcf/map/EventPage.cpp
    core/lcf/map_tree/MapInfo.cpp
    core/lcf/Database.cpp
    core/lcf/Map.cpp
    core/lcf/MapTree.cpp)

set(emu_headers
    core/emu_interface/RPGEntryPoint.h
    core/emu_interface/RPGMakerInterface.h)

set(serializer_headers
    core/lcf_serializers/EventCommandSerializer.h
    core/lcf_serializers/EventCommandSerializerRAPID.h
    core/lcf_serializers/CommonEventSerializer.h
    core/lcf_serializers/DatabaseSerializer.h
    core/lcf_serializers/MapSerializer.h
    core/lcf_serializers/MapSerializerRAPID.h
    core/lcf_serializers/MapTreeSerializer.h
    core/lcf_serializers/Templates.h)

set(serializer_source
    core/lcf_serializers/EventCommandSerializer.cpp
    core/lcf_serializers/EventCommandSerializerRAPID.cpp
    core/lcf_serializers/CommonEventSerializer.cpp
    core/lcf_serializers/DatabaseSerializer.cpp
    core/lcf_serializers/MapSerializer.cpp
    core/lcf_serializers/MapSerializerRAPID.cpp
    core/lcf_serializers/MapTreeSerializer.cpp)

set(structure_headers
    core/structure/Logger.h
    core/structure/ManagerInterface.h
    core/structure/Singleton.h
    core/structure/StateMachine.h)

set(structure_source
    core/structure/Logger.cpp)

set(utility_headers core/utilities/RPGHelper.h)
set(utility_source core/utilities/RPGHelper.cpp)

set(def_headers 
    core/def/MemorySizes.h 
    core/def/RPGMaker.h 
    core/def/VarMapping.h)

add_library(core 
    ${lcf_headers} ${lcf_source}
    ${emu_headers}
    ${structure_headers} ${structure_source}
    ${serializer_headers} ${serializer_source}
    ${utility_headers} ${utility_source}
    ${def_headers})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(core PRIVATE core/pch.h)


### features
target_compile_features(core PUBLIC cxx_std_17)
#target_set_warnings(core ON)


### dependencies
# third party
target_link_libraries(core PRIVATE tinyxml2)
target_link_libraries(core PRIVATE rapidxml)