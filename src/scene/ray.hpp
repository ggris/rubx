#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

class ray
{
public:
	ray();
	~ray();
private:
	glm::vec3 worldPos;
	glm::vec3 direction;


};

#endif