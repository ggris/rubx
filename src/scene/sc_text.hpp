#ifndef SC_TEXT_HPP
#define SC_TEXT_HPP

#include <vector>
#include "include_gl.hpp"
#include <string>

#include "sc_2d_panel.hpp"

class ScText
{
    public:
		ScText();
		ScText(glm::vec2 bottomLeftPosition, glm::vec2 size, std::string text, int maxLength);

		void updateText(std::string text);
		std::string getText() const;

        void display();

    private:


		std::string text_;
		Sc2dPanel panel_;
		unsigned int maxLength_;

		glm::vec2 initialCharacterPos_;
		glm::vec2 currentCharacterPos_;
		glm::vec2 size_;

		void updatePanel();

		int noCol;
		int noRow;
		int startCharacter;
		unsigned int lastTextSize;
};

#endif
