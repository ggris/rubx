#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

Camera::Camera() :
    fov_(45.0f),
    ratio_(1.0f),
    z_near_(0.1f),
    z_far_(10.0f),
    rot_z_(0.0f),
    rot_loc_x_(0.0f),
    position_(0.0f),            // Zero vector
    mat_project_(glm::perspective(fov_, ratio_, z_near_, z_far_)),
    mat_rotate_(1.0f),          // Identity
    mat_camera_(mat_project_)
{
}

Camera::Camera(float fov, float ratio, float z_near, float z_far) :
    fov_(fov),
    ratio_(ratio),
    z_near_(z_near),
    z_far_(z_far),
    rot_z_(0.0f),
    rot_loc_x_(0.0f),
    position_(0.0f),            // Zero vector
    mat_project_(glm::perspective(fov_, ratio_, z_near_, z_far_)),
    mat_rotate_(1.0f),          // Identity
    mat_camera_(mat_project_)
{
}

void Camera::setPerspective(float fov, float ratio, float z_near, float z_far)
{
    fov_ = fov;
    ratio_ = ratio;
    z_near_ = z_near;
    z_far_ = z_far;
    update_mat_project();
}

void Camera::set_ratio(float ratio)
{
    ratio_ = ratio;
}

const glm::mat4& Camera::get_mat_camera() const
{
    return mat_camera_;
}

void Camera::update_mat_project()
{
    mat_project_ = glm::perspective(fov_, ratio_, z_near_, z_far_);
}

void Camera::update_mat_rotate()
{
    mat_rotate_ = glm::rotate(rot_z_, glm::vec3(0.0f, 0.0f, 1.0f));
    mat_rotate_ = glm::rotate(mat_rotate_, rot_loc_x_, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::update_mat_camera()
{
    mat_camera_ = mat_project_ * mat_rotate_;
}


