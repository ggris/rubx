#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "util/include_gl.hpp"

#include "scene_graph.hpp"
#include "mesh_cube.hpp"

#include "ui.hpp"
#include "camera.hpp"

class Context
{
    public:
        Context();
        ~Context();

        void run();

    private:
        GLFWwindow *m_window;
		UI *m_ui;
        Camera camera_;
        ScVector sc_vector_;

        void initGL();
        void update();
};

#endif
