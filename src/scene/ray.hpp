#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

class ray
{
public:
	ray();
	ray(glm::vec3 origin, glm::vec3 direction);
	~ray();
private:
	glm::vec3 origin_;
	glm::vec3 direction_;

};

#endif