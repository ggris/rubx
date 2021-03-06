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
    public :
        SmallCube(Sc3dNode * parent, int x, int y, int z);


        void display();
        void rotate(int axis, int direct, float speed);
        glm::imat4 transform_;

        ScMesh * getMesh() const;
        glm::ivec4 getNormal(int selectedFace);

        void resetTransform();
    private:
        glm::imat4 initial_transform_;
        ScMesh * mesh_;

        //animation
        float animation_start_;
        float animation_length_;
        bool is_animate_;
        glm::mat4 last_transform_;


        //rotation
        int axis_rotation_;
        int direct_rotation_;
};

#endif
