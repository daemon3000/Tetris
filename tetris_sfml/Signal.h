#pragma once

#include <functional>
#include <unordered_map>
#include <SFML\Graphics.hpp>

namespace tetris
{
	typedef unsigned int SignalHandle;

	class Signal : sf::NonCopyable
	{
		std::unordered_map<SignalHandle, std::function<void()>> m_listeners;
		SignalHandle m_lastID;

	public:
		Signal() :
			m_lastID(0)
		{
		}

		SignalHandle connect(std::function<void()> listener)
		{
			m_listeners.emplace(m_lastID++, listener);
			return m_lastID - 1;
		}

		void disconnect(SignalHandle id)
		{
			m_listeners.erase(id);
		}

		void disconnectAll()
		{
			m_listeners.clear();
		}

		void send()
		{
			for(auto it = m_listeners.begin(); it != m_listeners.end(); it++)
				it->second();
		}
	};
}