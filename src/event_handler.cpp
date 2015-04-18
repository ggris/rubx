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
	else if (action == GLFW_PRESS)
		m_ui->receiveKeyPress(key);
}

void EventHandler::mouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	//Left mouse button click
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		buttonPressed = true;

		detectObjectUnderClick();
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		buttonPressed = false;
}

void EventHandler::setUI(UI* ui) { m_ui = ui; }
void EventHandler::setWindow(GLFWwindow* window) { m_window = window; }
void EventHandler::setObjectStack(Sc3d* sc3d) { m_objectStack = sc3d; }

//http://www.antongerdelan.net/opengl/raycasting.html
void EventHandler::detectObjectUnderClick()
{
	double mouse_xpos, mouse_ypos;
	glfwGetCursorPos(m_window, &mouse_xpos, &mouse_ypos);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	//Normalise mouse coordinates
	float x = (2.0f * mouse_xpos) / width - 1.0f;
	float y = 1.0f - (2.0f * mouse_ypos) / height;
	float z = 1.0f;
	glm::vec3 ray = glm::vec3(x, y, z);

	//Ray homogeneous clip coords
	glm::vec4 ray_clip = glm::vec4(ray.x, ray.y, -1.0, 1.0);

	//Camera coordinates
	Camera camera = m_objectStack->getCamera();
	glm::mat4 projection = camera.getProjectionMat();

	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;

	//World coordinates
	glm::mat4 view = camera.getViewMat();

	glm::vec3 ray_world(glm::inverse(view) * ray_eye);
	ray_world = glm::normalize(ray_world);

	std::printf(testRayCollisionsWithObjectStack(ray_world) ? "true" : "false");
}

bool EventHandler::testRayCollisionsWithObjectStack(glm::vec3 ray)
{
	RubixCube* rubixCube = (RubixCube*) m_objectStack[0][0];
	std::vector<SmallCube*> smallCubes = rubixCube->getCubes();
	
	bool collided = false;

	for (int i = 0; i < smallCubes.size(); i++)
	{
		bool temp = testRayCollisionsWithMesh(ray, smallCubes[i]->getMesh());
		if (temp == true && collided == false)
			collided = true;
	}

	return collided;
}

bool EventHandler::testRayCollisionsWithMesh(glm::vec3 ray, ScMesh* mesh)
{
	bool collided = false;

	return collided;
}