#include <utility>
#include "ResourceCache.h"
#include "DataAsset.h"
#include "TextAsset.h"
#include "Tileset.h"
#include "MusicPlaylist.h"

using namespace tetris;

std::shared_ptr<sf::Texture> ResourceCache::loadTexture(const std::string& path, bool smooth)
{
	auto loadedTexture = m_textures.find(path);
	if (loadedTexture != m_textures.end())
		return loadedTexture->second;

	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile(path))
	{
		texture->setSmooth(smooth);
		m_textures.insert(std::make_pair(path, texture));
		return texture;
	}
	
	return nullptr;
}

std::shared_ptr<sf::Font> ResourceCache::loadFont(const std::string& path)
{
	auto loadedFont = m_fonts.find(path);
	if (loadedFont != m_fonts.end())
		return loadedFont->second;

	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
	if (font->loadFromFile(path))
	{
		m_fonts.insert(std::make_pair(path, font));
		return font;
	}
	
	return nullptr;
}

std::shared_ptr<sf::SoundBuffer> ResourceCache::loadSound(const std::string & path)
{
	auto loadedSound = m_sounds.find(path);
	if(loadedSound != m_sounds.end())
		return loadedSound->second;

	std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();
	if(sound->loadFromFile(path))
	{
		m_sounds.insert(std::make_pair(path, sound));
		return sound;
	}

	return nullptr;
}

std::shared_ptr<sf::Music> ResourceCache::loadMusic(const std::string & path)
{
	auto loadedMusic = m_music.find(path);
	if(loadedMusic != m_music.end())
		return loadedMusic->second;

	std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
	if(music->openFromFile(path))
	{
		m_music.insert(std::make_pair(path, music));
		return music;
	}

	return nullptr;
}

std::shared_ptr<DataAsset> ResourceCache::loadDataAsset(const std::string& path)
{
	auto loadedDataAsset = m_dataAssets.find(path);
	if(loadedDataAsset != m_dataAssets.end())
		return loadedDataAsset->second;

	std::shared_ptr<DataAsset> dataAsset = std::make_shared<DataAsset>();
	if(dataAsset->loadFromFile(path))
	{
		m_dataAssets.insert(std::make_pair(path, dataAsset));
		return dataAsset;
	}

	return nullptr;
}

std::shared_ptr<TextAsset> ResourceCache::loadTextAsset(const std::string& path)
{
	auto loadedTextAsset = m_textAssets.find(path);
	if(loadedTextAsset != m_textAssets.end())
		return loadedTextAsset->second;

	std::shared_ptr<TextAsset> textAsset = std::make_shared<TextAsset>();
	if(textAsset->loadFromFile(path))
	{
		m_textAssets.insert(std::make_pair(path, textAsset));
		return textAsset;
	}

	return nullptr;
}

std::shared_ptr<Tileset> ResourceCache::loadTileset(const std::string& path)
{
	auto loadedTileset = m_tilesets.find(path);
	if(loadedTileset != m_tilesets.end())
	return loadedTileset->second;

	std::shared_ptr<Tileset> tileset = std::make_shared<Tileset>();
	if(tileset->loadFromFile(path, *this))
	{
		m_tilesets.insert(std::make_pair(path, tileset));
		return tileset;
	}

	return nullptr;
}

std::shared_ptr<MusicPlaylist> ResourceCache::loadPlaylist(const std::string & path)
{
	auto loadedPlaylist = m_playlists.find(path);
	if(loadedPlaylist != m_playlists.end())
		return loadedPlaylist->second;

	std::shared_ptr<MusicPlaylist> playlist = std::make_shared<MusicPlaylist>();
	if(playlist->loadFromFile(path, *this))
	{
		m_playlists.insert(std::make_pair(path, playlist));
		return playlist;
	}

	return nullptr;
}
