#include "small_cube.hpp"
#include "logger.hpp"
#include "glm/ext.hpp"
#include "mesh_generator.hpp"

float SmallCube::ANIMATION_LENGTH=5.0f;

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
    is_animate_=false;
}

void SmallCube::display()
{
    float t = (glfwGetTime()-animation_start_)/ANIMATION_LENGTH;

    if(t>1)
        is_animate_=false;

    if (is_animate_){
        transformation_ = t * ((glm::fmat4)transform_) +
            (1-t) * ((glm::fmat4)last_transform_);
    }
    else {
        transformation_=transform_;
    }
    mesh_->display();
}

void SmallCube::rotate(glm::imat4 rotation)
{
    last_transform_=transform_;
    transform_= rotation*transform_;

    is_animate_=true;
    animation_start_=glfwGetTime();
}

ScMesh * SmallCube::getMesh() const
{
    return mesh_;
}
