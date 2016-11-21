#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

namespace tetris
{
	class ResourceCache;

	class MusicPlaylist : sf::NonCopyable
	{
		std::vector<std::shared_ptr<sf::Music>> m_musicTracks;

	public:
		bool loadFromFile(const std::string &filename, ResourceCache &resourceCache);
		size_t count() const;
		std::shared_ptr<sf::Music> getTrack(int index) const;
	};
}
