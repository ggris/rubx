#include "event_handler.hpp"

bool EventHandler::buttonPressed = false;
UI* EventHandler::m_ui;

void EventHandler::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		m_ui->receiveKeyPress(GLFW_KEY_A);

	//Quit
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void EventHandler::mouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	//Left mouse button click
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		buttonPressed = true;
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		buttonPressed = false;

	//test get cursor pos
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
}

void EventHandler::setUI(UI* ui)
{
	m_ui = ui;
}
