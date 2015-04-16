#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "util/include_gl.hpp"

class Context;

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
        MeshCube *m_cube;
		UI *m_ui;
        Camera camera_;

		//a enlever
		GLuint m_program;
		//

        void initGL();
        void update();
};

#endif
