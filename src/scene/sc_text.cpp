#include <cmath>

#include "sc_text.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "program.hpp"

ScText::ScText(){}

ScText::ScText(glm::vec2 bottomLeftPosition, glm::vec2 size, std::string text, int maxLength)
{
	noCol = 8;
	noRow = 8;
	startCharacter = 32;
	lastTextSize = 0;

	text_ = text;
	maxLength_ = maxLength;

	initialCharacterPos_ = bottomLeftPosition;
	currentCharacterPos_ = bottomLeftPosition;

	size_ = size;

	//temporary coords
	std::vector<float> tex_coords = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f };

	panel_ = Sc2dPanel(bottomLeftPosition, size, "data/img/timesNewRomanFont.bmp", tex_coords);

	updatePanel();

}

void ScText::display()
{
	panel_.display(); 
}

void ScText::updatePanel()
{
	std::vector<float> tex_coord;
	std::vector<float> points;

	for (unsigned int i = text_.size(); i > 0; i--)
	{

		char character = text_[i-1];

		int charIndex = character - startCharacter;
		int charRow = charIndex / noRow;
		int charCol = charIndex % noRow;

		float cellReduction = 0.05f; //5%

		float atlasColL = ((float)charCol) / noCol;
		float atlasRowT = 1.0f - ((float)charRow / noRow);

		float atlasColR = atlasColL + (1.0f / noCol)*(1.0f - cellReduction);
		float atlasRowB = atlasRowT - (1.0f / noRow)*(1.0f - cellReduction);

		tex_coord.push_back(atlasColL); //bas gauche
		tex_coord.push_back(atlasRowB);

		tex_coord.push_back(atlasColR); //bas droit
		tex_coord.push_back(atlasRowB);

		tex_coord.push_back(atlasColL); //Haut gauche
		tex_coord.push_back(atlasRowT);

		tex_coord.push_back(atlasColL); //Haut gauche
		tex_coord.push_back(atlasRowT);

		tex_coord.push_back(atlasColR); //bas droit
		tex_coord.push_back(atlasRowB);

		tex_coord.push_back(atlasColR); //haut droit
		tex_coord.push_back(atlasRowT);

		if (lastTextSize != text_.size())
		{
			points.push_back(-1.0f+i);
			points.push_back(-1.0f);

			points.push_back(1.0f+i);
			points.push_back(-1.0f);

			points.push_back(-1.0f+i);
			points.push_back(1.0f);

			points.push_back(-1.0f+i);
			points.push_back(1.0f);

			points.push_back(1.0f+i);
			points.push_back(-1.0f);

			points.push_back(1.0f+i);
			points.push_back(1.0f);
		}
		else
		{
			points = panel_.getPoints();
		}
	}
	panel_.update(points, tex_coord);
}

void ScText::updateText(std::string text)
{
	lastTextSize = text_.size();

	if (text.size() > maxLength_)
		text_ = text.substr(0, maxLength_);
	else
		text_ = text;

	updatePanel();
}

std::string ScText::getText() const
{
	return text_;
}