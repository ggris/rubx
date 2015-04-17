#ifndef SC_MESH_HPP
#define SC_MESH_HPP

#include <vector>

#include "include_gl.hpp"
#include "sc_3d_node.hpp"
#include "camera.hpp"
#include "texture.hpp"

class ScMesh : public Sc3dNode
{
    public:
        ScMesh(Sc3dNode * parent,
                const std::vector<float> &points,
                const std::vector<float> &normals,
                const std::vector<float> &tex_coord,
                const std::vector<unsigned short> &index);
        void display();

    private:
        GLuint program_;
        GLuint vao_;
        GLuint texture_;

};

#endif
