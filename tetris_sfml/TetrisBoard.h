#pragma once

#include <memory>
#include <SFML\Graphics.hpp>

#include "Tetromino.h"
#include "Direction.h"
#include "Signal.h"

namespace tetris
{
	class Tileset;
	class ResourceCache;

	class TetrisBoard : sf::NonCopyable
	{
		const float BASE_COOLDOWN = 0.5f;
		const float BASE_COOLDOWN_SPEED = 1.0f;
		const float COOLDOWN_MULTIPLIER_PER_LEVEL = 0.2f;
		const float TURBO_SPEED = 16.0f;

		std::vector<TetrominoColor> m_board;
		std::shared_ptr<Tileset> m_tileset;
		sf::Vector2i m_tetrominoPos;
		Tetromino m_tetromino;
		bool m_isStable;
		bool m_turboCooldownSpeed;
		int m_width;
		int m_height;
		int m_score;
		int m_level;
		int m_numberOfClearedLines;
		int m_numberOfLockedTetrominos;
		float m_moveCooldown;
		float m_cooldownSpeed;

		void clear();
		void lockTetromino();
		void addScore(int clearedLines);
		void levelUp();
		bool isLineFull(int y) const;
		bool isCellEmpty(int x, int y) const;
		bool doesTetrominoFit(const Tetromino &tetromino, const sf::Vector2i &position) const;
		void updateCooldownSpeed();
	public:
		TetrisBoard();

		bool create(int width, int height, ResourceCache &resourceCache);
		void reset();
		void update(float deltaTime);
		void render();
		bool addTetromino(TetrominoType type);
		void moveTetromino(Direction direction);
		void rotateTetromino();
		void toggleTurboGravity(bool enabled);
		bool isStable() const;
		int getScore() const;
		int getLevel() const;
		int getNumberOfClearedLines() const;

		Signal scoreChanged;
		Signal levelChanged;
		Signal numberOfClearedLinesChanged;
	};
}