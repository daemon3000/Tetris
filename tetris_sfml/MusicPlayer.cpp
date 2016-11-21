#include "MusicPlayer.h"
#include "MusicPlaylist.h"
#include "Math.h"

using namespace tetris;

MusicPlayer::MusicPlayer() :
	m_playlist(nullptr),
	m_currentTrack(nullptr),
	m_currentTrackIndex(-1),
	m_loop(LoopType::None),
	m_state(State::Stopped)
{
}

MusicPlayer::MusicPlayer(std::shared_ptr<MusicPlaylist> playlist) :
	m_playlist(playlist),
	m_currentTrack(nullptr),
	m_currentTrackIndex(-1),
	m_loop(LoopType::None),
	m_state(State::Stopped)
{
}

void MusicPlayer::update()
{
	if(m_state == State::Playing && m_currentTrack->getStatus() != sf::SoundSource::Status::Playing)
	{
		int nextTrack = getNextTrack();
		if(nextTrack >= 0)
		{
			playTrack(nextTrack);
		}
		else
		{
			stop();
		}
	}
}

void MusicPlayer::playTrack(int index)
{
	stop();
	if(m_playlist != nullptr && m_playlist->count() > 0)
	{
		m_currentTrackIndex = index;
		m_currentTrack = m_playlist->getTrack(m_currentTrackIndex);
		m_currentTrack->play();
		m_state = State::Playing;
	}
}

void MusicPlayer::play()
{
	stop();
	if(m_playlist != nullptr && m_playlist->count() > 0)
	{
		if(m_currentTrackIndex < 0)
			m_currentTrackIndex = 0;

		m_currentTrack = m_playlist->getTrack(m_currentTrackIndex);
		m_currentTrack->play();
		m_state = State::Playing;
	}
}

void MusicPlayer::stop()
{
	if(m_state == State::Playing)
	{
		m_currentTrack->stop();
		m_state = State::Stopped;
	}
}

void MusicPlayer::pause()
{
	if(m_state == State::Playing)
	{
		m_currentTrack->pause();
		m_state = State::Paused;
	}
}

void MusicPlayer::resume()
{
	if(m_state == State::Paused)
	{
		m_currentTrack->play();
		m_state = State::Playing;
	}
}

void MusicPlayer::setLoop(LoopType loop)
{
	m_loop = loop;
}

void MusicPlayer::setPlaylist(std::shared_ptr<MusicPlaylist> playlist)
{
	stop();
	m_playlist = playlist;
	m_currentTrack = nullptr;
	m_currentTrackIndex = -1;
}

size_t MusicPlayer::getPlaylistSize() const
{
	return (m_playlist != nullptr) ? m_playlist->count() : 0;
}

bool MusicPlayer::isPlaying() const
{
	return m_state == State::Playing;
}

bool MusicPlayer::isPaused() const
{
	return m_state == State::Paused;
}

int MusicPlayer::getRandomTrack()
{
	return math::randomRange(0, (int)m_playlist->count());
}

int MusicPlayer::getNextTrack()
{
	if(m_loop == LoopType::None)
	{
		if(m_currentTrackIndex < m_playlist->count() - 1)
			return m_currentTrackIndex + 1;
	}
	else if(m_loop == LoopType::Track)
	{
		return m_currentTrackIndex;
	}
	else if(m_loop == LoopType::Playlist)
	{
		if(m_currentTrackIndex < m_playlist->count() - 1)
			return m_currentTrackIndex + 1;
		else
			return 0;
	}

	return -1;
}