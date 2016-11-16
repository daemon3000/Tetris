#pragma once

#include <string>
#include <vector>

namespace tetris
{
	struct Highscore
	{
		std::string name;
		int score;

		Highscore() :
			name(""),
			score(0)
		{
		}

		Highscore(std::string name, int score)
		{
			this->name = name;
			this->score = score;
		}
	};

	class HighscoreManager
	{
		std::vector<Highscore> m_highscores;
		int m_maxHighscores;

	public:
		HighscoreManager(int maxHighscores);

		void load();
		void save();
		void add(std::string name, int score);
		int count() const;
		int maxCount() const;
		Highscore getAt(int index) const;
		bool isHighscore(int score) const;
	};
}