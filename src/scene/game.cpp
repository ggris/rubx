#include "game.hpp"
#include <sstream>

Game::Game()
{
	gameIsWon = false;
	time = 0.0;
	initialTime = 0.0;
	userName_ = "";
	timerRandomMoves = 0;
}

void Game::setCube(RubixCube * cube)
{
	cube_ = cube;
}

std::string Game::getTime()
{
	unsigned int timeTemp = (unsigned int)time;
	unsigned int minutes = timeTemp / 60;

	unsigned int seconds = timeTemp - (60 * minutes);

	std::string str;
	std::ostringstream stream;
	
	if (seconds >= 10 && minutes >= 10)
		stream << minutes << ":" << seconds;
	else if (minutes < 10 && seconds >= 10)
		stream << "0" << minutes << ":" << seconds;
	else
		stream << "0" << minutes << ":" << "0" << seconds;

	str = stream.str();

	return str;
}

void Game::newGame(std::string userName, game_difficulty difficulty)
{
	userName_ = userName;
	difficulty_ = difficulty;
	time = 0.0;
	initialTime = 0.0;
	timerRandomMoves = 3;
	score = 0;

	cube_->shuffle(30, 0.1f);
}

void Game::endGame()
{
	if (gameIsWon)
	{
		score = time;
		//TODO
		//save score
	}
}

void Game::update()
{

	if (timerRandomMoves > 0)
	{
		timerRandomMoves--;

		if (timerRandomMoves == 0) // init timer if last random move
			initialTime = glfwGetTime();
	}
	else
	{
		time = glfwGetTime() - initialTime;
	}
}

void Game::receiveLeftMouseDrag(glm::vec2 direction, unsigned int selectedId)
{
	cube_->rotate(direction, selectedId, 0.5f);

	gameIsWon = cube_->isWon();

	if (gameIsWon)
		endGame();

}

void Game::receiveRightMouseDrag(glm::vec2 direction)
{
	//Todo rotate big cube
}

bool Game::getIsWon()
{
	return gameIsWon;
}