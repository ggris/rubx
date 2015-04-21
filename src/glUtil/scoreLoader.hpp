#ifndef SCORE_LOADER_HPP
#define SCORE_LOADER_HPP

#include <string>
#include <vector>

class Score
{
public:
	Score();
	Score(std::string userName, unsigned int score);
	unsigned int getScore() const;
	std::string getUserName() const;
private:
	std::string userName_;
	unsigned int score_;
};

class ScoreLoader
{

public:
	ScoreLoader();
	void loadScoresFromFile();
	void saveScore(std::string user, unsigned int score);
	std::vector<Score> getScores();
private:
	std::vector<Score> scores_;
};

#endif
