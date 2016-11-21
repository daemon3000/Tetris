#pragma once

#include <TGUI\TGUI.hpp>
#include "ApplicationListener.h"
#include "TetrisBoard.h"
#include "TetrisMenu.h"
#include "ResourceCache.h"
#include "Signal.h"
#include "HighscoreManager.h"
#include "MusicPlayer.h"

namespace tetris
{
	class TetrisGame : public ApplicationListener
	{
		std::shared_ptr<HighscoreManager> m_highscores;
		ResourceCache m_resourceCache;
		TetrisBoard m_board;
		TetrisMenu m_menu;
		sf::Sprite m_background;
		MusicPlayer m_musicPlayer;
		TetrominoType m_queuedTromino;
		float m_gameTime;
		bool m_isGameRunning;
		bool m_isGameOver;
		bool m_isGamePaused;

		TetrominoType chooseRandomTetromino();
		void onGameOver();
	public:
		TetrisGame();

		virtual bool startup() override;
		virtual void fixedUpdate() override;
		virtual void update(float deltaTime) override;
		virtual void render(float deltaTime) override;
		virtual void shutdown() override;

		void startNewGame();
		void stopCurrentGame();
		void pauseCurrentGame();
		void unpauseCurrentGame();
		void quit();

		std::shared_ptr<HighscoreManager> getHighscores() const;
		TetrominoType getQueuedTetromino() const;
		float getGameTime() const;
		int getScore() const;
		int getLevel() const;
		int getNumberOfClearedLines() const;
		bool isGameRunning() const;
		bool isGameOver() const;
		bool isGamePaused() const;

		Signal gameStarted;
		Signal gameStopped;
		Signal gameOver;
		Signal tetrominoQueueChanged;
		Signal scoreChanged;
		Signal levelChanged;
		Signal numberOfClearedLinesChanged;
	};
}