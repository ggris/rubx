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
	glm::vec4 ray_clip = glm::vec4(ray.x, ray.y, 1.0, 1.0);

	//Camera coordinates
	Camera camera = m_objectStack->getCamera();
	glm::mat4 projection = camera.getProjectionMat();

	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x,ray_eye.y, -1.0, 0.0);

	glm::vec3 ray_origin(ray_eye);

	//World coordinates
	glm::mat4 view = camera.getViewMat();

	glm::vec3 ray_world(glm::inverse(view) * ray_eye);
	ray_world = glm::normalize(ray_world);

	std::printf(testRayCollisionsWithObjectStack(ray_origin, ray_world) ? "true" : "false");
	std::printf("\n\n");
}

bool EventHandler::testRayCollisionsWithObjectStack(glm::vec3 ray_origin, glm::vec3 ray_direction)
{
	RubixCube* rubixCube = (RubixCube*) m_objectStack[0][0];
	std::vector<SmallCube*> smallCubes = rubixCube->getCubes();
	
	bool collided = false;

	float collisionDistance = 0.0f;

	int test = 0;
	for (int i = 0; i < smallCubes.size(); i++)
	{
		bool temp = testRayCollisionsWithMesh(ray_origin, ray_direction, smallCubes[i]->getMesh(), collisionDistance);
		if (temp == true && collided == false)
		{
			collided = true;
			test = i;
		}
	}

	std::printf("%d\n", test);

	return collided;
}

//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
bool EventHandler::testRayCollisionsWithMesh(glm::vec3 ray_origin, glm::vec3 ray_direction, ScMesh* mesh, float& intersection_distance)
{
	bool collided = true;

	glm::vec3 bb_max = mesh->getBoundingBoxMax();
	glm::vec3 bb_min = mesh->getBoundingBoxMin();
	glm::mat4 transf = mesh->getTransformation();

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 bb_position_world(transf[3].x, transf[3].y, transf[3].z);
	glm::vec3 delta = bb_position_world - ray_origin;

	//X axis
	glm::vec3 xaxis(transf[0].x, transf[0].y, transf[0].z);
	float e = glm::dot(xaxis, delta);
	float f = glm::dot(ray_direction, xaxis);

	if (f < 0.00001)
		f = 1.0f;

	float t1 = (e + bb_min.x) / f;
	float t2 = (e + bb_max.x) / f;

	if (t1 > t2) // if wrong order
	{
		float w = t1;
		float t1 = t2;
		float t2 = w;
	}

	if (t2 < tMax)
		tMax = t2;

	if (t1 > tMin)
		tMin = t1;

	if (tMax < tMin)
		collided = false;

	//Y axis
	glm::vec3 yaxis(transf[1].x, transf[1].y, transf[1].z);
	e = glm::dot(yaxis, delta);
	f = glm::dot(ray_direction, yaxis);

	if (f < 0.00001)
		f = 1.0f;

	t1 = (e + bb_min.y) / f;
	t2 = (e + bb_max.y) / f;

	if (t1 > t2) // if wrong order
	{
		float w = t1;
		float t1 = t2;
		float t2 = w;
	}

	if (t2 < tMax)
		tMax = t2;

	if (t1 > tMin)
		tMin = t1;

	if (tMax < tMin)
		collided = false;

	//Y axis
	glm::vec3 zaxis(transf[1].x, transf[1].y, transf[1].z);
	e = glm::dot(zaxis, delta);
	f = glm::dot(ray_direction, zaxis);

	if (f < 0.00001)
		f = 1.0f;

	t1 = (e + bb_min.y) / f;
	t2 = (e + bb_max.y) / f;

	if (t1 > t2) // if wrong order
	{
		float w = t1;
		float t1 = t2;
		float t2 = w;
	}

	if (t2 < tMax)
		tMax = t2;

	if (t1 > tMin)
		tMin = t1;

	if (tMax < tMin)
		collided = false;

	intersection_distance = tMin;

	return collided;
}