#include <cmath>

#include "sc_text.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"

ScText::ScText()
{
	text_ = "";
}

ScText::ScText(glm::vec2 bottomLeftPosition, glm::vec2 size, std::string text, int maxLength, float charOffSet)
{
	noCol = 8;
	noRow = 8;
	startCharacter = 32;

	charOffSet_ = charOffSet;
	text_ = text;
	maxLength_ = maxLength;

	initialCharacterPos_ = bottomLeftPosition;
	currentCharacterPos_ = bottomLeftPosition;

	size_ = size;

	for (unsigned int i = 0; i < text_.size(); i++)
	{
		generatePanel(text_[i]);
		currentCharacterPos_.x += 0.2f;
	}

}


void ScText::display()
{
	for (unsigned int i = panels_.size(); i > 0; i--)
		panels_[i-1].display();
}

void ScText::generatePanel(char character)
{
	int charIndex = character - startCharacter;
	int charRow = charIndex / noRow;
	int charCol = charIndex % noRow;

	float cellReduction = 0.35f; //35%

	float atlasColL = ((float)charCol) / noCol;
	float atlasRowT = 1.0f - ((float)charRow / noRow);

	float atlasColR = atlasColL + (1.0f/noCol)*(1.0f-cellReduction);
	float atlasRowB = atlasRowT - (1.0f / noRow)*(1.0f-cellReduction);

	std::vector<float> tex_coord = {
		atlasColL, atlasRowB,  //bas gauche
		atlasColR, atlasRowB,  //bas droit
		atlasColL, atlasRowT, //Haut gauche
		atlasColL, atlasRowT, //Haut gauche
		atlasColR, atlasRowB, //bas droit
		atlasColR, atlasRowT }; //haut droit

	Sc2dPanel panel = Sc2dPanel(currentCharacterPos_, size_, "data/img/timesNewRomanFont.bmp", tex_coord);

	panels_.push_back(panel);
}

void ScText::updateText(std::string text)
{
	if (text.size() > maxLength_)
		text_ = text.substr(0, maxLength_);
	else
		text_ = text;

	currentCharacterPos_ = initialCharacterPos_;

	panels_.clear();

	for (unsigned int i = 0; i < text_.size(); i++)
	{
		generatePanel(text_[i]);
		currentCharacterPos_.x += charOffSet_;
	}
}

std::string ScText::getText() const
{
	return text_;
}