#pragma once

#include <memory>
#include <SFML\Audio.hpp>

namespace tetris
{
	class MusicPlaylist;

	class MusicPlayer
	{
	public:
		enum class LoopType
		{
			None, Track, Playlist
		};

	private:

		enum class State
		{
			Playing, Paused, Stopped
		};

		std::shared_ptr<MusicPlaylist> m_playlist;
		std::shared_ptr<sf::Music> m_currentTrack;
		State m_state;
		LoopType m_loop;
		int m_currentTrackIndex;

		int getRandomTrack();
		int getNextTrack();
	public:
		MusicPlayer();
		MusicPlayer(std::shared_ptr<MusicPlaylist> playlist);

		void update();
		void playTrack(int index);
		void play();
		void stop();
		void pause();
		void resume();
		void setLoop(LoopType loop);
		void setPlaylist(std::shared_ptr<MusicPlaylist> playlist);
		
		size_t getPlaylistSize() const;
		bool isPlaying() const;
		bool isPaused() const;
	};
}