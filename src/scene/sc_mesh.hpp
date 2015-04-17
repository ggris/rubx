#ifndef SC_MESH_HPP
#define SC_MESH_HPP

#include <vector>

#include "include_gl.hpp"
#include "scene_graph.hpp"
#include "camera.hpp"

class ScMesh : public ScNode
{
    public:
        ScMesh(Camera * camera,
                const std::vector<float> &points,
                const std::vector<float> &normals,
                const std::vector<float> &tex_coord,
                const std::vector<unsigned short> &index);
        void display();

    private:
        GLuint program_;
        GLuint vao_;
        Camera * camera_;

};

#endif
