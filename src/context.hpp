#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "util/include_gl.hpp"

class Context;

#include "mesh_cube.hpp"
#include "camera.hpp"

class Context
{
    public:
        Context();
        ~Context();

        void run();

    private:
        GLFWwindow *m_window;
        MeshCube *m_cube;
        Camera camera_;

        void initGL();
        void update();
};

#endif
