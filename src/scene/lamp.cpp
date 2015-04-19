#include "lamp.hpp"

Lamp::Lamp():
    light_(1.0,1.0,1.0,0.0),
    color_(1.0,1.0,1.0,1.0)
{
}

Lamp::Lamp(glm::vec4 light,glm::vec4 color):
    light_(light),
    color_(color)
{
}

Lamp::Lamp(glm::vec3 light, sourceType source, glm::vec4 color):
    light_(setLight(light,source)),
    color_(color)
{
}

glm::vec4 Lamp::setLight(glm::vec3 light, sourceType source){
    if (source==DIRECTIONAL) return glm::vec4(light,0.0);
    return glm::vec4(light,1.0);
}


void Lamp::display(){}
