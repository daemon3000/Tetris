#include "MusicPlaylist.h"
#include "ResourceCache.h"
#include "pugixml.hpp"

using namespace tetris;

bool MusicPlaylist::loadFromFile(const std::string &filename, ResourceCache &resourceCache)
{
	pugi::xml_document doc;

	m_musicTracks.clear();
	if(doc.load_file(filename.c_str()))
	{
		auto rootNode = doc.document_element();
		
		for(pugi::xml_node child = rootNode.child("track"); child; child = child.next_sibling("track"))
		{
			std::string path = child.attribute("path").as_string();
			float volume = child.attribute("volume").as_float(100.0f);

			auto music = resourceCache.loadMusic(path);
			if(music != nullptr)
			{
				music->setVolume(volume);
				m_musicTracks.push_back(music);
			}
		}

		return true;
	}

	return false;
}

size_t MusicPlaylist::count() const
{
	return m_musicTracks.size();
}

std::shared_ptr<sf::Music> MusicPlaylist::getTrack(int index) const
{
	return m_musicTracks[index];
}