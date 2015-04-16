#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "util/include_gl.hpp"
#include "ui.hpp"

class EventHandler;

class EventHandler
{
    public:
		static EventHandler& getInstance()
		{
			static EventHandler instance;
			return instance;
		}

		static void setUI(UI* ui);

		static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButton_Callback(GLFWwindow* window, int button, int action, int mods);
    private:
		EventHandler() {};
		EventHandler(EventHandler const&) = delete;
		void operator=(EventHandler const&) = delete;

		static UI* m_ui;
		static bool buttonPressed;
};

#endif