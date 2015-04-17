#include <glm/gtx/transform.hpp>

#include "logger.hpp"
#include "rubix_cube.hpp"

using namespace std;

RubixCube::RubixCube(Sc3dNode * parent) :
    Sc3dNode(parent)
{
    cubes_.push_back(new SmallCube(this, -1, -1, -1));
    cubes_.push_back(new SmallCube(this, -1, -1,  1));
    cubes_.push_back(new SmallCube(this, -1,  1, -1));
    cubes_.push_back(new SmallCube(this, -1,  1,  1));
    cubes_.push_back(new SmallCube(this,  1, -1, -1));
    cubes_.push_back(new SmallCube(this,  1, -1,  1));
    cubes_.push_back(new SmallCube(this,  1,  1, -1));
    cubes_.push_back(new SmallCube(this,  1,  1,  1));

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

    for(unsigned int i=0;i<cubes_.size();i++){
        cubes_[i]->display();
    }
}

void RubixCube::rotate (int axis, int crown, int direct)
{

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

std::string RubixCube::test_string(){
    return glm::to_string(cubes_[0]->transform_);

}



