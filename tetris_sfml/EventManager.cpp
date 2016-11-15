#include "EventManager.h"
#include "Application.h"

using namespace tetris;

void EventManager::update(sf::RenderWindow &window)
{
	auto app = Application::getInstance();
	sf::Event evt;

	m_events.clear();
	while(window.pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed)
			app->quit();

		m_events.push_back(evt);
	}
}

void EventManager::forEachEvent(std::function<void(const sf::Event &evt)> handler) const
{
	for(auto &evt : m_events)
		handler(evt);
}