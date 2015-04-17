#include "event_handler.hpp"

bool EventHandler::buttonPressed = false;
UI* EventHandler::m_ui;
GLFWwindow* EventHandler::m_window;

void EventHandler::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	//Quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS)
		m_ui->receiveKeyPress(key);
}

void EventHandler::mouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	//Left mouse button click
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		buttonPressed = true;

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		buttonPressed = false;
}

void EventHandler::setUI(UI* ui) { m_ui = ui; }
void EventHandler::setWindow(GLFWwindow* window) { m_window = window; }
