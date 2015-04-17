#ifndef RUBIX_CUBE_HPP
#define RUBIX_CUBE_HPP

#include <vector>
#include "small_cube.hpp"
#include "scene_graph.hpp"
#include "include_gl.hpp"
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include <glm/gtx/transform.hpp>

class RubixCube : public ScNode
{
public :
    static float timer_duration_;
    
public :
	RubixCube();
    bool isWon();
    void rotate (int axis, int crown, int direct);
        //axis = 0 pour x, 1 pour y, 2 pour z
        //direct = +1 ou -1
        //crown = +1 ou -1
    void display(); //TODO
    std::string test_string();
private :
    
    std::vector <SmallCube> cubes_;
    
    
};

#endif
