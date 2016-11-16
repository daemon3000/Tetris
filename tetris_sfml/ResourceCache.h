#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace tetris
{
	class Tileset;
	class DataAsset;
	class TextAsset;

	class ResourceCache : sf::NonCopyable
	{
		std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textures;
		std::unordered_map<std::string, std::shared_ptr<sf::Font>> m_fonts;
		std::unordered_map<std::string, std::shared_ptr<DataAsset>> m_dataAssets;
		std::unordered_map<std::string, std::shared_ptr<TextAsset>> m_textAssets;
		std::unordered_map<std::string, std::shared_ptr<Tileset>> m_tilesets;

	public:
		std::shared_ptr<sf::Texture> loadTexture(const std::string &path, bool smooth = true);
		std::shared_ptr<sf::Font> loadFont(const std::string &path);
		std::shared_ptr<DataAsset> loadDataAsset(const std::string &path);
		std::shared_ptr<TextAsset> loadTextAsset(const std::string &path);
		std::shared_ptr<Tileset> loadTileset(const std::string &path);
	};
}
