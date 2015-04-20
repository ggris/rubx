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
    cubes_.push_back(new SmallCube(this, -1, -1, -1));
    cubes_.push_back(new SmallCube(this, -1, -1,  1));
    cubes_.push_back(new SmallCube(this, -1,  1, -1));
    cubes_.push_back(new SmallCube(this, -1,  1,  1));
    cubes_.push_back(new SmallCube(this,  1, -1, -1));
    cubes_.push_back(new SmallCube(this,  1, -1,  1));
    cubes_.push_back(new SmallCube(this,  1,  1, -1));
    cubes_.push_back(new SmallCube(this,  1,  1,  1));
    
    transformation_ = glm::translate(glm::vec3(0.0f, 0.0f, -5.0f));
    srand (time(NULL));
    
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

void RubixCube::display(){
    
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
    SmallCube::ANIMATION_LENGTH = speed;
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

void RubixCube::rotate(glm::vec2 direction, unsigned int id, float speed){
    SmallCube * selectedCube;
    for (unsigned int i =0; i<cubes_.size(); i++){
        if (cubes_[i]->getMesh()->getId()==id)
            selectedCube=cubes_[i];
    }
    
    glm::vec2 x(getTransformation()*glm::vec4(1,0,0,1));
    glm::vec2 y(getTransformation()*glm::vec4(0,1,0,1));
    glm::vec2 z(getTransformation()*glm::vec4(0,0,1,1));
    
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
    
    int axis;
    int dir;
    switch(imax){
        case 0:
            axis=0;
            dir=1;
            break;
        case 1:
            axis=1;
            dir=1;
            break;
        case 2:
            axis=2;
            dir=1;
            break;
        case 3:
            axis=0;
            dir=-1;
            break;
        case 4:
            axis=1;
            dir=-1;
            break;
        case 5:
            axis=2;
            dir=-1;
            break;
        default :
            axis=0;
            dir=1;
            break;
            
    }
    int crown = selectedCube->transform_[3][axis];
    rotate(axis, crown, dir, speed);
}

