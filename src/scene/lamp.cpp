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
    Lamp::Lamp(lamp_position, 0.0, 0.0, color)
{
    view_matrix_=glm::lookAt(lamp_position,object_position,glm::vec3(0.0,1.0,0.0));
}

void Lamp::display()
{

}

