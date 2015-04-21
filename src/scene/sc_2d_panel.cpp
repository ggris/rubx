#include "sc_2d_panel.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"
#include "texture.hpp"

Sc2dPanel::Sc2dPanel(){}

Sc2dPanel::Sc2dPanel(glm::vec2 position, glm::vec2 scale, std::string textureFile, std::vector<float> tex_coords)
{
	position_ = position;
	scale_ = scale;

	tex_coords_ = tex_coords;

	points_ = { 
			-1.0f,-1.0f,
			 1.0f,-1.0f,
			-1.0f, 1.0f,
			-1.0f, 1.0f,
			 1.0f,-1.0f,
			 1.0f, 1.0f };

	glGenBuffers(1, &vbo_); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(float), points_.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &tex_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo_);
	glBufferData(GL_ARRAY_BUFFER, tex_coords_.size() * sizeof(float), tex_coords_.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL); 
	glEnableVertexAttribArray (0);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo_);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//Creating program
	Program program;

	program.emplace_back("panel.vert", GL_VERTEX_SHADER);
	program.emplace_back("panel.frag", GL_FRAGMENT_SHADER);

	program.link();

	program.clearShaders();

	program_ = program.get_program();

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
	glDrawArrays(GL_TRIANGLES, 0, points_.size()/2);

	glUseProgram(0);
}

void Sc2dPanel::update(std::vector<float> points, std::vector<float> tex_coord)
{
	points_ = points;
	tex_coords_ = tex_coord;

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(float), points_.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo_);
	glBufferData(GL_ARRAY_BUFFER, tex_coords_.size() * sizeof(float), tex_coords_.data(), GL_DYNAMIC_DRAW);

}

std::vector<float> Sc2dPanel::getPoints() const
{
	return points_;
}

std::vector<float> Sc2dPanel::getTexCoords() const
{
	return tex_coords_;
}

void Sc2dPanel::updatePosition(glm::vec2 position)
{
	position_ = position;
}
