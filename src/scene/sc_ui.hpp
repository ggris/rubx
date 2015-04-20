#ifndef UI_HPP
#define UI_HPP

#include <vector>

#include "scene_graph.hpp"
#include "include_gl.hpp"
#include "sc_2d_panel.hpp"
#include "sc_text.hpp"
#include "game.hpp"

enum UI_state { UI_MENU, UI_SCORE, UI_GAME };
class UI : public ScNode
{
    public:
		UI();
        void display();
		
		void receiveKeyPress(int key, int keyAction);

		void setGame(Game * game);
		UI_state getState();
		Game* getGame();

		void receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId);
		void receiveRightMouseDrag(glm::vec2 direction);

    private:
		UI_state ui_state = UI_MENU;
		Sc2dPanel scorePanel;
		Sc2dPanel menuPanel;
		ScText nameTextBox;

		ScText timerLabel;

		ScText fpsLabel;
		int lastTime;

		void calculateFps();
		int fps;
		int frameCount;

		Game * game_;

		bool showFps = false;

		void mainMenuKeyPress(int key, int keyAction);
		void scoreKeyPress(int key, int keyAction);
		void gameKeyPress(int key, int keyAction);

};

#endif
