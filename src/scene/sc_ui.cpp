#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "sc_ui.hpp"


UI::UI() 
{
	//Coords in 3/4 ratio
	std::vector<float> tex_3on4_coord = {
		0.0f, (1.0f / 4.0f),
		1.0f, (1.0f / 4.0f),
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, (1.0f / 4.0f),
		1.0f, 1.0f };

	frameCount = 60;

	scorePanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/scoreBackground.bmp", tex_3on4_coord);
	menuPanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/mainMenuBackground.bmp", tex_3on4_coord);

	nameTextBox = ScText(glm::vec2(-5.0f, -2.0f), glm::vec2(0.1f, 0.1f*(3.0f/4.0f)), "", 10);
	timerLabel = ScText(glm::vec2(0.0f, -12.0f), glm::vec2(0.1f, 0.1f*(3.0f / 4.0f)), "", 10);
	fpsLabel = ScText(glm::vec2(-24.0f, -32.0f), glm::vec2(0.04f, 0.04f*(3.0f / 4.0f)), "", 10);
}

void UI::display()
{
	switch (ui_state)
	{
	case UI_MENU:
		nameTextBox.display();
		menuPanel.display();
		break;
	case UI_SCORE:
		scorePanel.display();
		break;
	case UI_GAME:
		int time = glfwGetTime();
		if ((time - lastTime) >= 1) //each second
		{
			lastTime = time;

			//fps count
			if (showFps)
			{
				calculateFps();
				std::string str;
				std::ostringstream fpsStream;
				fpsStream << fps;
				str = fpsStream.str();
				str += " FPS";
				fpsLabel.updateText(str);
			}

			game_->update();

			//timer
			timerLabel.updateText(game_->getTime());
		}
		
		timerLabel.display();

		if (showFps)
		{
			frameCount++;
			fpsLabel.display();
		}

		break;
	}
}

void UI::receiveKeyPress(int key, int keyAction)
{
	switch (ui_state)
	{
	case UI_MENU:
		mainMenuKeyPress(key, keyAction);
		break;
	case UI_SCORE:
		scoreKeyPress(key, keyAction);
		break;
	case UI_GAME:
		gameKeyPress(key, keyAction);
		break;
	}
}

void UI::calculateFps()
{
	fps = frameCount;
	frameCount = 0;
}

void UI::setGame(Game * game)
{
	game_ = game;
}

UI_state UI::getState()
{
	return ui_state;
}

void UI::receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId)
{
	if (ui_state == UI_GAME)
		game_->receiveLeftMouseDrag(direction, selectedId);
}

void UI::receiveRightMouseDrag(glm::vec2 direction)
{
	if (ui_state == UI_GAME)
		game_->receiveRightMouseDrag(direction);
}

Game* UI::getGame()
{
	return game_;
}

void UI::mainMenuKeyPress(int key, int keyAction)
{
	if (key == GLFW_KEY_ENTER && keyAction == GLFW_PRESS)
	{
		game_->newGame(nameTextBox.getText(), GAME_EASY);
		showFps = false;
		ui_state = UI_GAME;
	}
	else if (key == GLFW_KEY_DOWN && keyAction != GLFW_RELEASE)
	{

	}
	else if (key == GLFW_KEY_UP && keyAction != GLFW_RELEASE)
	{

	}
	//User name textbox
	else if (key > GLFW_KEY_SPACE && key < GLFW_KEY_Z && keyAction == GLFW_PRESS)
	{
		char cKey = static_cast<char>(key);
		nameTextBox.updateText(nameTextBox.getText() + cKey);
	}
	else if (key == GLFW_KEY_BACKSPACE && keyAction == GLFW_PRESS || keyAction == GLFW_REPEAT)
	{
		nameTextBox.updateText(nameTextBox.getText().substr(0, nameTextBox.getText().size() - 1));
	}
}

void UI::scoreKeyPress(int key, int keyAction)
{
	if (key == GLFW_KEY_ENTER && keyAction == GLFW_PRESS)
	{
		ui_state = UI_MENU;
	}
}

void UI::gameKeyPress(int key, int keyAction)
{
	if (key == GLFW_KEY_ESCAPE && keyAction == GLFW_PRESS)
	{
		game_->endGame();
		if (game_->getIsWon())
			ui_state = UI_SCORE;
		else
			ui_state = UI_MENU;
	}
	else if (key == GLFW_KEY_F && keyAction == GLFW_PRESS)
	{
		fps = 0;
		showFps = !showFps;
	}
}