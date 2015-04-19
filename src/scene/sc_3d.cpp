#include "sc_mesh.hpp"
#include "mesh_generator.hpp"
#include "rubix_cube.hpp"
#include "lamp.hpp"
#include <iostream>

Sc3d::Sc3d(GLFWwindow * window) :
    window_(window)
{
    camera_= new Camera(80.0f, 1.0f, 0.1f, 10.0f);
    camera_->setScene(this);
    addLamp(glm::vec4(1.1,1.1,1.1,0.0));
    addLamp(glm::vec4(0.1,1.1,1.1,1.0));
    addLamp(glm::vec4(1.1,0.1,1.1,0.0));
    //    push_back(MeshGenerator::rubixSmallCube(&camera_));
    RubixCube * rubii =  new RubixCube(camera_);
    push_back(rubii);
}

void Sc3d::display()
{
    int width, height;

    glfwGetFramebufferSize(window_, &width, &height);
    camera_->set_ratio(width / (float) height);

    ScVector::display();
}

Camera Sc3d::getCamera()
{
    return *camera_;
}

std::vector <Lamp *> Sc3d::getLamps()
{
    return lamps_;
}

void Sc3d::addLamp(Lamp * lamp)
{
    if(lamps_.size()<=20){ // Dirty hack to accomodate GLSL fixed-length arrays
        lamps_.push_back(lamp);
    }
    else {
        std::cout<<"Sc3d : too many lamps, lamp not added"<<std::endl;
    }
}

void Sc3d::addLamp(glm::vec4 light)
{
    addLamp(new Lamp(light));
}

void Sc3d::addLamp(glm::vec4 light, glm::vec4 color)
{
    addLamp(new Lamp(light,color));
}
