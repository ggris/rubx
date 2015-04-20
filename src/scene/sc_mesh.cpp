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

ScMesh::ScMesh(Sc3dNode * parent,
        Sc3d * scene,
        const std::vector<float> &points,
        const std::vector<float> &normals,
        const std::vector<float> &tex_coord,
        const std::vector<unsigned short> &index,
		unsigned int id,
		Texture * texture) :
    Sc3dNode(parent,scene)
{

    transformation_ = translate (transformation_, glm::vec3(-0.5f, -0.5f, -0.5f));

	id_ = id;

	texture_=texture;

    GLuint points_vbo;
    glGenBuffers (1, &points_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glBufferData (GL_ARRAY_BUFFER, points.size() * sizeof (float), points.data(), GL_STATIC_DRAW);

    GLuint normals_vbo;
    glGenBuffers (1, &normals_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glBufferData (GL_ARRAY_BUFFER, normals.size() * sizeof (float), normals.data(), GL_STATIC_DRAW);

    GLuint index_buffer_object;
    glGenBuffers (1, &index_buffer_object);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof (unsigned short), index.data(), GL_STATIC_DRAW);

    GLuint UVcoords_buffer_object;
    glGenBuffers (1,&UVcoords_buffer_object);
    glBindBuffer (GL_ARRAY_BUFFER,UVcoords_buffer_object);
    glBufferData (GL_ARRAY_BUFFER,tex_coord.size() * sizeof (float),tex_coord.data(), GL_STATIC_DRAW);

    glGenVertexArrays (1, &vao_);
    glBindVertexArray (vao_);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    glEnableVertexAttribArray(2);

    glBindBuffer (GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, normals_vbo);
    glVertexAttribPointer (1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER,UVcoords_buffer_object);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

    glBindVertexArray(0);

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

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);

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

        std::ostringstream sslight,sscolor;
        sslight << "allLamps[" << i << "].light";
        sscolor << "allLamps[" << i << "].color";
        std::string lightUnifName = sslight.str();
        std::string colorUnifName = sscolor.str();

        GLuint lightUniform = glGetUniformLocation(program_,lightUnifName.c_str());
        GLuint colorUniform = glGetUniformLocation(program_,colorUnifName.c_str());

        glUniform4f(lightUniform,lamps[i]->getLight().x,lamps[i]->getLight().y,lamps[i]->getLight().z,lamps[i]->getLight().w);
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

	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, 0);

	glUseProgram(0);
}

unsigned int ScMesh::getId() const
{
	return id_;
}




