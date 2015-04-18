#include "ray.hpp"


ray::ray()
{

}

ray::ray(glm::vec3 origin, glm::vec3 direction)
{
	origin_ = origin;
	direction_ = direction;
}

ray::~ray()
{

}
