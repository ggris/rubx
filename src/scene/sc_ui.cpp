#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

#include "logger.hpp"
#include "camera.hpp"
#include "sc_ui.hpp"

UI::UI() 
{
	//UV coords in 3/4 ratio
	std::vector<float> tex_3on4_coord = {
		0.0f, (1.0f / 4.0f),
		1.0f, (1.0f / 4.0f),
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, (1.0f / 4.0f),
		1.0f, 1.0f };

	//UV coords in 1/1 ratio
	std::vector<float> tex_coord = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f };

	//Score
	scoreLoader_ = ScoreLoader();
	scoreLabel1 = new ScText(glm::vec2(-6.0f, 8.0f), glm::vec2(0.05f, 0.05f*(4.0f / 3.0f)), "", 20);
	scoreLabel2 = new ScText(glm::vec2(-6.0f, 5.0f), glm::vec2(0.05f, 0.05f*(4.0f / 3.0f)), "", 20);
	scoreLabel3 = new ScText(glm::vec2(-6.0f, 2.0f), glm::vec2(0.05f, 0.05f*(4.0f / 3.0f)), "", 20);
	scoreLabel4 = new ScText(glm::vec2(-6.0f, -1.0f), glm::vec2(0.05f, 0.05f*(4.0f / 3.0f)), "", 20);
	scoreLabel5 = new ScText(glm::vec2(-6.0f, -4.0f), glm::vec2(0.05f, 0.05f*(4.0f / 3.0f)), "", 20);
	scoreLabels.push_back(scoreLabel1);
	scoreLabels.push_back(scoreLabel2);
	scoreLabels.push_back(scoreLabel3);
	scoreLabels.push_back(scoreLabel4);
	scoreLabels.push_back(scoreLabel5);

	//Backgrounds
	scorePanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/scoreBackground.bmp", tex_3on4_coord);
	menuPanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/mainMenuBackground.bmp", tex_3on4_coord);
	aboutPanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/aboutBackground.bmp", tex_3on4_coord);
	bottomPanel = Sc2dPanel(glm::vec2(0.0f, -9.0f), glm::vec2(1.0f, 0.1f), "data/img/bottomPanel.bmp", tex_3on4_coord);

	//Labels
	nameTextBox = ScText(glm::vec2(-4.0f,  5.0f), glm::vec2(0.07f, 0.07f*(4.0f/3.0f)), "", 10);
	timerLabel = ScText(glm::vec2(-2.4f, -8.5f), glm::vec2(0.08f, 0.08f*(4.0f/3.0f)), "", 10);
	victoryLabel = ScText(glm::vec2(-4.0f, -8.5f), glm::vec2(0.08f, 0.08f*(4.0f / 3.0f)), "", 10);
	fpsLabel = ScText(glm::vec2(-24.0f, -18.0f), glm::vec2(0.04f, 0.04f*(4.0f/3.0f)), "", 10);

	//Selector
	mainMenuPositions.push_back(glm::vec2(-6.0f, 2.95f)); //Easy game
	mainMenuPositions.push_back(glm::vec2(-6.0f, 0.90f)); //Normal game
	mainMenuPositions.push_back(glm::vec2(-6.0f, -1.5f)); //Hard game

	mainMenuPositions.push_back(glm::vec2(-10.1f, -4.0f)); //Score window
	mainMenuPositions.push_back(glm::vec2(-10.1f, -6.2f)); //About window
	mainMenuPositions.push_back(glm::vec2(-10.1f, -8.5f)); //Quit

	scoreSelectorPos = glm::vec2(-10.1f, -8.5f); //Back to main menu
	aboutSelectorPos = glm::vec2(-10.1f, -8.5f); //Back to main menu

	selectorPosition = 0;

	selector = Sc2dPanel(mainMenuPositions[selectorPosition], glm::vec2(0.04f, 0.04f*(4.0f/3.0f)), "data/img/selector.bmp", tex_coord);

	//fps
	frameCount = 60;
}

void UI::display()
{
	switch (ui_state)
	{
	case UI_MENU:
		selector.display();
		nameTextBox.display();
		menuPanel.display();
		break;
	case UI_SCORE:
		selector.display();
		scoreLabel1->display();
		scoreLabel2->display();
		scoreLabel3->display();
		scoreLabel4->display();
		scoreLabel5->display();
		scorePanel.display();
		break;
	case UI_ABOUT:
		selector.display();
		aboutPanel.display();
		break;
	case UI_GAME:
		double time = glfwGetTime();
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

		if (showFps)
		{
			frameCount++;
			fpsLabel.display();
		}

		if (game_->getIsWon())
		{
			victoryLabel.updateText("SCORE: " + game_->getScoreString());
			victoryLabel.display();
		}
		else
			timerLabel.display();

		bottomPanel.display();

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
	case UI_ABOUT:
		aboutKeyPress(key, keyAction);
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

void UI::receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId, int selectedFace)
{
	if (ui_state == UI_GAME)
		game_->receiveLeftMouseDrag(direction, selectedId, selectedFace);
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
		switch (selectorPosition)
		{
		case 0: //Easy game
			game_->newGame(nameTextBox.getText(), GAME_EASY);
			showFps = false;
			ui_state = UI_GAME;
			break;
		case 1: //Normal game
			game_->newGame(nameTextBox.getText(), GAME_NORMAL);
			showFps = false;
			ui_state = UI_GAME;
			break;
		case 2: //Hard game
			game_->newGame(nameTextBox.getText(), GAME_HARD);
			showFps = false;
			ui_state = UI_GAME;
			break;
		case 3: //Score window
			loadScore();
			ui_state = UI_SCORE;
			selector.updatePosition(scoreSelectorPos);
			break;
		case 4: //About window
			ui_state = UI_ABOUT;
			selector.updatePosition(aboutSelectorPos);
			break;
		case 5: //Quit
			quit = true;
			break;
		default:
			break;
		}
	}
	else if (key == GLFW_KEY_DOWN && keyAction != GLFW_RELEASE)
	{
		if (selectorPosition < mainMenuPositions.size()-1)
			selectorPosition++;
		else
			selectorPosition = 0;

		selector.updatePosition(mainMenuPositions[selectorPosition]);
	}
	else if (key == GLFW_KEY_UP && keyAction != GLFW_RELEASE)
	{
		if (selectorPosition > 0)
			selectorPosition--;
		else
			selectorPosition = mainMenuPositions.size()-1;

		selector.updatePosition(mainMenuPositions[selectorPosition]);
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
	if ((key == GLFW_KEY_ENTER || key == GLFW_KEY_ESCAPE) && keyAction == GLFW_PRESS)
	{
		ui_state = UI_MENU;
		selectorPosition = 3;
		selector.updatePosition(mainMenuPositions[selectorPosition]);
	}
}

void UI::aboutKeyPress(int key, int keyAction)
{
	if ((key == GLFW_KEY_ENTER || key == GLFW_KEY_ESCAPE) && keyAction == GLFW_PRESS)
	{
		ui_state = UI_MENU;
		selectorPosition = 4;
		selector.updatePosition(mainMenuPositions[selectorPosition]);
	}
}

void UI::gameKeyPress(int key, int keyAction)
{
	if (key == GLFW_KEY_ESCAPE && keyAction == GLFW_PRESS)
	{
		if (game_->getIsWon())
		{
			loadScore();
			scoreLoader_.saveScore(game_->getUser(), game_->getScore());
			loadScore();
			ui_state = UI_SCORE;
			selector.updatePosition(scoreSelectorPos);
		}
		else
			ui_state = UI_MENU;
	}
	else if (key == GLFW_KEY_F && keyAction == GLFW_PRESS)
	{
		fps = 0;
		showFps = !showFps;
	}
}

bool UI::getQuit()
{
	return quit;
}

void UI::loadScore()
{
	scoreLoader_.loadScoresFromFile();
	std::vector<Score> scores = scoreLoader_.getScores();

	for (unsigned int i = 0; i < scores.size(); i++)
	{
		std::ostringstream stream;
		stream << (i + 1) << ": ";
		stream << scores[i].getUserName() << " ";
		stream << scores[i].getScore() << "PTS";
		scoreLabels[i]->updateText(stream.str());
	}
}
