#ifndef MESH_GENERATOR_HPP
#define MESH_GENERATOR_HPP

#include "sc_mesh.hpp"
#include "sc_3d.hpp"

class MeshGenerator
{
    public:
        static ScMesh * testCube(Sc3d * sc3d);
        static ScMesh * rubixSmallCube(Sc3d * sc3d);

};

#endif


