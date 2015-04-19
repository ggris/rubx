#include <string>
#include <cstring>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>

#include "sc_ui.hpp"


UI::UI() 
{

	//Coords in 3/4 ratio
	std::vector<float> tex_coord = {
		0.0f, + (1.0f / 4.0f),
		1.0f, (1.0f / 4.0f),
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, (1.0f / 4.0f),
		1.0f, 1.0f };

	scorePanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/scoreBackground.bmp", tex_coord);
	menuPanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/mainMenuBackground.bmp", tex_coord);
}

void UI::display()
{
	switch (ui_state)
	{
	case UI_MENU:
		menuPanel.display();
		break;
	case UI_SCORE:
		scorePanel.display();
		break;
	case UI_GAME:
		break;
	}
}

void UI::receiveKeyPress(int key)
{
	if (key == GLFW_KEY_S)
	{
		switch (ui_state)
		{
		case UI_MENU:
			ui_state = UI_SCORE;
			break;
		case UI_SCORE:
			ui_state = UI_MENU;
			break;
		}
	}
	else if (key == GLFW_KEY_P && ui_state == UI_MENU)
		ui_state = UI_GAME;
	else if (key == GLFW_KEY_Q && ui_state == UI_GAME)
		ui_state = UI_MENU;
}


