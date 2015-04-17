#include "sc_3d.hpp"
#include "sc_mesh.hpp"
#include "mesh_generator.hpp"
#include "rubix_cube.hpp"

Sc3d::Sc3d(GLFWwindow * window) :
    window_(window),
    camera_(80.0f, 1.0f, 0.1f, 10.0f)
{
//    push_back(MeshGenerator::rubixSmallCube(&camera_));
    RubixCube * rubii =  new RubixCube(&camera_);
    rubii->rotate(1, 1, 1);
    push_back(rubii);
}

void Sc3d::display()
{
    int width, height;

    glfwGetFramebufferSize(window_, &width, &height);
    camera_.set_ratio(width / (float) height);

    ScVector::display();
}
