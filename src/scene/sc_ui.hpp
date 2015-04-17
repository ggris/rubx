#ifndef UI_HPP
#define UI_HPP

#include <vector>

class UI;

#include "scene_graph.hpp"
#include "include_gl.hpp"

class UI : public ScNode
{
    public:
		UI();
        void display();
		
		void receiveKeyPress(int key);

    private:
        GLuint m_program;
        GLuint m_vao;
		bool test = false;
};

#endif
