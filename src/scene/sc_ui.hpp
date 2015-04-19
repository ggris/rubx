#ifndef UI_HPP
#define UI_HPP

#include <vector>

#include "scene_graph.hpp"
#include "include_gl.hpp"
#include "sc_2d_panel.hpp"

enum UI_state { UI_MENU, UI_SCORE, UI_GAME };
class UI : public ScNode
{
    public:
		UI();
        void display();
		
		void receiveKeyPress(int key);

    private:
		UI_state ui_state = UI_MENU;
		Sc2dPanel scorePanel;
		Sc2dPanel menuPanel;

};

#endif
