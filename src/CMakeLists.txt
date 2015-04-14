add_subdirectory(util)
add_subdirectory(glProgram)

add_executable(rubx
    main.cpp
    context.cpp
    mesh_cube.cpp
    )

target_link_libraries(rubx
    glfw
    ${GLFW_LIBRARIES}
    rubx_util
    )

set_target_properties( rubx
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

