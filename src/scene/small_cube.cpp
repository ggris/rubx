#include "small_cube.hpp"
#include "logger.hpp"
#include "glm/ext.hpp"
#include "mesh_generator.hpp"
#include <math.h>
#include "glm/gtx/transform.hpp"
#define PI 3.14159265


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
    initial_transform_=transform_;
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

void scaleTranslation (glm::mat4 & mat, float factor){
    mat[3][0]*=factor;
    mat[3][1]*=factor;
    mat[3][2]*=factor;
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

        transformation_ =  transform_;
        transformation_ = transformation_;
    }
    scaleTranslation(transformation_,2.0f);
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

glm::ivec4 SmallCube::getNormal (int selectedFace){
    glm::vec4 normal;
    switch (selectedFace){
        case 0:
            normal = glm::ivec4(1, 0, 0, 0);
            break;
        case 1:
            normal = glm::ivec4(0, 1, 0, 0);
            break;
        case 2:
            normal = glm::ivec4(0, 0, 1, 0);
            break;
        case 3:
            normal = glm::ivec4(-1, 0, 0, 0);
            break;
        case 4:
            normal = glm::ivec4(0, -1, 0, 0);
            break;
        case 5:
            normal = glm::ivec4(0, 0, -1, 0);
            break;
        default:
            break;
    }
    return (transform_)*normal;
}
void SmallCube::resetTransform(){
    transform_=initial_transform_;
}
