#include "game.hpp"


Game::Game()
{
	gameIsWon = false;
	time = 0.0;
	initialTime = 0.0;
	userName_ = "";
}

void Game::setCube(RubixCube * cube)
{
	cube_ = cube;
}

std::string Game::getTime()
{
	return "";
}

void Game::newGame(std::string userName, game_difficulty difficulty)
{
	userName_ = userName;
	difficulty_ = difficulty;
}

void Game::quitGame()
{

}