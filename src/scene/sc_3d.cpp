#include <iostream>
#include <stdexcept>

#include "mesh_generator.hpp"
#include "rubix_cube.hpp"

#include "lamp.hpp"
#include "camera.hpp"
#include "sc_3d.hpp"

Sc3d::Sc3d(GLFWwindow * window) :
    window_(window)
{
    initTextures();
    initPrograms();
    initVAOs();
    camera_= new Camera(1.0f, 1.0f, 0.1f, 30.0f);
    camera_->setScene(this);
    addLamp(glm::vec3(0.0,10.0,10.0),10.0,10.0,glm::vec4(1.0,1.0,1.0,1.0));
    addLamp(glm::vec3(20.0,1.0,5.0),10.0,10.0,glm::vec4(1.0,0.7,0.5,1.0));
    addLamp(glm::vec3(-20.0,1.0,5.0),10.0,10.0,glm::vec4(0.5,0.5,1.0,1.0));

    rubix_cube_ =  new RubixCube(nullptr,this);
    push_back(rubix_cube_);
    push_back(MeshGenerator::tableSurface(nullptr,this));
}

void Sc3d::initTextures()
{
    textures_.insert( {"default", new Texture("data/img/default.bmp")} );
    textures_.insert( {"small_cube", new Texture("data/img/small_cube.bmp")} );
}

void Sc3d::initPrograms()
{
    programs_.insert( {"lighting", new Program(GL_PATCHES, "lighting")} );
}

void Sc3d::initVAOs()
{
}

void Sc3d::display()
{
    int width, height;

    glfwGetFramebufferSize(window_, &width, &height);
    camera_->set_ratio(width / (float) height);

    ScVector::display();
}

Camera * Sc3d::getCamera()
{
    return camera_;
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

void Sc3d::addLamp()
{
    addLamp(new Lamp());
}

void Sc3d::addLamp(glm::vec3 position,float rot_y,float rot_loc_x,glm::vec4 color)
{
    addLamp(new Lamp( position,rot_y,rot_loc_x,color));
}

Texture * Sc3d::getTexture(std::string objectID){
    try{
        return textures_.at(objectID);
    }
    catch(std::out_of_range e){ //if ID unknow, return default texture
        return textures_.at("default");
    }
}
