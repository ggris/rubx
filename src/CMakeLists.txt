add_subdirectory(glProgram)

set(INC
    ../
    )

set(SRC
    main.hpp
    main.cpp

    context.hpp
    context.cpp

    mesh_cube.hpp
    mesh_cube.cpp
    )


add_executable(rubx ${SRC})

include_directories(${INC})

target_link_libraries(rubx
    glfw
    ${GLFW_LIBRARIES}
    rubx_glProgram
    glew32s
    )

set_target_properties( rubx
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

