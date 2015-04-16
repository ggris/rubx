#include <string>
#include <cstring>
#include <cmath>

#include "util/logger.hpp"
#include "UI.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glProgram/program.hpp"

UI::UI()
{
	GLfloat points[] = { 
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f };

	GLuint vbo = 0; 
	glGenBuffers(1, &vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint m_vao = 0; glGenVertexArrays(1, &m_vao); 
	glBindVertexArray(m_vao); glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Creating program
	Program program;

	program.emplace_back("panel.vert", GL_VERTEX_SHADER);
	program.emplace_back("panel.frag", GL_FRAGMENT_SHADER);

	program.link();

	program.clearShaders();

	m_program = program.getProgram();

}

void UI::display()
{
    glUseProgram(m_program);

	glBindVertexArray(m_vao); // draw points 0-3 from the currently bound VAO with current in-use shader glDrawArrays (GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
}



