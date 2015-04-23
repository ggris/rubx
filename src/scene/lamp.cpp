#include <glm/gtx/transform.hpp>
#include <cmath>

#include "lamp.hpp"

Lamp::Lamp():
    Camera(1.0f, 1.0f, 0.1f, 200.0f),
    color_(1.0,1.0,1.0,1.0)
{
}

Lamp::Lamp(glm::vec3 position, float rot_y, float rot_loc_x, glm::vec4 color):
    Camera(1.0f, 1.0f, 0.1f, 200.0f),
    color_(color)
{
    transformation_=glm::translate(position)*glm::rotate(rot_y,glm::vec3(0.0,1.0,0.0))*glm::rotate(rot_loc_x,glm::vec3(1.0,0.0,0.0));
}

//Construct a lamp pointing at an object
Lamp::Lamp(glm::vec3 lamp_position, glm::vec3 object_position, glm::vec4 color):
    Lamp(lamp_position,
    computeRotY(lamp_position-object_position),
    computeRotLocX(lamp_position-object_position),
    color)
{
}

void Lamp::display()
{

}

float Lamp::computeRotY(glm::vec3 cartesian)
{
    return atan2(cartesian[0],cartesian[2]);
}

float Lamp::computeRotLocX(glm::vec3 cartesian)
{
    return acos(cartesian[1]/glm::length(cartesian));
}

