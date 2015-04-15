#ifndef MESH_CUBE_HPP
#define MESH_CUBE_HPP

#include <vector>

class MeshCube;

#include "util/include_gl.hpp"

class MeshCube
{
    public:
        MeshCube();
        void display(float time);
    private:
        GLuint m_program;
        GLuint m_vao;
};

#endif
