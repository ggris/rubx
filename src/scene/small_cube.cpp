#include "small_cube.hpp"


SmallCube::SmallCube (int x,int y,int z)

{
    transform_=
    {
        1,  0,  0,  0,
        0,  1,  0,  0,
        0,  0,  1,  0,
        x,  y,  z,  1
    };
}

void SmallCube::display()
{
    
}

void SmallCube::rotate(glm::imat4 rotation)
{
    transform_= rotation*transform_;
}