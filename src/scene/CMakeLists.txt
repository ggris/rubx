set(INC
    ../
    ../util/
    ../glUtil/
    )

set(SRC
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

    ui.hpp
    ui.cpp
    )

add_library(rubx_scene ${SRC})

include_directories(${INC})

target_link_libraries(rubx_scene
    glfw
    ${GLFW_LIBRARIES}
    ${GLEW}
    rubx_glUtil
    )
