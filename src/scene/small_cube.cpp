#include "small_cube.hpp"
#include "logger.hpp"
#include "glm/ext.hpp"
#include "mesh_generator.hpp"

SmallCube::SmallCube (Sc3dNode * parent, int x, int y, int z) :
    Sc3dNode(parent),
    mesh_(MeshGenerator::rubixSmallCube(this))
{
    transform_=
    {
        1,  0,  0,  0,
        0,  1,  0,  0,
        0,  0,  1,  0,
        x,  y,  z,  1
    };
    transformation_ = transform_;
}

void SmallCube::display()
{
    mesh_->display();
}

void SmallCube::rotate(glm::imat4 rotation)
{
    transform_= rotation*transform_;
    transformation_ = transform_;
    LOG_DEBUG << glm::to_string(transform_);
    LOG_DEBUG << glm::to_string(transformation_);
}

ScMesh * SmallCube::getMesh() const
{
	return mesh_;
}