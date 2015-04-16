#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "util/include_gl.hpp"

class EventHandler;

class EventHandler
{
    public:
		static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods);
    private:
		static bool buttonPressed;
};

#endif
