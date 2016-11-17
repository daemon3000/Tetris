#include <algorithm>
#include <filesystem>
#include "pugixml.hpp"
#include "easylogging++.h"
#include "HighscoreManager.h"
#include "GameConstants.h"

using namespace tetris;

HighscoreManager::HighscoreManager(int maxHighscores) :
	m_maxHighscores(maxHighscores)
{
}

void HighscoreManager::load()
{
	pugi::xml_document doc;

	m_highscores.clear();
	if(doc.load_file("saves/highscores.xml"))
	{
		for(pugi::xml_node child = doc.document_element().child("item"); child; child = child.next_sibling("item"))
		{
			std::string name = child.attribute("name").as_string();
			int score = child.attribute("score").as_int();

			if(score > MAX_SCORE)
				score = MAX_SCORE;

			m_highscores.push_back({ name, score });
		}
	}

	std::sort(m_highscores.begin(), m_highscores.end(), [](auto a, auto b)
	{
		return a.score > b.score;
	});
}

void HighscoreManager::save()
{
	pugi::xml_document doc;
	auto root = doc.append_child("highscores");

	for(size_t i = 0; i < m_highscores.size(); i++)
	{
		auto child = root.append_child("item");
		auto name = child.append_attribute("name");
		auto score = child.append_attribute("score");

		name.set_value(m_highscores[i].name.c_str());
		score.set_value(m_highscores[i].score);
	}

	try
	{
		if(!std::experimental::filesystem::exists("saves"))
			std::experimental::filesystem::create_directory("saves");
	}
	catch(const std::exception&)
	{
		LOG(ERROR) << "Failed to create 'saves' directory!";
	}
	
	if(!doc.save_file("saves/highscores.xml"))
	{
		LOG(ERROR) << "Failed to save highscores at 'saves/highscores.xml'!";
	}
}

void HighscoreManager::add(std::string name, int score)
{
	if(m_highscores.size() == 0)
	{
		m_highscores.push_back({ name, score });
		return;
	}

	for(int i = 0; i < m_highscores.size(); i++)
	{
		if(score >= m_highscores[i].score)
		{
			for(int k = m_highscores.size() - 1; k >= i; k--)
			{
				if(k == m_highscores.size() - 1)
				{
					if(m_highscores.size() < m_maxHighscores)
						m_highscores.push_back(m_highscores[m_highscores.size() - 1]);
				}
				else
				{
					m_highscores[k + 1] = m_highscores[k];
				}
			}

			m_highscores[i] = { name, score };
			break;
		}
	}
}

int HighscoreManager::count() const
{
	return m_highscores.size();
}

int HighscoreManager::maxCount() const
{
	return m_maxHighscores;
}

Highscore HighscoreManager::getAt(int index) const
{
	return m_highscores[index];
}

bool HighscoreManager::isHighscore(int score) const
{
	if(score > 0)
	{
		if(m_highscores.size() < m_maxHighscores)
			return true;

		for(size_t i = 0; i < m_highscores.size(); i++)
		{
			if(score >= m_highscores[i].score)
				return true;
		}
	}

	return false;
}