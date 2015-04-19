#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include "sc_3d_node.hpp"


class Lamp : public Sc3dNode
{
    public:
        enum sourceType{DIRECTIONAL, PUNCTUAL};
        Lamp();
        Lamp(glm::vec4 light,glm::vec4 color=glm::vec4(1.0,1.0,1.0,1.0));
        Lamp(glm::vec3 light,sourceType source,glm::vec4 color=glm::vec4(1.0,1.0,1.0,1.0));
        glm::vec4 getLight() const { return light_; }
        glm::vec4 getColor() const { return color_; }
        void display();
    private:
        const glm::vec4 light_;
        const glm::vec4 color_;
        glm::vec4 setLight(glm::vec3 light, sourceType source);
};

#endif // LAMP_H
