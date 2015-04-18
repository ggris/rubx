#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "sc_3d_node.hpp"

class Camera : public Sc3dNode
{
    public:
        Camera();
        Camera(float fov, float ratio, float z_near, float z_far);

        void setPerspective(float fov, float ratio, float z_near, float z_far);
        void set_ratio(float ratio);

        const glm::mat4 & getTransformation() const;

		glm::mat4 getProjectionMat() const;
		glm::mat4 getViewMat() const;

        void display();

    private:
        float fov_;
        float ratio_;
        float z_near_;
        float z_far_;

        float rot_z_;
        float rot_loc_x_;
        glm::vec3 position_;

        glm::mat4 mat_project_;     // Projection matrix
        glm::mat4 mat_rotate_;
        glm::mat4 mat_camera_;         // Projection matrix translated for the camera

        void update_mat_project();
        void update_mat_rotate();
        void update_mat_camera();

};

#endif


