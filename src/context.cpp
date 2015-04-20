#include "logger.hpp"
#include "event_handler.hpp"

#include "sc_ui.hpp"
#include "sc_3d.hpp"
#include "game.hpp"

#include "context.hpp"

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

    window_ = glfwCreateWindow(1024, 768, "Rubix", NULL, NULL);

    if (!window_)
    {
        glfwTerminate();
        LOG_FATAL << "Failed to create glfw window";
        exit(EXIT_FAILURE);
    }

	glfwMakeContextCurrent(window_);

	glewExperimental = GL_TRUE;
	GLenum glewinit = glewInit();

	if (glewinit != GLEW_OK)
	{
		std::cout << "Glew not okay! " << glewinit;
		exit(EXIT_FAILURE);
	}
	LOG_INFO << "Glew init ok";

    glfwSwapInterval(1);

	//Setup events
    glfwSetKeyCallback(window_, EventHandler::key_Callback);
	glfwSetMouseButtonCallback(window_, EventHandler::mouseButton_Callback);

    LOG_INFO << "glfw OpenGL context ready";

	initGL();
    initScene();
}

Context::~Context()
{
    glfwDestroyWindow(window_);
    glfwTerminate();
    LOG_INFO << "glfw OpenGL context destroyed";
}

void Context::run()
{
    while (!glfwWindowShouldClose(window_))
    {
        update();
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

}

void Context::initGL()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void Context::initScene()
{
	Game * game = new Game();
    UI * ui = new UI();

	ui->setGame(game);

	Sc3d* sc3d = new Sc3d(window_);

	sc_vector_.push_back(sc3d);
    sc_vector_.push_back(ui);

	EventHandler::setUI(ui);
	EventHandler::setWindow(window_);
	EventHandler::setObjectStack(sc3d);
}

void Context::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    glViewport(0, 0, width, height);

	if (EventHandler::buttonPressed)
	{
		EventHandler::colorBasedObjectDetection();
	}

	sc_vector_.display();

	
}
