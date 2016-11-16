#pragma once

#include <memory>
#include <SFML\Graphics.hpp>
#include <TGUI\TGUI.hpp>

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
		std::shared_ptr<tgui::Gui> m_gui;

	public:
		TetrisMenu();

		bool create(TetrisGame *game, ResourceCache &resourceCache);
		void update(float deltaTime);
		void render();
		void showNewHighscoreScreen();
	};
}