cmake_minimum_required(VERSION 2.8)
project(Rubx)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -o2 -g -std=c++11")
    message("Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -o2 -g -std=c++11")
    message("gcc")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("VS C++")
endif()

add_subdirectory(lib/glfw-3.1.1)
include_directories(lib/glfw-3.1.1/include)

add_subdirectory(src)

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/bin")
file(INSTALL "shaders" DESTINATION "${CMAKE_BINARY_DIR}/bin")
