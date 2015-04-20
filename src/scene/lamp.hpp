#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include "camera.hpp"


class Lamp : public Camera
{
    public:
        Lamp();
        Lamp(glm::vec3 position, float rot_y, float rot_loc_x,glm::vec4 color = glm::vec4(1.0,1.0,1.0,1.0));
        void display();
        glm::vec4 getColor()const {return color_;}
    private:
        const glm::vec4 color_;
};

#endif // LAMP_H
