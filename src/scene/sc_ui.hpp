#ifndef UI_HPP
#define UI_HPP

#include <vector>

#include "scene_graph.hpp"
#include "include_gl.hpp"
#include "sc_2d_panel.hpp"
#include "sc_text.hpp"
#include "game.hpp"

enum UI_state { UI_MENU, UI_SCORE, UI_GAME, UI_ABOUT };
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

		bool getQuit();

    private:
		UI_state ui_state = UI_MENU;

		Sc2dPanel scorePanel;
		Sc2dPanel aboutPanel;
		Sc2dPanel menuPanel;
		Sc2dPanel selector;

		Sc2dPanel bottomPanel;
		
		ScText nameTextBox;
		ScText timerLabel;
		ScText fpsLabel;
		ScText victoryLabel;

		int lastTime;

		void calculateFps();
		int fps;
		int frameCount;

		Game * game_;

		bool showFps = false;
		bool quit = false;

		void mainMenuKeyPress(int key, int keyAction);
		void scoreKeyPress(int key, int keyAction);
		void aboutKeyPress(int key, int keyAction);
		void gameKeyPress(int key, int keyAction);

		glm::vec2 scoreSelectorPos;
		glm::vec2 aboutSelectorPos;
		std::vector<glm::vec2> mainMenuPositions;

		unsigned int selectorPosition;

};

#endif
