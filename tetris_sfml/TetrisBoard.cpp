#include "TetrisBoard.h"
#include "Tileset.h"
#include "ResourceCache.h"
#include "Math.h"
#include "Application.h"
#include "GameConstants.h"

using namespace tetris;

TetrisBoard::TetrisBoard()
{
	m_moveCooldown = GameConstants::BASE_COOLDOWN;
	m_cooldownSpeed = GameConstants::BASE_COOLDOWN_SPEED;
	m_width = 0;
	m_height = 0;
	m_numberOfClearedLines = 0;
	m_numberOfLockedTetrominos = 0;
	m_score = 0;
	m_level = 1;
	m_isStable = true;
	m_turboCooldownSpeed = false;
	m_tileset = nullptr;

	updateCooldownSpeed();
	clear();
}

bool TetrisBoard::create(int width, int height, ResourceCache &resourceCache)
{
	m_tileset = resourceCache.loadTileset("data/gfx/tileset.xml");
	if(m_tileset == nullptr || width <= 0 || height <= 0)
		return false;

	m_width = width;
	m_height = height;
	clear();

	return true;
}

void TetrisBoard::reset()
{
	clear();
	m_tetromino.setType(TetrominoType::None);
	m_isStable = true;
	m_turboCooldownSpeed = false;
	m_score = 0;
	m_level = 1;
	m_numberOfClearedLines = 0;
	updateCooldownSpeed();

	scoreChanged.send();
	levelChanged.send();
	numberOfClearedLinesChanged.send();
}

void TetrisBoard::clear()
{
	m_board.clear();
	for(int i = 0; i < m_width * m_height; i++)
		m_board.push_back(TetrominoColor::None);
}

void TetrisBoard::lockTetromino()
{
	if(!m_isStable && m_tetromino.isValid())
	{
		TetrominoColor color = m_tetromino.getColor();

		for(int y = m_tetromino.getPaddingTop(); y < m_tetromino.getHeight() - m_tetromino.getPaddingBottom(); y++)
		{
			for(int x = m_tetromino.getPaddingLeft(); x < m_tetromino.getWidth() - m_tetromino.getPaddingRight(); x++)
			{
				if(m_tetromino.isSolid(x, y))
				{
					int by = m_tetrominoPos.y + y;
					int bx = m_tetrominoPos.x + x;
					m_board[by * m_width + bx] = color;
				}
			}
		}

		for(int y = m_height - 1; y >= 0; y--)
		{
			if(isLineFull(y))
			{
				int k = y - 1, clearedLines = 0;

				while(k >= 0 && isLineFull(k))
					--k;

				clearedLines = y - k;

				for(int i = y; i > k; i--)
				{
					for(int x = 0; x < m_width; x++)
						m_board[i * m_width + x] = TetrominoColor::None;
				}

				for(int i = k; i >= 0; i--)
				{
					for(int x = 0; x < m_width; x++)
					{
						m_board[(y + (i - k)) * m_width + x] = m_board[i * m_width + x];
						m_board[i * m_width + x] = TetrominoColor::None;
					}
				}

				addScore(clearedLines);
				m_numberOfClearedLines += clearedLines;
			}
		}

		numberOfClearedLinesChanged.send();
		++m_numberOfLockedTetrominos;

		if(m_numberOfLockedTetrominos >= (10 + m_level * 2))
		{
			levelUp();
			m_numberOfLockedTetrominos = 0;
		}

		m_tetromino.setType(TetrominoType::None);
		m_isStable = true;
	}
}

void TetrisBoard::addScore(int clearedLines)
{
	if(clearedLines >= 4)
		m_score += 1200 * m_level;
	else if(clearedLines == 3)
		m_score += 500 * m_level;
	else if(clearedLines == 2)
		m_score += 300 * m_level;
	else if(clearedLines == 1)
		m_score += 100 * m_level;

	m_score = math::min(m_score, GameConstants::MAX_SCORE);
	scoreChanged.send();
}

void TetrisBoard::levelUp()
{
	++m_level;
	levelChanged.send();
	updateCooldownSpeed();
}

bool TetrisBoard::isLineFull(int y) const
{
	for(int x = 0; x < m_width; x++)
	{
		if(m_board[y * m_width + x] == TetrominoColor::None)
		{
			return false;
		}
	}

	return true;
}

bool TetrisBoard::isCellEmpty(int x, int y) const
{
	return m_board[y * m_width + x] == TetrominoColor::None;
}

bool TetrisBoard::doesTetrominoFit(const Tetromino &tetromino, const sf::Vector2i &position) const
{
	if(position.x < -tetromino.getPaddingLeft() || position.x > m_width - (tetromino.getWidth() - tetromino.getPaddingRight()) ||
	   position.y < -tetromino.getPaddingTop() || position.y > m_height - (tetromino.getHeight() - tetromino.getPaddingBottom()))
	{
		return false;
	}

	for(int y = tetromino.getPaddingTop(); y < tetromino.getHeight() - tetromino.getPaddingBottom(); y++)
	{
		for(int x = tetromino.getPaddingLeft(); x < tetromino.getWidth() - tetromino.getPaddingRight(); x++)
		{
			if(!isCellEmpty(position.x + x, position.y + y) && tetromino.isSolid(x, y))
			{
				return false;
			}
		}
	}

	return true;
}

void TetrisBoard::update(float deltaTime)
{
	if(!m_isStable && m_tetromino.isValid())
	{
		m_moveCooldown -= m_cooldownSpeed * deltaTime;
		if(m_moveCooldown <= 0.0f)
		{
			sf::Vector2i newPos = m_tetrominoPos;
			newPos.y += 1;

			if(doesTetrominoFit(m_tetromino, newPos))
			{
				m_tetrominoPos = newPos;
				m_moveCooldown = GameConstants::BASE_COOLDOWN;
			}
			else
			{
				lockTetromino();
			}
		}
	}
}

void TetrisBoard::render()
{
	auto app = Application::getInstance();
	auto tileSize = m_tileset->getTileSize();

	if(m_tetromino.isValid())
	{
		auto tile = m_tileset->getTile(m_tetromino.getColor());
		if(tile != nullptr)
		{
			for(int y = 0; y < m_tetromino.getHeight(); y++)
			{
				for(int x = 0; x < m_tetromino.getWidth(); x++)
				{
					if(m_tetromino.isSolid(x, y))
					{
						tile->setPosition((m_tetrominoPos.x + x) * tileSize.x, (m_tetrominoPos.y + y) * tileSize.y);
						app->draw(*tile);
					}
				}
			}
		}
	}

	for(int y = 0; y < m_height; y++)
	{
		for(int x = 0; x < m_width; x++)
		{
			if(m_board[y * m_width + x] != TetrominoColor::None)
			{
				auto tile = m_tileset->getTile(m_board[y * m_width + x]);
				tile->setPosition(x * tileSize.x, y * tileSize.y);
				app->draw(*tile);
			}
		}
	}
}

bool TetrisBoard::addTetromino(TetrominoType type)
{
	bool success = false;

	if(m_isStable)
	{
		m_tetromino.setType(type, Rotation::R0);
		if(m_tetromino.isValid())
		{
			m_tetrominoPos.x = m_width / 2 - m_tetromino.getWidth() / 2;
			m_tetrominoPos.y = 0;

			if(doesTetrominoFit(m_tetromino, m_tetrominoPos))
			{
				m_isStable = false;
				success = true;
				m_moveCooldown = GameConstants::BASE_COOLDOWN;
			}
		}

		if(!success)
		{
			m_tetromino.setType(TetrominoType::None);
		}
	}
	
	return success;
}

void TetrisBoard::moveTetromino(Direction direction)
{
	sf::Vector2i newPos = m_tetrominoPos;
	newPos.x += direction == Direction::Left ? -1 : 1;

	if(doesTetrominoFit(m_tetromino, newPos))
		m_tetrominoPos = newPos;
}

void TetrisBoard::rotateTetromino()
{
	if(m_tetromino.isValid())
	{
		Tetromino tetromino = m_tetromino;
		tetromino.rotate();

		if(doesTetrominoFit(tetromino, m_tetrominoPos))
			m_tetromino = tetromino;
	}
}

void TetrisBoard::toggleTurboGravity(bool enabled)
{
	m_turboCooldownSpeed = enabled;
	updateCooldownSpeed();
}

void TetrisBoard::updateCooldownSpeed()
{
	m_cooldownSpeed = GameConstants::BASE_COOLDOWN_SPEED + (math::min(m_level, 21) - 1) * GameConstants::COOLDOWN_MULTIPLIER_PER_LEVEL;
	if(m_turboCooldownSpeed)
		m_cooldownSpeed = math::max(GameConstants::TURBO_SPEED, m_cooldownSpeed);
}

bool TetrisBoard::isStable() const
{
	return m_isStable;
}

int TetrisBoard::getScore() const
{
	return m_score;
}

int TetrisBoard::getLevel() const
{
	return m_level;
}

int TetrisBoard::getNumberOfClearedLines() const
{
	return m_numberOfClearedLines;
}
