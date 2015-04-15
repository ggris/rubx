#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
    public:
        Camera(float fov, float ratio, float z_near, float z_far);

    private:
        float m_fov;
        float m_ratio;
        float m_z_near;
        float m_z_far;

        float m_rot_z;
        float m_rot_loc_x;
        glm::vec3 m_position;
        
        glm::mat4 m_projection;
};

#endif


