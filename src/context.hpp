#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "include_gl.hpp"

#include "scene_graph.hpp"

#include "ui.hpp"

class Context
{
    public:
        Context();
        ~Context();

        void run();

    private:
        GLFWwindow * window_;
        ScVector sc_vector_;

        void initGL();
        void initScene();

        void update();
};

#endif
