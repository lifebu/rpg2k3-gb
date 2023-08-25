project(cppRPGEnv VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Runtime Environment similar to RPG Maker 2003")

### files
set(cppRPGEnv_headers
    cppRPGenv/interface_impl/RPGMakerImpl.h
    cppRPGenv/manager/InputManager.h 
    cppRPGenv/manager/LCFManager.h 
    cppRPGenv/manager/RenderManager.h
    cppRPGenv/system/SystemStateMachine.h
    cppRPGenv/manager/renderer/RenderDef.h
    cppRPGenv/manager/renderer/TextBox.h
    cppRPGenv/manager/renderer/ChoiceBox.h
    cppRPGenv/manager/renderer/InputBox.h
    cppRPGenv/manager/renderer/ImGUIRenderer.h
    cppRPGenv/manager/VariableManager.h)

set(cppRPGEnv_source
    cppRPGenv/interface_impl/RPGMakerImpl.cpp
    cppRPGenv/manager/InputManager.cpp 
    cppRPGenv/manager/LCFManager.cpp 
    cppRPGenv/manager/RenderManager.cpp
    cppRPGenv/system/SystemStateMachine.cpp
    cppRPGenv/manager/renderer/TextBox.cpp
    cppRPGenv/manager/renderer/ChoiceBox.cpp
    cppRPGenv/manager/renderer/InputBox.cpp
    cppRPGenv/manager/renderer/ImGUIRenderer.cpp
    cppRPGenv/manager/VariableManager.cpp)

add_executable(cppRPGEnv cppRPGenv.cpp ${cppRPGEnv_source} ${cppRPGEnv_headers})

target_include_directories(cppRPGEnv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(cppRPGEnv PRIVATE cppRPGenv/pch.h)


### features
target_compile_features(cppRPGEnv PUBLIC cxx_std_17)


### dependencies
target_link_libraries(cppRPGEnv PRIVATE core)
target_link_libraries(cppRPGEnv PRIVATE emu)
# third party
target_link_libraries(cppRPGEnv PRIVATE sfml-system)
target_link_libraries(cppRPGEnv PRIVATE sfml-window)
target_link_libraries(cppRPGEnv PRIVATE sfml-graphics)
target_link_libraries(cppRPGEnv PRIVATE ImGui-SFML::ImGui-SFML)