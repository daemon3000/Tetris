#pragma once

#include <SFML\Audio.hpp>
#include <TGUI\TGUI.hpp>
#include "MenuState.h"

namespace tetris
{
	class TetrisGame;

	namespace ui
	{
		class MenuAboutScreen : public MenuState
		{
			TetrisGame *m_game;
			sf::Sound m_clickSound;
			tgui::Panel::Ptr m_panel;
			bool m_wasPaused;
			
			bool createBackgroundPanel(ResourceCache &resourceCache);
			bool createTitle();
			bool createAboutMessage(ResourceCache &resourceCache);
			bool createButtons(ResourceCache &resourceCache);
		public:
			MenuAboutScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine);

			bool create(ResourceCache &resourceCache) override;
			void onUpdate(float deltaTime) override {}
			void onRender() override {}
			void onEnter() override;
			void onExit() override;
			void onFocusEnter() override;
			void onFocusExit() override;
			void onShow() override;
			void onHide() override;
			std::string getID() const override;
			MenuStackFlags getStackFlags() const override;
		};
	}
}
