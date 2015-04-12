cmake_minimum_required(VERSION 2.8)
project(Rubix)

set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost REQUIRED COMPONENTS log thread system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -o2 -g -std=c++11")

add_subdirectory(lib/glfw-3.1.1)
include_directories(lib/glfw-3.1.1/include)

add_executable(rubix
    src/main.cpp
    src/logger.cpp
    src/context.cpp
    src/mesh_cube.cpp
    )

target_link_libraries(rubix
    ${Boost_LIBRARIES}
    glfw
    ${GLFW_LIBRARIES}
    )

