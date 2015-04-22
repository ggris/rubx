set(INC
    ../
    ../util/
    ../glUtil/
    )

set(SRC
    scene_graph.hpp
    scene_graph.cpp

    sc_ui.hpp
    sc_ui.cpp
    sc_3d.hpp
    sc_3d.cpp
    sc_3d_node.hpp
    sc_3d_node.cpp
    sc_mesh.hpp
    sc_mesh.cpp

    camera.hpp
    camera.cpp

    lamp.hpp
    lamp.cpp

    rubix_cube.hpp
    rubix_cube.cpp
    small_cube.hpp
    small_cube.cpp

	sc_2d_panel.hpp
	sc_2d_panel.cpp

	sc_text.hpp
	sc_text.cpp

	game.hpp
	game.cpp
    )

add_library(rubx_scene ${SRC})

include_directories(${INC})

target_link_libraries(rubx_scene
    glfw
    ${GLFW_LIBRARIES}
    ${GLEW}
    rubx_glUtil
    )
