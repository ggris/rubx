#include "util/logger.hpp"
#include "mesh_cube.hpp"

#include "context.hpp"

void error_callback(int error, const char* description)
{
    LOG_ERROR << error << " : " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

Context::Context()
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

    m_window = glfwCreateWindow(640, 480, "Rubix", NULL, NULL);

    if (!m_window)
    {
        glfwTerminate();
        LOG_FATAL << "Failed to create glfw window";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);
    glfwSetKeyCallback(m_window, key_callback);

    LOG_INFO << "glfw OpenGL context ready";

    initGL();
}

Context::~Context()
{
    delete m_cube;
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
    m_cube = new MeshCube();
}

void Context::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float ratio;
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    m_cube->display(glfwGetTime());
/*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
*/
}
