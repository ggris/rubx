#ifndef SCORE_LOADER_HPP
#define SCORE_LOADER_HPP

#include <string>
#include <vector>

class ScoreLoader
{

public:
	ScoreLoader();
	void saveScores(std::vector<std::string> scores);
private:


};

class Score
{
public:
	Score();
private:
	std::string userName;
	unsigned int score;
};

#endif
