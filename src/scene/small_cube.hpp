#ifndef BIG_CUBE_HPP
#define BIG_CUBE_HPP

#include <vector>
#include <glm/glm.hpp>

class smallCube {

public :
	smallCube();
	smallCube (int x,int y,int z,int rx,int ry,int rz);

	void display();	
	
	int pos[3];
	int rot[3];
	glm::vec3 fpos;
	glm::vec3 frot;
};

#endif
