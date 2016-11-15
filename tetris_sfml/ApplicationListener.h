#pragma once

#include <SFML\Graphics.hpp>

namespace tetris
{
	class ApplicationListener : sf::NonCopyable
	{
	public:
		virtual ~ApplicationListener() { }
		virtual bool startup() = 0;
		virtual void fixedUpdate() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render(float deltaTime) = 0;
		virtual void shutdown() = 0;
	};
}
