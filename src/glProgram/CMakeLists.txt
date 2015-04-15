set(INC
    ../
    )

set(SRC
    shader.hpp
    shader.cpp
    program.hpp
    program.cpp
    )

add_library(rubx_glProgram ${SRC})

include_directories(${INC})

target_link_libraries(rubx_glProgram
    glfw
    ${GLFW_LIBRARIES}
    ${GLEW}
    )
