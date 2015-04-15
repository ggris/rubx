#ifndef RUBIX_CUBE_HPP
#define RUBIX_CUBE_HPP

#include <vector>
#include "small_cube.hpp"


class rubixCube {

public :
	rubixCube();
	bool isWon();
	void rotate (int axis, int dir); //axis=0 : x ; axis=1 : y ; axis=2 : z ; dir : sens

	std::vector <smallCube> cubes;
};

#endif
