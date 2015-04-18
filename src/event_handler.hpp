#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include "util/include_gl.hpp"

#include "sc_ui.hpp"
#include "sc_3d.hpp"
#include "sc_mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"

class EventHandler;

class EventHandler
{
    public:

		static void setUI(UI* ui);
		static void setWindow(GLFWwindow* m_window);
		static void setObjectStack(Sc3d* sc3d);

		static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButton_Callback(GLFWwindow* window, int button, int action, int mods);

		static bool buttonPressed;
		static void colorBasedObjectDetection();

    private:
		EventHandler() {};
		EventHandler(EventHandler const&) = delete;
		void operator=(EventHandler const&) = delete;

		
		static void detectObjectUnderClick();

		static UI* m_ui;
		static GLFWwindow* m_window;
		static Sc3d* m_objectStack;

};

#endif
