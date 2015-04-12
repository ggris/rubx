#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Context;

#include "mesh_cube.hpp"

class Context
{
    public:
        Context();
        ~Context();

        void run();

    private:
        GLFWwindow *m_window;
        MeshCube *m_cube;

        void initGL();
        void update();
};

#endif
