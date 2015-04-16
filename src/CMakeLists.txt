add_subdirectory(glProgram)

set(INC
    ../
    )

set(SRC
    main.hpp
    main.cpp

    context.hpp
    context.cpp

    scene_graph.hpp
    scene_graph.cpp
    camera.hpp
    camera.cpp
    mesh_cube.hpp
    mesh_cube.cpp

    rubix_cube.hpp
    rubix_cube.cpp
    small_cube.hpp
    small_cube.cpp

    eventHandler.hpp
    eventHandler.cpp

    ui.hpp
    ui.cpp
    )


add_executable(rubx ${SRC})

include_directories(${INC})

target_link_libraries(rubx
    glfw
    ${GLFW_LIBRARIES}
    rubx_glProgram
    ${GLEW}
    )

set_target_properties( rubx
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

