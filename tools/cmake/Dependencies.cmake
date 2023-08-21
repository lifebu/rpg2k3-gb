function(add_cmake_graphviz_target)
    set(OUTPUT_DIR ${CMAKE_BINARY_DIR})
    set(DEPENDENCY_DIR ${CMAKE_BINARY_DIR}/dep)

    if(NOT EXISTS ${DEPENDENCY_DIR})
        make_directory(${DEPENDENCY_DIR})
    endif()

    add_custom_target(
        run_graphviz
        COMMAND cmake .. --graphviz=dep.dot
        COMMAND dot -Tpng dep.dot -o ${OUTPUT_DIR}/dependencies.png
        WORKING_DIRECTORY ${DEPENDENCY_DIR})
endfunction()