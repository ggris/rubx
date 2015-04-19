add_subdirectory(glUtil)
add_subdirectory(scene)

set(INC
    util/
    glUtil/
    scene/
    )

set(SRC
    main.hpp
    main.cpp

    context.hpp
    context.cpp
    event_handler.hpp
    event_handler.cpp
	game.hpp
	game.cpp

    )


add_executable(rubx ${SRC})

include_directories(${INC})

target_link_libraries(rubx
    glfw
    ${GLFW_LIBRARIES}
    ${GLEW}
    rubx_glUtil
    rubx_scene
    )

set_target_properties( rubx
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
