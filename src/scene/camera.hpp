#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "sc_3d_node.hpp"

class Camera : public Sc3dNode
{
    public:
        Camera();
        ~Camera(){}
        Camera(float fov, float ratio, float z_near, float z_far);

        void setPerspective(float fov, float ratio, float z_near, float z_far);
        void set_ratio(float ratio);

		glm::mat4 getProjectionMat() const;

        void display(){}

    private:
        float fov_;
        float ratio_;
        float z_near_;
        float z_far_;

        glm::mat4 mat_project_;     // Projection matrix

        void update_mat_project();

};

#endif


