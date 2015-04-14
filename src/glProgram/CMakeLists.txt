set(INC
    ../
    )

set(SRC
    shader.hpp
    shader.cpp
    )

add_library(rubx_glProgram ${SRC})

include_directories(${INC})

target_link_libraries(rubx_glProgram
    utils
    glfw
    ${GLFW_LIBRARIES}
    )
