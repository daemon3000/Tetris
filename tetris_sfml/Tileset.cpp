#include "Tileset.h"
#include "ResourceCache.h"
#include "pugixml.hpp"

using namespace tetris;

bool Tileset::loadFromFile(const std::string &filename, ResourceCache &resourceCache)
{
	pugi::xml_document doc;

	m_tiles.clear();
	if(doc.load_file(filename.c_str()))
	{
		auto rootNode = doc.document_element();
		auto imagePath = rootNode.attribute("image").as_string();
		auto texture = resourceCache.loadTexture(imagePath);

		if(texture != nullptr)
		{
			m_size.x = rootNode.attribute("width").as_int();
			m_size.y = rootNode.attribute("height").as_int();
			m_tileSize.x = rootNode.attribute("tileWidth").as_int();
			m_tileSize.y = rootNode.attribute("tileHeight").as_int();

			for(pugi::xml_node child = rootNode.child("item"); child; child = child.next_sibling("item"))
			{
				int x = child.attribute("x").as_int();
				int y = child.attribute("y").as_int();
				int w = child.attribute("width").as_int();
				int h = child.attribute("height").as_int();
				TetrominoColor color = (TetrominoColor)child.attribute("color").as_int();

				auto tile = std::make_shared<sf::Sprite>();
				tile->setTexture(*texture);
				tile->setTextureRect(sf::IntRect(x, y, w, h));

				m_tiles.emplace(color, tile);
			}

			return true;
		}
	}

	return false;
}

std::shared_ptr<sf::Sprite> Tileset::getTile(TetrominoColor color) const
{
	auto tile = m_tiles.find(color);
	if(tile != m_tiles.end())
		return tile->second;

	return nullptr;
}

sf::Vector2i Tileset::getSize() const
{
	return m_size;
}

sf::Vector2i Tileset::getTileSize() const
{
	return m_tileSize;
}