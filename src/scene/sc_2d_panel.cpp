#include <string>
#include <cstring>
#include <cmath>

#include "logger.hpp"
#include "sc_ui.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"

UI::UI()
{
	float points[] = { 
			-1.0f,-1.0f,
			 1.0f,-1.0f,
			-1.0f, 1.0f,
			-1.0f, 1.0f,
			 1.0f,-1.0f,
			 1.0f, 1.0f };

	GLuint vp_vbo; 
	glGenBuffers(1, &vp_vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, vp_vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
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
	glUseProgram(m_program);

	//temp colour to test ui flow
	GLuint u_colour = glGetUniformLocation(m_program, "colour");

	switch (ui_state)
	{
		case UI_START:
			glUniform4f(u_colour, 0.5f, 0.5f, 0.5f, 1.0f);
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;
		case UI_SCORE:
			glUniform4f(u_colour, 1.0f, 1.0f, 1.0f, 1.0f);
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			break;
		case UI_GAME:
			break;
	}

	glUseProgram(0);
}

void UI::receiveKeyPress(int key)
{
	if (key == GLFW_KEY_S)
	{
		switch (ui_state)
		{
		case UI_START:
			ui_state = UI_SCORE;
			break;
		case UI_SCORE:
			ui_state = UI_START;
			break;
		}
	}
	else if (key == GLFW_KEY_P && ui_state == UI_START)
		ui_state = UI_GAME;
	else if (key == GLFW_KEY_Q && ui_state == UI_GAME)
		ui_state = UI_START;
}


