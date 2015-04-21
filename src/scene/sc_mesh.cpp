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
                VAO * vao,
				Texture * texture,
				unsigned int id,
                Sc3dNode * parent) :
    Sc3dNode(parent,scene),
    program_(new Program(GL_PATCHES)),
    pickingProgram_(new Program(GL_TRIANGLES)),
    vao_(vao),
	texture_(texture),
	id_(id)
{
//    transformation_ = translate (transformation_, glm::vec3(-0.5f, -0.5f, -0.5f));

    // Creating programs

    program_->emplace_back("lighting.vs", GL_VERTEX_SHADER);
    program_->emplace_back("lighting.cs", GL_TESS_CONTROL_SHADER);
    program_->emplace_back("lighting.es", GL_TESS_EVALUATION_SHADER);
    program_->emplace_back("lighting.fs", GL_FRAGMENT_SHADER);

    program_->link();

    program_->clearShaders();

	//picking program
	
    pickingProgram_->emplace_back("picking.vert", GL_VERTEX_SHADER);
	pickingProgram_->emplace_back("picking.frag", GL_FRAGMENT_SHADER);

	pickingProgram_->link();

	pickingProgram_->clearShaders();

}

void ScMesh::display()
{
    program_->use();

    // Get program uniforms

    GLuint projectionMatrixUnif = program_->getUniformLocation( "projection_matrix" );
    GLuint transformationMatrixUnif = program_->getUniformLocation( "transformation_matrix" );
    GLuint textureSamplerUniform = program_->getUniformLocation( "texture_Sampler" );

    // Get camera projection matrix

    glm::mat4 projection = getScene()->getCamera()->getProjectionMat();

    // Get transformation matrix

    glm::mat4 transformation = glm::inverse(getScene()->getCamera()->getTransformation())*getTransformation();

    // Define uniform values
    glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));
    texture_->bindToSampler(textureSamplerUniform);

    //set Lamps
    setLamps();

    vao_->bindAndDraw(program_->get_mode());

    glUseProgram(0);
}

void ScMesh::setLamps()
{

    std::vector<Lamp*> lamps = getScene()->getLamps();
    glm::mat4 camera_transf = glm::inverse(getScene()->getCamera()->getTransformation());
    //set number of lamps
    GLuint nblamps = program_->getUniformLocation( "numLamps" );
    glUniform1i(nblamps,lamps.size());

    //set lamp array
    for (unsigned int i=0;i<lamps.size();i++){

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




