#include <glm/gtx/transform.hpp>

#include "logger.hpp"
#include "rubix_cube.hpp"
#include <time.h>
#include <stdlib.h>

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
        if((glfwGetTime() - shuffle_start_)/animation_length_ > shuffle_number_){
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
    for (unsigned int i=0; i<cubes_.size();i++)
    {
        if (cubes_[i]->transform_[3][axis]==crown)
        {
            cubes_[i]->rotate(rotation);
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

