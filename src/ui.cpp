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
	float points[] = { 
		-1.0f,-1.0f, 
		 1.0f,-1.0f, 
		-1.0f, 1.0f, 
		-1.0f, 1.0f, 
		 1.0f,-1.0f, 
		 1.0f, 1.0f };

	GLuint vp_vbo, vao; 
	glGenBuffers(1, &vp_vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao); 
	glBindVertexArray(vao); // note: vertex buffer is already bound 
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL); 
	glEnableVertexAttribArray (0);

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
	if (test)
	{
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrthof(0, 1240, 0, 480, -5, 1);

		glUseProgram(m_program);

		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glUseProgram(0);
	}
}

void UI::receiveKeyPress(int key)
{
	if (test)
		test = false;
	else
		test = true;
}


