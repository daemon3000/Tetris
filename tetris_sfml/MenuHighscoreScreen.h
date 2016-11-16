#pragma once

#include <TGUI\TGUI.hpp>
#include "MenuState.h"

namespace tetris
{
	class TetrisGame;

	namespace ui
	{
		class MenuHighscoreScreen : public MenuState
		{
			TetrisGame *m_game;
			tgui::Panel::Ptr m_panel;
			tgui::Label::Ptr m_numberLabel;
			tgui::Label::Ptr m_nameLabel;
			tgui::Label::Ptr m_scoreLabel;
			bool m_wasPaused;

			bool createBackgroundPanel(ResourceCache &resourceCache);
			bool createTitle();
			bool createHighscores();
			bool createButtons(ResourceCache &resourceCache);
		public:
			MenuHighscoreScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine);

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
