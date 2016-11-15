#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

namespace tetris
{
	class ResourceCache;
	class TetrisGame;
	
	namespace ui
	{
		class MenuStateMachine;
	}

	class TetrisMenu : sf::NonCopyable
	{
		std::shared_ptr<ui::MenuStateMachine> m_stateMachine;

	public:
		TetrisMenu();

		bool create(TetrisGame *game, ResourceCache &resourceCache);
		void update(float deltaTime);
		void render();
	};
}