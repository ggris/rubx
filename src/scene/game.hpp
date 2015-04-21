#ifndef GAME_HPP
#define GAME_HPP

#include "include_gl.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"

#include "sc_3d.hpp"
#include "rubix_cube.hpp"

enum game_difficulty
{
	GAME_EASY,
	GAME_NORMAL,
	GAME_HARD
};

class Game;

class Game
{
    public:
		Game();
		void newGame(std::string userName, game_difficulty difficulty);
		void endGame();

		void setCube(RubixCube * cube);
		std::string getTime();
		std::string getScore();

		void update();

		void receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId, int selectedFace);
		void receiveRightMouseDrag(glm::vec2 direction);

		bool getIsWon();
    private:
		bool gameIsWon;
		std::string userName_;
		RubixCube * cube_;
        Sc3d * sc3d_;

		double initialTime;
		double time;

		unsigned int score = 0;
		unsigned int timerRandomMoves;

		game_difficulty difficulty_;

};

#endif
