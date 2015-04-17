#include "rubix_cube.hpp"
#include <glm/gtx/transform.hpp>

using namespace std;

RubixCube::RubixCube()
{
    cubes_=vector<SmallCube>();
    cubes_.push_back(SmallCube(-1, -1, -1 ));
    cubes_.push_back(SmallCube(-1, -1, 1 ));
    cubes_.push_back(SmallCube(-1, 1, -1 ));
    cubes_.push_back(SmallCube(-1, 1, 1 ));
    cubes_.push_back(SmallCube(1, -1, -1 ));
    cubes_.push_back(SmallCube(1, -1, 1 ));
    cubes_.push_back(SmallCube(1, 1, -1 ));
    cubes_.push_back(SmallCube(1, 1, 1 ));
    
}


bool RubixCube::isWon()
{
    bool ans=true;
    
    return ans;
}

void RubixCube::display(){
    
    for(unsigned int i=0;i<cubes_.size();i++){
        cubes_[i].display();
    }
}

void RubixCube::rotate (int axis, int crown, int direct)
{
    glm::ivec3 axis_vector= {0,0,0};
    axis_vector[axis]=direct;
    glm::imat4 rotation;
    
    switch (axis){
        case 0:
            rotation={
                1,  0,  0,  0,
                0,  0,  1,  0,
                0,  -1, 0,  0,
                0,  0,  0,  1
            };
            break;
        case 1:
            rotation={
                0,  0, -1,  0,
                0,  1,  0,  0,
                1,  0,  0,  0,
                0,  0,  0,  1
            };
            break;
        case 2:
            rotation={
                0,  1,  0,  0,
                -1, 0,  0,  0,
                0,  0,  1,  0,
                0,  0,  0,  1
            };
            break;
        default:
            break;
    }
    for (unsigned int i=0; i<cubes_.size();i++)
    {
        if (cubes_[i].transform_[3][axis]==crown)
        {
            cubes_[i].rotate(rotation);
        }
    }
}