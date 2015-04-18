#ifndef SC_3D_HPP
#define SC_3D_HPP

#include "include_gl.hpp"
#include "glm/glm.hpp"

#include "scene_graph.hpp"

//#include "camera.hpp"

class Camera;

class Sc3d : public ScVector
{
    public:
        Sc3d(GLFWwindow * window);

        void display();

		Camera getCamera();

    private:
        GLFWwindow * window_;
        Camera * camera_;
};

#endif //SC3D_HPP
