#pragma once

#include <memory>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include "TetrominoColor.h"

namespace tetris
{
	class ResourceCache;

	class Tileset
	{
		std::unordered_map<TetrominoColor, std::shared_ptr<sf::Sprite>> m_tiles;
		sf::Vector2i m_tileSize;
		sf::Vector2i m_size;

	public:
		bool loadFromFile(const std::string &filename, ResourceCache &resourceCache);
		std::shared_ptr<sf::Sprite> getTile(TetrominoColor color) const;
		sf::Vector2i getSize() const;
		sf::Vector2i getTileSize() const;
	};
}