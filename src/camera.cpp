#include "camera.hpp"

Camera::Camera(float fov, float ratio, float z_near, float z_far) :
    m_fov(fov),
    m_ratio(ratio),
    m_z_near(z_near),
    m_z_far(z_far),
    m_rot_z(0),
    m_rot_loc_x(0),
    m_position()
{
}
