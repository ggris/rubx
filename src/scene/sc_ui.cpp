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

	scorePanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/scoreBackground.bmp", tex_3on4_coord);
	menuPanel = Sc2dPanel(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), "data/img/mainMenuBackground.bmp", tex_3on4_coord);

	nameTextBox = ScText(glm::vec2(-5.0f, -2.0f), glm::vec2(0.1f, 0.1f*(3.0f/4.0f)), "", 10, 1.35f);
	timer = ScText(glm::vec2(-0.5f, -2.0f), glm::vec2(0.1f, 0.1f*(3.0f / 4.0f)), "", 10, 1.35f);
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
		if ((time - lastTime) >= 1)
		{
			lastTime = time;
			std::ostringstream strs;
			strs << lastTime;
			std::string str = strs.str();
			timer.updateText(str);
		}
		timer.display();
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
	else if (ui_state == UI_MENU)
	{
		if (key > GLFW_KEY_SPACE && key < GLFW_KEY_Z)
		{
			char cKey = static_cast<char>(key);
			nameTextBox.updateText(nameTextBox.getText() + cKey);
		}
		else if (key == GLFW_KEY_BACKSPACE)
		{
			nameTextBox.updateText(nameTextBox.getText().substr(0, nameTextBox.getText().size()-1));
		}
	}
}


