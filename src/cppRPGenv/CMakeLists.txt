project(cppRPGEnv VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "Runtime Environment similar to RPG Maker 2003")

set(cppRPGEnv_headers
    interface_impl/RPGMakerImpl.h
    manager/InputManager.h manager/LCFManager.h manager/RenderManager.h
    system/SystemStateMachine.h
    manager/renderer/RenderDef.h
    manager/renderer/TextBox.h
    manager/renderer/ChoiceBox.h
    manager/renderer/InputBox.h
    manager/renderer/ImGUIRenderer.h
    manager/VariableManager.h)

set(cppRPGEnv_source
    interface_impl/RPGMakerImpl.cpp
    manager/InputManager.cpp manager/LCFManager.cpp manager/RenderManager.cpp
    system/SystemStateMachine.cpp
    manager/renderer/TextBox.cpp
    manager/renderer/ChoiceBox.cpp
    manager/renderer/InputBox.cpp
    manager/renderer/ImGUIRenderer.cpp
    manager/VariableManager.cpp)

add_executable(cppRPGEnv cppRPGenv.cpp ${cppRPGEnv_source} ${cppRPGEnv_headers})

target_include_directories(cppRPGEnv PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/thirdparty)

target_link_libraries(cppRPGEnv PRIVATE core)
target_link_libraries(cppRPGEnv PRIVATE emu)

# third party
target_link_libraries(cppRPGEnv PRIVATE sfml-system)
target_link_libraries(cppRPGEnv PRIVATE sfml-window)
target_link_libraries(cppRPGEnv PRIVATE sfml-graphics)
target_link_libraries(cppRPGEnv PRIVATE ImGui-SFML::ImGui-SFML)

target_compile_features(cppRPGEnv PUBLIC cxx_std_17)