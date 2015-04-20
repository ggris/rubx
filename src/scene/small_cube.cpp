#include "small_cube.hpp"
#include "logger.hpp"
#include "glm/ext.hpp"
#include "mesh_generator.hpp"
#include <math.h>
#include "glm/gtx/transform.hpp"
#define PI 3.14159265

float SmallCube::ANIMATION_LENGTH=5.0f;

SmallCube::SmallCube (Sc3dNode * parent, int x, int y, int z) :
    Sc3dNode(parent),
    mesh_(MeshGenerator::rubixSmallCube(this,this->scene_))
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

glm::mat4 computeRotation(int axis, int direct, float t){
    glm::mat4 rotation;
    float angle =direct*PI*t/2;
    switch (axis){
        case 0:
            rotation=glm::rotate(angle,glm::vec3(1.0f,0.0f,0.0f));
            break;
        case 1:
            rotation=glm::rotate(angle,glm::vec3(0.0f,1.0f,0.0f));
            break;
        case 2:
            rotation=glm::rotate(angle,glm::vec3(0.0f,0.0f,1.0f));
            break;
        default :
            break;
    }
    return rotation;
}

glm::imat4 computeIntRotation(int axis, int direct){
    glm::imat4 rotation;
    switch (axis){
        case 0:
            rotation={
                1,  0,  0,  0,
                0,  0,  direct,  0,
                0,  -direct, 0,  0,
                0,  0,  0,  1
            };
            break;
        case 1:
            rotation={
                0,  0, -direct,  0,
                0,  1,  0,  0,
                direct,  0,  0,  0,
                0,  0,  0,  1
            };
            break;
        case 2:
            rotation={
                0,  direct,  0,  0,
                -direct, 0,  0,  0,
                0,  0,  1,  0,
                0,  0,  0,  1
            };
            break;
        default:
            break;
    }
    return rotation;
}

void SmallCube::display()
{
    
    float t = (glfwGetTime()-animation_start_)/animation_length_;
    
    if(is_animate_ && t>1){
        is_animate_=false;
    }
    if (is_animate_){
        transformation_ =  computeRotation(axis_rotation_,direct_rotation_,t) * last_transform_;
    }
    else {
        transformation_ = transform_;
    }
    
    mesh_->display();
}

ScMesh * SmallCube::getMesh() const
{
    return mesh_;
}
    
void SmallCube::rotate(int axis, int direct, float speed){
    last_transform_ = transform_;
    
    transform_=computeIntRotation(axis,direct) * transform_;
    
    is_animate_= true;
    animation_start_=glfwGetTime();
    animation_length_=speed;
    axis_rotation_=axis;
    direct_rotation_=direct;
}
