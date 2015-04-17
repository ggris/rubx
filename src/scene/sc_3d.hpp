#ifndef SC_3D_HPP
#define SC_3D_HPP

#include "include_gl.hpp"

#include "scene_graph.hpp"

#include "camera.hpp"

class Sc3d : public ScVector
{
    public:
        Sc3d(GLFWwindow * window);

        Camera * getCameraPointer();
        void display();

    private:
        GLFWwindow * window_;
        Camera camera_;
};

#endif //SC3D_HPP
