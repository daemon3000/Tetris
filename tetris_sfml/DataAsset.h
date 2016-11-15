#pragma once

#include <SFML\Graphics.hpp>
#include "pugixml.hpp"

namespace tetris
{
	class DataAsset : sf::NonCopyable
	{
		pugi::xml_document m_document;

	public:
		bool loadFromFile(const std::string &filename);

		std::string getString(const std::string &name, std::string def = "");
		float getFloat(const std::string &name, float def = 0.0f);
		int getInteger(const std::string &name, int def = 0);
		bool getBool(const std::string &name, bool def = false);
	};
}
