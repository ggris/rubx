#include "event_handler.hpp"

#include "camera.hpp"
#include "rubix_cube.hpp"

bool EventHandler::buttonPressed = false;
UI* EventHandler::m_ui;
GLFWwindow* EventHandler::m_window;
Sc3d* EventHandler::m_objectStack;

void EventHandler::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	//Quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS || (key== GLFW_KEY_BACKSPACE && action == GLFW_REPEAT))
		m_ui->receiveKeyPress(key);
}

void EventHandler::mouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	//Left mouse button click
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		buttonPressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		buttonPressed = false;
}

void EventHandler::setUI(UI* ui) { m_ui = ui; }
void EventHandler::setWindow(GLFWwindow* window) { m_window = window; }
void EventHandler::setObjectStack(Sc3d* sc3d) { m_objectStack = sc3d; }

void EventHandler::colorBasedObjectDetection()
{
	double mouse_xpos, mouse_ypos;
	glfwGetCursorPos(m_window, &mouse_xpos, &mouse_ypos);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RubixCube* rubixCube = (RubixCube*)m_objectStack[0][0];
	std::vector<SmallCube*> smallCubes = rubixCube->getCubes();

	for (unsigned int i = 0; i < smallCubes.size(); i++)
	{
		unsigned int id = smallCubes[i]->getMesh()->getId();
		glm::vec3 colour(0.0f, 0.0f, 0.0f);

		colour.x = (id & 0x000000FF) >> 0;
		colour.y = (id & 0x0000FF00) >> 8;
		colour.z = (id & 0x00FF0000) >> 16;

		smallCubes[i]->getMesh()->displayWithPickingColour(colour);
	}

	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned char pixelData[4];
	glReadPixels(mouse_xpos, height - mouse_ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);

	int pickedID =
		pixelData[0] +
		pixelData[1] * 256 +
		pixelData[2] * 256 * 256;

	if (pickedID == 0x00ffffff) // Full white, must be the background !
		std::printf("\nbackground");
	else
	{
		std::printf("\nnot background: ");
		std::printf("%d", pickedID);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}