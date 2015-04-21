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

	std::ostringstream stream;
	
	if (seconds >= 10 && minutes >= 10)
		stream << minutes << ":" << seconds;
	else if (minutes < 10 && seconds >= 10)
		stream << "0" << minutes << ":" << seconds;
	else
		stream << "0" << minutes << ":" << "0" << seconds;

	return stream.str();
}

std::string Game::getScore()
{
	std::ostringstream stream;

	stream << score;
	return stream.str();
}

void Game::newGame(std::string userName, game_difficulty difficulty)
{
	userName_ = userName;
	difficulty_ = difficulty;
	time = 0.0;
	initialTime = 0.0;
	timerRandomMoves = 5;
	score = 0;
	gameIsWon = false;

	//TODO RESET CUBE

	switch (difficulty)
	{
	case GAME_EASY:
		cube_->shuffle(1, 4.0f);
		break;
	case GAME_NORMAL:
		cube_->shuffle(20, 0.1f);
		break;
	case GAME_HARD:
		cube_->shuffle(50, 0.05f);
		break;
	}
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
	else if (!gameIsWon)
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
	//Todo rotate big cube or camera
}

bool Game::getIsWon()
{
	return gameIsWon;
}