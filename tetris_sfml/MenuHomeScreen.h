#pragma once

#include <SFML\Audio.hpp>
#include <TGUI\TGUI.hpp>
#include "MenuState.h"
#include "Tetromino.h"

namespace tetris
{
	class TetrisGame;
	class Tileset;

	namespace ui
	{
		class MenuHomeScreen : public MenuState
		{
			TetrisGame *m_game;
			Tetromino m_queuedTetromino;
			sf::Sound m_clickSound;
			tgui::Panel::Ptr m_panel;
			tgui::Button::Ptr m_pauseButton;
			tgui::Label::Ptr m_levelStat;
			tgui::Label::Ptr m_scoreStat;
			tgui::Label::Ptr m_linesStat;
			tgui::Label::Ptr m_timeStat;
			tgui::Label::Ptr m_gameOverLabel;
			std::shared_ptr<Tileset> m_tileset;

			bool createBackgroundPanel(ResourceCache &resourceCache);
			bool createTitle();
			bool createButtons(ResourceCache &resourceCache);
			bool createGameplayStats();
			bool createGameOverLabel();
			void renderTetrominoPreview();
			tgui::Button::Ptr createButton(std::shared_ptr<sf::Texture> atlas, std::string text, sf::Vector2f position);
			tgui::Label::Ptr createStatLable(std::string text, sf::Vector2f position);
		public:
			MenuHomeScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine);

			bool create(ResourceCache &resourceCache) override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onFocusEnter() override;
			void onFocusExit() override;
			void onShow() override;
			void onHide() override;
			std::string getID() const override;
			MenuStackFlags getStackFlags() const override;
		};
	}
}
