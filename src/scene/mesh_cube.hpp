#ifndef MESH_CUBE_HPP
#define MESH_CUBE_HPP

#include <vector>

#include "scene_graph.hpp"
#include "include_gl.hpp"

class MeshCube : public ScNode
{
    public:
        MeshCube();
        void display();
    private:
        GLuint m_program;
        GLuint m_vao;
};

#endif
