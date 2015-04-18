#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include "sc_3d_node.hpp"


class Lamp : public Sc3dNode
{
    public:
        enum sourceType{DIRECTIONAL, PUNCTUAL};
        Lamp(glm::vec4 color=glm::vec4(1.0,1.0,1.0,1.0));
        Lamp(glm::vec4 posDir,glm::vec4 color=glm::vec4(1.0,1.0,1.0,1.0));
        Lamp(glm::vec3 posDir,sourceType source,glm::vec4 color=glm::vec4(1.0,1.0,1.0,1.0));
        glm::vec4 getLight_() const { return light_; }
        void display();
    private:
        const glm::vec4 light_;
        const glm::vec4 color_;
        glm::vec4 setLight(glm::vec3 posDir, sourceType source);
};

#endif // LAMP_H