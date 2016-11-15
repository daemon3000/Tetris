#pragma once

#include <string>
#include <SFML\Graphics.hpp>

namespace tetris
{
	class Scene : sf::NonCopyable
	{
	public:
		virtual ~Scene() {}

		virtual bool create() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void render(float deltaTime) = 0;
	};
}
