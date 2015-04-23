#include <iostream>
#include <stdexcept>

#include "rubix_cube.hpp"

#include "lamp.hpp"
#include "camera.hpp"
#include "sc_3d.hpp"



Sc3d::Sc3d(GLFWwindow * window) :
    window_(window),
    next_id_(0)
{
    initTextures();
    initPrograms();
    initVAOs();
    initLamps();

    camera_= new Camera(1.0f, 1.0f, 0.1f, 200.0f);
    camera_->setScene(this);

    rubix_cube_ =  new RubixCube(nullptr,this);
    push_back(rubix_cube_);
//    push_back( new ScMesh( this, "floor", "lighting") );
}

void Sc3d::addTexture(std::string name)
{
    textures_.insert( {name, new Texture( "data/img/" + name + ".bmp" )} );
}

void Sc3d::addProgram(std::string name, GLenum mode)
{
    programs_.insert( {name, new Program( mode, name ) } );
}

void Sc3d::addVAO(std::string name)
{
    vaos_.insert( {name, new VAO( "data/mesh/" + name + ".obj" )} );
}

void Sc3d::addShadowmap(){
    shadowmaps_.push_back(new ShadowMap());
}

void Sc3d::initTextures()
{
    addTexture( "default" );
    addTexture( "small_cube" );
    addTexture ("smoothcube2");
    addTexture("normalmap");
}

void Sc3d::initPrograms()
{
    addProgram( "lighting", GL_PATCHES );
    addProgram( "picking" );

    programs_.insert( {"default", programs_.at( "lighting" )} );
}

void Sc3d::initVAOs()
{
    addVAO( "cube" );
    addVAO( "floor" );

    vaos_.insert( {"default", vaos_.at( "cube" )} );
}

void Sc3d::initLamps()
{
    addLamp(glm::vec3(0.0,20.0,20.0),10.0,10.0,glm::vec4(1.0,1.0,1.0,1.0));
    addLamp(glm::vec3(20.0,1.0,10.0),10.0,10.0,glm::vec4(1.0,0.7,0.5,1.0));
    addLamp(glm::vec3(-20.0,1.0,10.0),10.0,10.0,glm::vec4(0.5,0.5,1.0,1.0));
    addLamp(glm::vec3(-2.0,1.0,40.0),10.0,10.0,glm::vec4(1.0,1.0,1.0,1.0));
    //addLamp(glm::vec3(-5.0,-20.0,-10.0),10.0,10.0,glm::vec4(0.3,0.3,0.3,1.0));
}

void Sc3d::display()
{
    int width, height;

    glfwGetFramebufferSize(window_, &width, &height);
    camera_->set_ratio(width / (float) height);

    //computing shadowmaps
    ScVector::display(SHADOWMAP);

    //rendenring scene
    ScVector::display();
}

Camera * Sc3d::getCamera()
{
    return camera_;
}

ShadowMap * Sc3d::getShadowmap(int i){
    return shadowmaps_[i];
}

std::vector <Lamp *> Sc3d::getLamps()
{
    return lamps_;
}

void Sc3d::addLamp(Lamp * lamp)
{
    if(lamps_.size()<=20){ // Dirty hack to accomodate GLSL fixed-length arrays
        lamps_.push_back(lamp);
        addShadowmap();
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

Texture * Sc3d::getTexture( std::string name ) const
{
    try{
        return textures_.at( name );
    }
    catch(std::out_of_range e){ //if ID unknow, return default texture
        return textures_.at( "default" );
    }
}

Program * Sc3d::getProgram( std::string name ) const
{
    try{
        return programs_.at( name );
    }
    catch(std::out_of_range e){ //if ID unknow, return default program
        return programs_.at( "default" );
    }
}

VAO * Sc3d::getVAO( std::string name ) const
{
    try{
        return vaos_.at( name );
    }
    catch(std::out_of_range e){ //if ID unknow, return default texture
        return vaos_.at( "default" );
    }
}
