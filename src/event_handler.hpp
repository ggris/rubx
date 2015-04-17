#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "util/include_gl.hpp"
#include "sc_ui.hpp"

class EventHandler;

class EventHandler
{
    public:

		static void setUI(UI* ui);
		static void setWindow(GLFWwindow* m_window);

		static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButton_Callback(GLFWwindow* window, int button, int action, int mods);
    private:
		EventHandler() {};
		EventHandler(EventHandler const&) = delete;
		void operator=(EventHandler const&) = delete;

		static UI* m_ui;
		static GLFWwindow* m_window;
		static bool buttonPressed;
};

#endif
