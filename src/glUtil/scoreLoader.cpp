#include "scoreLoader.hpp"

#include <iostream>
#include <fstream>

Score::Score()
{
	userName_ = "";
	score_ = 0;
}

Score::Score(std::string userName, unsigned int score)
{
	userName_ = userName;
	score_ = score;
}

std::string Score::getUserName() const
{
	return userName_;
}

unsigned int Score::getScore() const
{
	return score_;
}

ScoreLoader::ScoreLoader()
{

}

void ScoreLoader::saveScore(std::string user, unsigned int score)
{
	bool savedScore = false;
	if (scores_.size() > 0)
	{
		for (unsigned int i = 0; i < 5 && i < scores_.size(); i++) //we keep only the 5 first scores
		{
			if (scores_[i].getScore() > score) //score is time, therefore less is better
			{
				unsigned int jInit = scores_.size() < 5 ? scores_.size()-1 : 4;
				for (unsigned int j = jInit; j > i; j--)
				{
					if (j - 1 > 0)
						scores_[j] = scores_[j - 1];
				}
				scores_[i] = Score(user, score);
				savedScore = true;
				break;
			}
		}
	}
	
	if (scores_.size() == 0 || (savedScore == false && scores_.size() < 5))
		scores_.push_back(Score(user, score));

	std::ofstream scoreFile;
	scoreFile.open("data/scores.txt");
	for (unsigned int i = 0; i < scores_.size(); i++)
	{
		scoreFile << scores_[i].getUserName() << "~" << scores_[i].getScore() << "\n";
	}
	scoreFile.close();
}

std::vector<Score> ScoreLoader::getScores()
{
	return scores_;
}

void ScoreLoader::loadScoresFromFile()
{
	scores_.clear();
	std::string line;
	std::ifstream scoreFile("data/scores.txt");
	std::string delimiter = "~";
	std::string userName = "";
	unsigned int score = 0;

	if (scoreFile.is_open())
	{
		while (std::getline(scoreFile, line))
		{
			userName = line.substr(0, line.find(delimiter));
			score = atoi(line.substr(line.find(delimiter)+1, line.size()).c_str());
			scores_.push_back(Score(userName, score));
		}
		scoreFile.close();
	}
}