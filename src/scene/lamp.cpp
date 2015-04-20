#include <glm/gtx/transform.hpp>
#include "lamp.hpp"

Lamp::Lamp():
    Camera(),
    color_(1.0,1.0,1.0,1.0)
{
}

Lamp::Lamp(glm::vec3 position, float rot_y, float rot_loc_x, glm::vec4 color):
    Camera(),
    color_(color)
{
    transformation_=glm::translate(position)*glm::rotate(rot_y,glm::vec3(0.0,1.0,0.0))*glm::rotate(rot_loc_x,glm::vec3(1.0,0.0,0.0));
}


void Lamp::display()
{

}
