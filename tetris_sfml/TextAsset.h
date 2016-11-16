#pragma once

#include <SFML\Graphics.hpp>

namespace tetris
{
	class TextAsset : sf::NonCopyable
	{
		std::string m_text;

	public:
		bool loadFromFile(const std::string &filename);
		std::string getText() const;
	};
}
