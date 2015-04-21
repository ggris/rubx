#include "event_handler.hpp"

#include "camera.hpp"
#include "rubix_cube.hpp"

bool EventHandler::leftButtonPressed = false;
bool EventHandler::rightButtonPressed = false;
UI* EventHandler::m_ui;
GLFWwindow* EventHandler::m_window;
Sc3d* EventHandler::m_objectStack;

int EventHandler::selectedId_;
glm::vec2 EventHandler::pressPos = { 0, 0 };
glm::vec2 EventHandler::releasePos = { 0, 0 };
glm::vec2 EventHandler::lastMousePos = { 0, 0 };

void EventHandler::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;

	//Quit
	if (m_ui->getState() == UI_MENU && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (action == GLFW_PRESS || (key == GLFW_KEY_BACKSPACE && action == GLFW_REPEAT))
	{
		m_ui->receiveKeyPress(key, action);
		if (m_ui->getQuit())
			glfwSetWindowShouldClose(window, GL_TRUE); //Quit
	}
}

void EventHandler::mouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	double mouse_xpos, mouse_ypos;
	glfwGetCursorPos(m_window, &mouse_xpos, &mouse_ypos);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	mouse_ypos = height - mouse_ypos;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //Left button press
	{
		leftButtonPressed = true;
		colorBasedObjectDetection(mouse_xpos, mouse_ypos);
		pressPos = glm::vec2(mouse_xpos, mouse_ypos);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) //Left button release
	{
		leftButtonPressed = false;
		releasePos = glm::vec2(mouse_xpos, mouse_ypos);

		if (selectedId_ != 0x00ffffff && !m_ui->getGame()->getIsWon())
			m_ui->receiveLeftMouseDrag(glm::normalize(releasePos-pressPos), selectedId_);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) //Right button down
	{
		rightButtonPressed = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		rightButtonPressed = true;
	}
}

void EventHandler::mouseMovement_Callback(GLFWwindow* window, double x, double y)
{
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	y = height - y;

	glm::vec2 newMousePos(x, y);

	m_ui->receiveRightMouseDrag(glm::normalize(newMousePos-lastMousePos));

	lastMousePos = newMousePos;
}

void EventHandler::setUI(UI* ui) { m_ui = ui; }
void EventHandler::setWindow(GLFWwindow* window) { m_window = window; }
void EventHandler::setObjectStack(Sc3d* sc3d) { m_objectStack = sc3d; }

void EventHandler::colorBasedObjectDetection(double mouseX, double mouseY)
{
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
	glReadPixels(mouseX, mouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);

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

	selectedId_ = pickedID;

	glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
