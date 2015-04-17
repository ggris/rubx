#include "mesh_generator.hpp"

ScMesh * MeshGenerator::testCube(Sc3d * sc3d)
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

    return new ScMesh(sc3d->getCameraPointer(), points, normals, points, index);

}

ScMesh * MeshGenerator::rubixSmallCube(Sc3d * sc3d)
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

    return new ScMesh(sc3d->getCameraPointer(), points, normals, points, index);

}