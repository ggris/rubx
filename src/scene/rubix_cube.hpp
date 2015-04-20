#ifndef RUBIX_CUBE_HPP
#define RUBIX_CUBE_HPP

#include <vector>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include <glm/gtx/transform.hpp>

#include "include_gl.hpp"
#include "sc_3d_node.hpp"
#include "small_cube.hpp"

class RubixCube : public Sc3dNode
{
    public :
        RubixCube(Sc3dNode * parent);
        bool isWon();
        void rotate (int axis, int crown, int direct, float speed);
        //axis = 0 pour x, 1 pour y, 2 pour z
        //direct = +1 ou -1
        //crown = +1 ou -1

        void randomRotate();
        void shuffle(int number);
    
        std::string test_string();

        void display();

		std::vector <SmallCube *> getCubes() const;

    private :

        std::vector <SmallCube *> cubes_;
    
        bool is_shuffling_;
        int shuffle_number_;
        int shuffle_length_;
        float shuffle_start_;

};

#endif
