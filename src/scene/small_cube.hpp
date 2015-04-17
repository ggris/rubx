#ifndef BIG_CUBE_HPP
#define BIG_CUBE_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_integer.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sc_3d_node.hpp"
#include "sc_mesh.hpp"

class SmallCube : public Sc3dNode
{
    public :
        SmallCube(Sc3dNode * parent, int x, int y, int z);


        void display();
        void rotate (glm::imat4 rotation);

        glm::imat4 transform_;

    private:
        ScMesh * mesh_;

};

#endif
