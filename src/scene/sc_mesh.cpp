#include <string>
#include <cstring>
#include <cmath>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"
#include "logger.hpp"
#include "program.hpp"
#include "lamp.hpp"
#include "camera.hpp"
#include "sc_3d.hpp"

#include "sc_mesh.hpp"

ScMesh::ScMesh(Sc3d * scene,
                const std::string & vao_name,
				const std::string & program_name,
				const std::string & texture_name,
                const std::string & normal_map_name,
                const std::string & bump_map_name,
                Sc3dNode * parent) :
    Sc3dNode( parent, scene ),
    vao_( scene->getVAO( vao_name ) ),
    program_( scene->getProgram( program_name ) ),
    texture_( scene->getTexture( texture_name ) ),
    normal_map_( scene->getTexture( normal_map_name ) ),
    pickingProgram_( scene->getProgram( "picking" ) ),
	id_(scene->getNextId())
{

}

void ScMesh::display()
{
    Sc3dNode::display();
    program_->use();

    // Get program uniforms

    GLuint projectionMatrixUnif = program_->getUniformLocation( "projection_matrix" );
    GLuint transformationMatrixUnif = program_->getUniformLocation( "transformation_matrix" );
    GLuint textureSamplerUniform = program_->getUniformLocation( "texture_Sampler" );
    GLuint normalMapSamplerUniform = program_->getUniformLocation( "normalmap_Sampler" );
    GLuint bumpMapSamplerUniform = program_->getUniformLocation( "bumpmap_Sampler" );
    // Get camera projection matrix

    glm::mat4 projection = getScene()->getCamera()->getProjectionMat();

    // Get transformation matrix

    glm::mat4 transformation = glm::inverse(getScene()->getCamera()->getTransformation())*getTransformation();

    // Define uniform values
    glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));

    texture_->bindToSampler(textureSamplerUniform);
    normal_map_->bindToSampler(normalMapSamplerUniform, 1);
    normal_map_->bindToSampler(bumpMapSamplerUniform, 2);
    //set Lamps
    setLamps();

    vao_->bindAndDraw(program_->get_mode());

    glUseProgram(0);
}

void ScMesh::setLamps()
{

    std::vector<Lamp*> lamps = scene_->getLamps();
    glm::mat4 camera_transf = glm::inverse(scene_->getCamera()->getTransformation());
    //set number of lamps
    GLuint nblamps = program_->getUniformLocation( "numLamps" );
    glUniform1i(nblamps,lamps.size());

    //set lamp array
    for (unsigned int i=0; i<lamps.size(); i++)
    {

        std::ostringstream sstransformation,sscolor;
        sstransformation << "allLamps[" << i << "].transformation";
        sscolor << "allLamps[" << i << "].color";
        std::string transformationUnifName = sstransformation.str();
        std::string colorUnifName = sscolor.str();

        GLuint transformUniform = program_->getUniformLocation( transformationUnifName );
        GLuint colorUniform = program_->getUniformLocation( colorUnifName );

        glUniformMatrix4fv(transformUniform, 1, GL_FALSE, glm::value_ptr(camera_transf*lamps[i]->getTransformation()));
        glUniform4f(colorUniform,lamps[i]->getColor().x,lamps[i]->getColor().y,lamps[i]->getColor().z,lamps[i]->getColor().w);

    }


}

void ScMesh::displayWithPickingColour(glm::vec3 colour)
{
    pickingProgram_->use();

    // Get program uniforms

    GLuint u_colour = pickingProgram_->getUniformLocation( "colour" );
    GLuint projectionMatrixUnif = pickingProgram_->getUniformLocation( "projection_matrix" );
    GLuint transformationMatrixUnif = pickingProgram_->getUniformLocation( "transformation_matrix" );

    // Get camera projection matrix

    glm::mat4 projection = getScene()->getCamera()->getProjectionMat();

    // Get transformation matrix

    glm::mat4 transformation = glm::inverse(getScene()->getCamera()->getTransformation())*getTransformation();


    // Define uniform values

    glUniform4ui(u_colour, colour.x, colour.y, colour.z, 0);
    glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));

    vao_->bindAndDraw(GL_TRIANGLES);

    glUseProgram(0);
}

unsigned int ScMesh::getId() const
{
    return id_;
}

void ScMesh::display(DisplayMode display_mode)
{
    switch (display_mode)
    {
    case RENDER_IMAGE: //rendering image from the camera
    {
        // Get appropriate program
        program_->use();
        // Get program uniforms

        GLuint projectionMatrixUnif = program_->getUniformLocation( "projection_matrix");
        GLuint transformationMatrixUnif = program_->getUniformLocation("transformation_matrix");
        GLuint textureSamplerUniform = program_->getUniformLocation( "texture_Sampler" );

        // Get camera projection matrix

        glm::mat4 projection = scene_->getCamera()->getProjectionMat();

        // Get transformation matrix

        glm::mat4 transformation = glm::inverse(scene_->getCamera()->getTransformation())*getTransformation();

        // Define uniform values
        glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));
        texture_->bindToSampler(textureSamplerUniform);

        //set Lamps
        setLamps();

        vao_->bindAndDraw(program_->get_mode());

        glUseProgram(0);
        break;
    }

    case PICKING: //rendering object ID for mouse interaction
    {
        // Get picking program
        pickingProgram_->use();

        //computing object color from ID

		glm::uvec3 colour(0);

		colour.x = (id_ & 0x000000FF) >> 0;
		colour.y = (id_ & 0x0000FF00) >> 8;
		colour.z = (id_ & 0x00FF0000) >> 16;

        // Get program uniforms

        GLuint u_colour = pickingProgram_->getUniformLocation( "colour" );
        GLuint projectionMatrixUnif = pickingProgram_->getUniformLocation( "projection_matrix" );
        GLuint transformationMatrixUnif = pickingProgram_->getUniformLocation( "transformation_matrix" );

        // Get camera projection matrix

        glm::mat4 projection = scene_->getCamera()->getProjectionMat();

        // Get transformation matrix

        glm::mat4 transformation = glm::inverse(scene_->getCamera()->getTransformation())*getTransformation();


        // Define uniform values

        glUniform4ui(u_colour, colour.x, colour.y, colour.z, 0);
        glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));

        vao_->bindAndDraw(pickingProgram_->get_mode());

        glUseProgram(0);

        break;
    }

    case SHADOWMAP: //rendering shadowmaps from lamps
    {
        //getting program
        shadowmap_program_->use();
        //getting lamps
        std::vector<Lamp*> lamps = scene_->getLamps();
        //render shadowmaps for all lamps
        for(unsigned int i=0; i<lamps.size(); i++)
        {
            //creating framebuffer to store texture
            GLuint framebuffer_name = 0;
            glGenFramebuffers(1, &framebuffer_name);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_name);

            //get shadowmap texture corresponding to lamp
            GLuint depth_texture = scene_->getTexture("shadow_map"+i)->getTexture();

            glBindTexture(GL_TEXTURE_2D, depth_texture);
            glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_texture, 0);

            glDrawBuffer(GL_NONE); // No color buffer is drawn to.

            // Always check that our framebuffer is ok
            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
                LOG_ERROR<<"Computing shadowmap lamp number "<<i<<" : framebuffer error";
            }

            //get program uniforms
            GLuint projectionMatrixUnif = shadowmap_program_->getUniformLocation( "projection_matrix" );
            GLuint transformationMatrixUnif = shadowmap_program_->getUniformLocation( "transformation_matrix" );

            // Get lamp projection matrix

            glm::mat4 projection = lamps[i]->getProjectionMat();

            // Get transformation matrix

            glm::mat4 transformation = glm::inverse(lamps[i]->getTransformation())*getTransformation();

            // Define uniform values
            glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));

            //drawing scene
            vao_->bindAndDraw(shadowmap_program_->get_mode());
        }


        glUseProgram(0);
        break;
    }
    default:
        break;
    }



}



