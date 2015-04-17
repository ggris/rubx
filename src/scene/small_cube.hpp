#ifndef BIG_CUBE_HPP
#define BIG_CUBE_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/matrix_transform.hpp>
class SmallCube
{

public :
    //contructors
	SmallCube();
	
    SmallCube (int x, int y, int z);
    
    
	void display();
    void rotate (glm::imat4 rotation);

    glm::imat4 transform_;
private :
	
};

#endif
