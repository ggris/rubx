#include "lamp.hpp"

Lamp::Lamp(glm::vec4 color):
    light_(1.0,1.0,1.0,0.0),
    color_(1.0,1.0,1.0,1.0)
{
}

Lamp::Lamp(glm::vec4 posDir,glm::vec4 color):
    light_(posDir),
    color_(color)
{
}

Lamp::Lamp(glm::vec3 posDir, sourceType source, glm::vec4 color):
    light_(setLight(posDir,source)),
    color_(color)
{
}

glm::vec4 Lamp::setLight(glm::vec3 posDir, sourceType source){
    if (source==DIRECTIONAL) return glm::vec4(posDir,0.0);
    return glm::vec4(posDir,1.0);
}


void Lamp::display(){}
