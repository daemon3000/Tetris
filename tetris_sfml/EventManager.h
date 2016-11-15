#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

namespace tetris
{
	class EventManager : sf::NonCopyable
	{
		std::vector<sf::Event> m_events;

	public:
		void update(sf::RenderWindow &window);
		void forEachEvent(std::function<void(const sf::Event &evt)> handler) const;
	};
}