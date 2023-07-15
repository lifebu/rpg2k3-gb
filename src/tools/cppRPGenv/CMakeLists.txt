cmake_minimum_required(VERSION 3.16...3.22)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22)
endif()

project(cppRPGEnv VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Runtime Environment similar to RPG Maker 2003")

set(cppRPGEnv_headers
    interface_impl/RPGMakerImpl.h
    manager/InputManager.h manager/LCFManager.h manager/RenderManager.h
    system/SystemCore.h
    manager/renderer/TextBox.h
    manager/renderer/ChoiceBox.h
    manager/renderer/InputBox.h
    manager/structure/ManagerInterface.h)

set(cppRPGEnv_source
    interface_impl/RPGMakerImpl.cpp
    manager/InputManager.cpp manager/LCFManager.cpp manager/RenderManager.cpp
    system/SystemCore.cpp
    manager/renderer/TextBox.cpp
    manager/renderer/ChoiceBox.cpp
    manager/renderer/InputBox.cpp)

add_executable(cppRPGEnv cppRPGenv.cpp ${cppRPGEnv_source} ${cppRPGEnv_headers})

target_include_directories(cppRPGEnv PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")
target_include_directories(cppRPGEnv PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(cppRPGEnv PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(cppRPGEnv PRIVATE core)
target_link_libraries(cppRPGEnv PRIVATE emu)

# third party
target_link_libraries(cppRPGEnv PRIVATE sfml-system)
target_link_libraries(cppRPGEnv PRIVATE sfml-window)
target_link_libraries(cppRPGEnv PRIVATE sfml-graphics)


target_compile_features(cppRPGEnv PUBLIC cxx_std_17)