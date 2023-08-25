add_subdirectory(tinyxml2)
add_subdirectory(rapidxml)

set(LIBLCF_WITH_XML ON)
set(LIBLCF_ENABLE_TOOLS ON)
set(LIBLCF_ENABLE_TESTS OFF)
add_subdirectory(liblcf)

set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)
add_subdirectory(SFML)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO OFF)
add_subdirectory(imgui-sfml)

#add_subdirectory(EasyRPGPlayer)
#file(COPY "build/EasyRPGPlayer/easyrpg-player" DESTINATION ${CMAKE_SOURCE_DIR})