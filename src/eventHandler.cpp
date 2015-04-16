#include "eventHandler.hpp"

bool EventHandler::buttonPressed = false;

void EventHandler::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	//test mods
	if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_A)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void EventHandler::MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
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