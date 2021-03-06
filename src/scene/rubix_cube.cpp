#include <glm/gtx/transform.hpp>

#include "logger.hpp"
#include "rubix_cube.hpp"
#include <time.h>
#include <stdlib.h>
#include <glm/glm.hpp>

using namespace std;

RubixCube::RubixCube(Sc3dNode * parent,Sc3d * scene) :
    Sc3dNode(parent,scene)
{
    for(int i=-1;i<=1;i+=1)
        for(int j=-1;j<=1;j+=1)
            for(int k=-1;k<=1;k+=1)
                cubes_.push_back(new SmallCube(this, i, j, k));
    srand (time(NULL));

}

void RubixCube::reset()
{
    for (int i=0; i<cubes_.size();i++)
        cubes_[i]->resetTransform();
}


bool RubixCube::isWon()
{
    bool ans=true;
    glm::imat3 rota = glm::imat3(cubes_[0]->transform_);
    for(unsigned int i = 0; i < cubes_.size(); i++){
        ans=ans && rota == glm::imat3(cubes_[i]->transform_);
    }
    return ans;
}

void RubixCube::display()
{
    Sc3dNode::display();

    if (is_shuffling_){
        if((glfwGetTime() - shuffle_start_)/animation_length_ > 2 *  shuffle_number_){
            shuffle_number_ ++;
            LOG_DEBUG << "Shuffle n° : " << shuffle_number_ << " / " << shuffle_length_;
            randomRotate(animation_length_);
        }
        if(shuffle_number_>=shuffle_length_){
            is_shuffling_=false;
        }
    }


    for(unsigned int i=0;i<cubes_.size();i++){
        cubes_[i]->display();
    }
}

void microShuffle(){

}

void RubixCube::rotate (int axis, int crown, int direct, float speed)
{

    for (unsigned int i=0; i<cubes_.size();i++)
    {
        if (cubes_[i]->transform_[3][axis]==crown)
        {
            cubes_[i]->rotate(axis, direct, speed);

        }
    }
}

std::string RubixCube::test_string()
{
    return glm::to_string(cubes_[0]->transform_);
}

std::vector <SmallCube *> RubixCube::getCubes() const
{
    return cubes_;
}

void RubixCube::randomRotate(float speed){
    int a = rand() % 3;
    int c = (rand() % 2)*2 - 1;
    int d = (rand() % 2)*2 - 1;
    rotate(a,c,d,speed);
}

void RubixCube::shuffle(int number, float speed){
    is_shuffling_=true;
    shuffle_number_= 0;
    shuffle_length_=number;
    shuffle_start_=glfwGetTime();
    animation_length_=speed;
}

int getAxisId(glm::vec3 axis){
    if (axis==glm::vec3(1.0,0.0,0.0))
        return 0;
    if (axis==glm::vec3(0.0,1.0,0.0))
        return 1;
    if (axis==glm::vec3(0.0,0.0,1.0))
        return 2;
    if (axis==glm::vec3(-1.0,0.0,0.0))
        return 0;
    if (axis==glm::vec3(0.0,-1.0,0.0))
        return 1;
    return 2;
}
int getDirId(glm::vec3 axis){
    if (axis==glm::vec3(1.0,0.0,0.0))
        return 1;
    if (axis==glm::vec3(0.0,1.0,0.0))
        return 1;
    if (axis==glm::vec3(0.0,0.0,1.0))
        return 1;
    return -1;
}

void RubixCube::rotate(glm::vec2 direction, unsigned int id, int selectedFace, float speed){
    SmallCube * selectedCube;
    for (unsigned int i =0; i<cubes_.size(); i++){
        if (cubes_[i]->getMesh()->getId()==id)
            selectedCube=cubes_[i];
    }
    glm::ivec4 normal = selectedCube->getNormal(selectedFace);

    //projections espace camera
    glm::vec2 x(getTransformation()*glm::vec4(1,0,0,1));
    glm::vec2 y(getTransformation()*glm::vec4(0,1,0,1));
    glm::vec2 z(getTransformation()*glm::vec4(0,0,1,1));
    glm::vec2 n(getTransformation()*normal);

    //what direction are we going ? store it in the vec3 move
    float scalarProducts [6];
    scalarProducts[0] = glm::dot(direction, x);
    scalarProducts[1] = glm::dot(direction, y);
    scalarProducts[2] = glm::dot(direction, z);
    scalarProducts[3] = glm::dot(direction, -x);
    scalarProducts[4] = glm::dot(direction, -y);
    scalarProducts[5] = glm::dot(direction, -z);
    int imax = 0;
    float pmax = 0.0f;
    for (int i=0; i<6; i++){
        if (scalarProducts[i]>pmax){
            pmax=scalarProducts[i];
            imax=i;
        }
    }
    glm::vec3 move;
    switch(imax){
        case 0:
            move=glm::vec3(1,0,0);
            break;
        case 1:
            move=glm::vec3(0,1,0);
            break;
        case 2:
            move=glm::vec3(0,0,1);
            break;
        case 3:
            move=glm::vec3(-1,0,0);
            break;
        case 4:
            move=glm::vec3(0,-1,0);
            break;
        case 5:
            move=glm::vec3(0,0,-1);
            break;
        default :
            move=glm::vec3(0,0,0);
            break;
    }
    //the axis of the rotation (as a vec3)
    glm::vec3 axis =glm::cross((glm::vec3)normal,move);

    int ax =getAxisId(axis);
    int dir = getDirId(axis);
    int crown = selectedCube->transform_[3][ax];

    //LOG_DEBUG << ax << "  " << dir << "  " << crown;
    rotate(ax,crown,dir,speed);
}

