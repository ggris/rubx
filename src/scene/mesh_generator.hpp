#ifndef MESH_GENERATOR_HPP
#define MESH_GENERATOR_HPP

#include "sc_mesh.hpp"
#include "sc_3d_node.hpp"

class MeshGenerator
{
    public:
        static ScMesh * testCube(Sc3dNode * parent);
        static ScMesh * rubixSmallCube(Sc3dNode * parent);

};

#endif


