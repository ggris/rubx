#include <cmath>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "logger.hpp"
#include "camera.hpp"

Camera::Camera() :
    Sc3dNode(),
    fov_(1.0f),
    ratio_(1.0f),
    z_near_(0.1f),
    z_far_(30.0f),
    mat_project_(glm::perspective(fov_, ratio_, z_near_, z_far_)),
    zoom_(10.0f)
{
    updateZoom(1.0f);
}

Camera::Camera(float fov, float ratio, float z_near, float z_far) :
    Sc3dNode(),
    fov_(fov),
    ratio_(ratio),
    z_near_(z_near),
    z_far_(z_far),
    mat_project_(glm::perspective(fov_, ratio_, z_near_, z_far_)),
    zoom_(10.0f)
{
    updateZoom(1.0f);
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
    update_mat_project();
}

void Camera::updateZoom( float f )
{
    zoom_ *= exp(f);

    transformation_ = glm::translate( glm::vec3( 0.0f, 0.0f, zoom_ ) );
}

void Camera::update_mat_project()
{
    mat_project_ = glm::perspective(fov_, ratio_, z_near_, z_far_);
}

glm::mat4 Camera::getProjectionMat() const
{
	return mat_project_;
}
