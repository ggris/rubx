#include "util/logger.hpp"
#include "mesh_cube.hpp"

#include "context.hpp"

#include "eventHandler.hpp"

void error_callback(int error, const char* description)
{
    LOG_ERROR << error << " : " << description;
}

Context::Context() :
    sc_vector_()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        LOG_FATAL << "Failed to init glfw context";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(1240, 480, "Rubix", NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
        LOG_FATAL << "Failed to create glfw window";
        exit(EXIT_FAILURE);
    }

	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	GLenum glewinit = glewInit();

	if (glewinit != GLEW_OK)
	{
		std::cout << "Glew not okay! " << glewinit;
		exit(EXIT_FAILURE);
	}
	LOG_INFO << "Glew init ok";

    glfwSwapInterval(1);

	m_ui = new UI();
	//Setup events
	EventHandler::getInstance().setUI(m_ui);
    glfwSetKeyCallback(m_window, EventHandler::key_Callback);
	glfwSetMouseButtonCallback(m_window, EventHandler::mouseButton_Callback);

    LOG_INFO << "glfw OpenGL context ready";

	initGL();
}

Context::~Context()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
    LOG_INFO << "glfw OpenGL context destroyed";
}

void Context::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        update();
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

}

void Context::initGL()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    sc_vector_.push_back(new MeshCube());
}

void Context::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float ratio;
    int width, height;

    glfwGetFramebufferSize(m_window, &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);

    sc_vector_.display();
    m_ui->display();
}
