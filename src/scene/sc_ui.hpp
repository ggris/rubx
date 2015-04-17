#ifndef UI_HPP
#define UI_HPP

#include <vector>

class UI;

#include "scene_graph.hpp"
#include "include_gl.hpp"

enum UI_state { UI_START, UI_SCORE, UI_GAME };
class UI : public ScNode
{
    public:
		UI();
        void display();
		
		void receiveKeyPress(int key);

    private:
        GLuint m_program;
        GLuint m_vao;
		UI_state ui_state = UI_START;
};

#endif
