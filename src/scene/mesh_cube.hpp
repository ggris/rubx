#ifndef MESH_CUBE_HPP
#define MESH_CUBE_HPP

#include <vector>

#include "include_gl.hpp"
#include "scene_graph.hpp"
#include "camera.hpp"

class MeshCube : public ScNode
{
    public:
        MeshCube(Camera * camera);
        void display();

    private:
        GLuint program_;
        GLuint vao_;
        Camera * camera_;

};

#endif
