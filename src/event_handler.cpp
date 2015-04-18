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

//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
void EventHandler::detectObjectUnderClick()
{
	double mouse_xpos, mouse_ypos;
	glfwGetCursorPos(m_window, &mouse_xpos, &mouse_ypos);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	mouse_ypos = height - mouse_ypos;

	//Normalise mouse coordinates
	float x = (((float)mouse_xpos / (float)width) -0.5f) * 2.0f;
	float y = (((float)mouse_ypos / (float)height)-0.5f) * 2.0f;
	glm::vec2 mouse_ndc = glm::vec2(x, y);

	//Ray homogeneous clip coords
	glm::vec4 ray_start_ndc = glm::vec4(mouse_ndc.x, mouse_ndc.y, -1.0, 1.0);
	glm::vec4 ray_end_ndc = glm::vec4(mouse_ndc.x, mouse_ndc.y, 0.0, 1.0);

	//Camera coordinates
	Camera camera = m_objectStack->getCamera();
	glm::mat4 inversedProjectionMatrix = glm::inverse(camera.getProjectionMat());
	glm::mat4 inversedViewMatrix = glm::inverse(camera.getViewMat());

	//World start vec
	glm::vec4 ray_start_camera = inversedProjectionMatrix * ray_start_ndc;
	ray_start_camera /= ray_start_camera.w;

	glm::vec4 ray_start_world = inversedViewMatrix * ray_start_camera;
	ray_start_world /= ray_start_world.w;

	//World end vec
	glm::vec4 ray_end_camera = inversedProjectionMatrix * ray_end_ndc;
	ray_end_camera /= ray_end_camera.w;

	glm::vec4 ray_end_world = inversedViewMatrix * ray_end_camera;
	ray_end_world /= ray_end_world.w;

	//Final vectors
	glm::vec3 ray_direction(ray_end_world - ray_start_world);
	glm::normalize(ray_direction);

	glm::vec3 ray_origin(ray_start_world);
	glm::normalize(ray_origin);

	std::printf(testRayCollisionsWithObjectStack(ray_origin, ray_direction) ? "true" : "false");
	std::printf("\n\n");
}

bool EventHandler::testRayCollisionsWithObjectStack(glm::vec3 ray_origin, glm::vec3 ray_direction)
{
	RubixCube* rubixCube = (RubixCube*) m_objectStack[0][0];
	std::vector<SmallCube*> smallCubes = rubixCube->getCubes();
	
	bool collided = false;

	float collisionDistance = 10000.0f;

	int test = 0;
	for (unsigned int i = 0; i < smallCubes.size(); i++)
	{
		float tempCollisionDistance = 1000.0f;
		bool temp = testRayCollisionsWithMesh(ray_origin, ray_direction, smallCubes[i]->getMesh(), tempCollisionDistance);
		if (temp == true && collided == false && tempCollisionDistance < collisionDistance)
		{
			collided = true;
			collisionDistance = tempCollisionDistance;
			test = i;
		}
	}

	std::printf("%d\n", test);
	std::printf("%f\n", collisionDistance);

	if (collided)
		rubixCube->rotate(0,1,1);

	return collided;
}

//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
bool EventHandler::testRayCollisionsWithMesh(glm::vec3 ray_origin, glm::vec3 ray_direction, ScMesh* mesh, float& intersection_distance)
{
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

	if (fabs(f) > 0.001f)
	{

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
			return false;
	}
	else
	{
		if (-e + bb_min.x > 0.0f || -e + bb_max.x < 0.0f)
			return false;
	}

	//Y axis
	glm::vec3 yaxis(transf[1].x, transf[1].y, transf[1].z);
	e = glm::dot(yaxis, delta);
	f = glm::dot(ray_direction, yaxis);

	if (fabs(f) > 0.001f)
	{

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
			return false;
	}
	else
	{
		if (-e + bb_min.x > 0.0f || -e + bb_max.x < 0.0f)
			return false;
	}

	//Z axis
	glm::vec3 zaxis(transf[2].x, transf[2].y, transf[2].z);
	e = glm::dot(zaxis, delta);
	f = glm::dot(ray_direction, zaxis);

	if (fabs(f) > 0.001f)
	{

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
			return false;
	}
	else
	{
		if (-e + bb_min.x > 0.0f || -e + bb_max.x < 0.0f)
			return false;
	}

	intersection_distance = tMin;

	return true;
}