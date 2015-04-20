#ifndef GAME_HPP
#define GAME_HPP

#include "util/include_gl.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"

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
		void quitGame();

		void setCube(RubixCube * cube);
		std::string getTime();

    private:
		bool gameIsWon;
		std::string userName_;
		RubixCube * cube_;

		double initialTime;
		double time;

		game_difficulty difficulty_;

};

#endif
