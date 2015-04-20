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
    vao_(vao),
	texture_(texture),
	id_(id)
{
//    transformation_ = translate (transformation_, glm::vec3(-0.5f, -0.5f, -0.5f));

    // Creating programs

    Program program;

    program.emplace_back("pos.vert", GL_VERTEX_SHADER);
    //program.emplace_back("smooth.frag", GL_FRAGMENT_SHADER);
    //program.emplace_back("texture.frag", GL_FRAGMENT_SHADER);
    program.emplace_back("ggx.frag", GL_FRAGMENT_SHADER);

    program.link();

    program.clearShaders();

    program_ = program.getProgram();

	//picking program
	Program pickingProgram;

	pickingProgram.emplace_back("picking.vert", GL_VERTEX_SHADER);
	pickingProgram.emplace_back("picking.frag", GL_FRAGMENT_SHADER);

	pickingProgram.link();

	pickingProgram.clearShaders();

	pickingProgram_ = pickingProgram.getProgram();

}

void ScMesh::display()
{
    glUseProgram(program_);

    // Get program uniforms

    GLuint projectionMatrixUnif = glGetUniformLocation(program_, "projection_matrix");
    GLuint transformationMatrixUnif = glGetUniformLocation(program_,"transformation_matrix");
    GLuint textureSamplerUniform = glGetUniformLocation(program_,"texture_Sampler");

    // Get camera projection matrix

    glm::mat4 projection = getScene()->getCamera().getProjectionMat();

    // Get transformation matrix

    glm::mat4 transformation = glm::inverse(getScene()->getCamera().getTransformation())*getTransformation();

    // Define uniform values
    glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));
    texture_->bindToSampler(textureSamplerUniform);

    //set Lamps
    setLamps();

    vao_->bindAndDraw();

    glUseProgram(0);
}

void ScMesh::setLamps()
{

    std::vector<Lamp*> lamps = getScene()->getLamps();
    //set number of lamps
    GLuint nblamps = glGetUniformLocation(program_, "numLamps");
    glUniform1i(nblamps,lamps.size());

    //set lamp array
    for (unsigned int i=0;i<lamps.size();i++){

        std::ostringstream sstransformation,sscolor;
        sstransformation << "allLamps[" << i << "].transformation";
        sscolor << "allLamps[" << i << "].color";
        std::string transformationUnifName = sstransformation.str();
        std::string colorUnifName = sscolor.str();

        GLuint transformUniform = glGetUniformLocation(program_,transformationUnifName.c_str());
        GLuint colorUniform = glGetUniformLocation(program_,colorUnifName.c_str());

        glUniformMatrix4fv(transformUniform, 1, GL_FALSE, glm::value_ptr(lamps[i]->getTransformation()));
        glUniform4f(colorUniform,lamps[i]->getColor().x,lamps[i]->getColor().y,lamps[i]->getColor().z,lamps[i]->getColor().w);

    }


}

void ScMesh::displayWithPickingColour(glm::vec3 colour)
{
	glUseProgram(pickingProgram_);

	// Get program uniforms

	GLuint u_colour = glGetUniformLocation(pickingProgram_, "colour");
	GLuint projectionMatrixUnif = glGetUniformLocation(pickingProgram_, "projection_matrix");
	GLuint transformationMatrixUnif = glGetUniformLocation(pickingProgram_, "transformation_matrix");

	// Get camera projection matrix

    glm::mat4 projection = getScene()->getCamera().getProjectionMat();

    // Get transformation matrix

    glm::mat4 transformation = glm::inverse(getScene()->getCamera().getTransformation())*getTransformation();


	// Define uniform values

	glUniform4f(u_colour, colour.x/255.0f, colour.y/255.0f, colour.z/255.0f, 1.0f);
	glUniformMatrix4fv(projectionMatrixUnif, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(transformationMatrixUnif, 1, GL_FALSE, glm::value_ptr(transformation));

    vao_->bindAndDraw();

	glUseProgram(0);
}

unsigned int ScMesh::getId() const
{
	return id_;
}




