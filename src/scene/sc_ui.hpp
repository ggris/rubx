#ifndef UI_HPP
#define UI_HPP

#include <vector>

#include "scene_graph.hpp"
#include "include_gl.hpp"
#include "sc_2d_panel.hpp"
#include "sc_text.hpp"
#include "game.hpp"
#include "scoreLoader.hpp"

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

		void receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId, int selectedFace);
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

		ScoreLoader scoreLoader_;

		double lastTime;

		void calculateFps();
		int fps;
		int frameCount;

		ScText* scoreLabel1;
		ScText* scoreLabel2;
		ScText* scoreLabel3;
		ScText* scoreLabel4;
		ScText* scoreLabel5;
		std::vector<ScText*> scoreLabels;

		Game * game_;

		bool showFps = false;
		bool quit = false;

		void mainMenuKeyPress(int key, int keyAction);
		void scoreKeyPress(int key, int keyAction);
		void aboutKeyPress(int key, int keyAction);
		void gameKeyPress(int key, int keyAction);

		void loadScore();

		glm::vec2 scoreSelectorPos;
		glm::vec2 aboutSelectorPos;
		std::vector<glm::vec2> mainMenuPositions;

		unsigned int selectorPosition;

};

#endif
