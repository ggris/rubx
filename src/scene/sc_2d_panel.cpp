#include "sc_2d_panel.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"
#include "texture.hpp"

Sc2dPanel::Sc2dPanel(){}

Sc2dPanel::Sc2dPanel(glm::vec2 position, glm::vec2 scale, std::string textureFile, std::vector<float> tex_coord)
{
	position_ = position;
	scale_ = scale;

	float points[] = { 
			-1.0f,-1.0f,
			 1.0f,-1.0f,
			-1.0f, 1.0f,
			-1.0f, 1.0f,
			 1.0f,-1.0f,
			 1.0f, 1.0f };

	std::vector<unsigned short> index = {
		0, 3, 2,
		0, 2, 1 };

	GLuint vp_vbo; 
	glGenBuffers(1, &vp_vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint index_buffer_object;
	glGenBuffers(1, &index_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned short), index.data(), GL_STATIC_DRAW);

	GLuint UVcoords_buffer_object;
	glGenBuffers(1, &UVcoords_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, UVcoords_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, tex_coord.size() * sizeof(float), tex_coord.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL); 
	glEnableVertexAttribArray (0);

	glBindBuffer(GL_ARRAY_BUFFER, UVcoords_buffer_object);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);

	glBindVertexArray(0);

	//Creating program
	Program program;

	program.emplace_back("panel.vert", GL_VERTEX_SHADER);
	program.emplace_back("panel.frag", GL_FRAGMENT_SHADER);

	program.link();

	program.clearShaders();

	program_ = program.getProgram();

	//Creating texture
	Texture texture(textureFile);
	texture_ = texture.getTexture();
}

void Sc2dPanel::display()
{
	glUseProgram(program_);

	GLuint textureSamplerUniform = glGetUniformLocation(program_, "texture_Sampler");
	GLuint u_scale = glGetUniformLocation(program_, "panel_scale");
	GLuint u_position = glGetUniformLocation(program_, "panel_position");

	glUniform2f(u_scale, scale_.x, scale_.y);
	glUniform2f(u_position, position_.x, position_.y);
	Texture::bindTextureToSampler(texture_, textureSamplerUniform);

	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glUseProgram(0);
}