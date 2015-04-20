#include "mesh_generator.hpp"
#include "sc_3d.hpp"
#include "vao.hpp"

unsigned int MeshGenerator::uniqueObjectId = 0;

ScMesh * MeshGenerator::testCube(Sc3dNode * parent, Sc3d * scene)
{
    std::vector<float> points = {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f
    };

    std::vector<float> normals = {
        -0.6f, -0.6f, -0.6f, 0.0f,
        0.6f, -0.6f, -0.6f, 0.0f,
        0.6f, 0.6f, -0.6f, 0.0f,
        -0.6f, 0.6f, -0.6f, 0.0f,
        -0.6f, -0.6f, 0.6f, 0.0f,
        0.6f, -0.6f, 0.6f, 0.0f,
        0.6f, 0.6f, 0.6f, 0.0f,
        -0.6f, 0.6f, 0.6f, 0.0f
    };

    std::vector<unsigned short> index = {
        0, 3, 2,
        0, 2, 1,
        0, 1, 5,
        0, 5, 4,
        1, 2, 6,
        1, 6, 5,
        2, 3, 7,
        2, 7, 6,
        3, 0, 4,
        3, 4, 7,
        4, 5, 6,
        4, 6, 7,
    };

    std::vector<float> tex_coord = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f

    };

//	glm::vec3 bb_max = { 1.0f, 1.0f, 1.0f };
//	glm::vec3 bb_min = { 0.0f, 0.0f, 0.0f };

	uniqueObjectId++;

    return new ScMesh(scene, new VAO(points, normals, tex_coord, index), scene->getTexture("testCube"), uniqueObjectId, parent);

}

ScMesh * MeshGenerator::rubixSmallCube(Sc3dNode * parent,Sc3d * scene)
{
    std::vector<float> points = {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
    };

    std::vector<float> normals = {
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f
    };

    std::vector<unsigned short> index = {
        0, 3, 2,
        0, 2, 1,
        4, 5, 6,
        4, 6, 7,

        8, 9, 10,
        8, 10, 11,
        12, 15, 14,
        12, 14, 13,

        16, 17, 18,
        16, 18, 19,
        20, 23, 22,
        20, 22, 21

    };

//    std::vector<float> tex_coord = { //whole texture repeated over every face
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f,
//
//        0.0f, 0.0f,
//        1.0f, 0.0f,
//        1.0f, 1.0f,
//        0.0f, 1.0f
//    };

    std::vector<float> tex_coord = { //.33 x .33 square for each face

        0.0f, 0.0f,
        0.33f, 0.0f,
        0.33f, 0.33f,
        0.0f, 0.33f,

        0.33f, 0.0f,
        0.67f, 0.0f,
        0.67f, 0.33f,
        0.33f, 0.33f,

        0.67f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.33f,
        0.67f, 0.33f,

        0.0f, 0.33f,
        0.33f, 0.33f,
        0.33f, 0.67f,
        0.0f, 0.67f,

        0.33f, 0.33f,
        0.67f, 0.33f,
        0.67f,0.67f,
        0.33f, 0.67f,

        0.67f, 0.33f,
        1.0f, 0.33f,
        1.0f, 0.67f,
        0.67f, 0.67f,
    };

//	glm::vec3 bb_max = { 1.0f, 1.0f, 1.0f };
//	glm::vec3 bb_min = { 0.0f, 0.0f, 0.0f };

	uniqueObjectId++;

    //return new ScMesh(scene, new VAO(points, normals, tex_coord, index), scene->getTexture("rubixSmallCube"), uniqueObjectId, parent);
    return new ScMesh(scene, new VAO("data/mesh/cube.obj"), scene->getTexture("default"), uniqueObjectId, parent);

}

ScMesh * MeshGenerator::tableSurface(Sc3dNode* parent,Sc3d * scene)
{
    std::vector<float> points = {
        0.0f, -0.6f, 0.0f,
        5.0f, -0.6f, 0.0f,
        5.0f, -0.6f, -5.0f,
        0.0f, -0.6f, -5.0f
    };
    std::vector<float> normals = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    std::vector<unsigned short> index = {
        0, 1, 2,
        0, 2, 3
    };
    std::vector<float> tex_coord = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    uniqueObjectId++;

    return new ScMesh(scene, new VAO(points, normals, tex_coord, index), scene->getTexture("tableSurface"), uniqueObjectId, parent);
}

