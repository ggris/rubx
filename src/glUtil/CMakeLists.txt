set(INC
    ../
    )

set(SRC
    shader.hpp
    shader.cpp
    program.hpp
    program.cpp

    texture.hpp
    texture.cpp
    shadowmap.hpp
    shadowmap.cpp
    vao.hpp
    vao.cpp

    scoreLoader.hpp
    scoreLoader.cpp
    )

add_library(rubx_glUtil ${SRC})

include_directories(${INC})

target_link_libraries(rubx_glUtil
    glfw
    ${GLFW_LIBRARIES}
    ${GLEW}
    )
