#include "TetrisGame.h"
#include "Application.h"
#include "Math.h"

using namespace tetris;

TetrisGame::TetrisGame() :
	m_highscores(std::make_shared<HighscoreManager>(10)),
	m_board(),
	m_isGameRunning(false),
	m_isGameOver(false),
	m_gameTime(0.0f)
{
}

TetrominoType TetrisGame::chooseRandomTetromino()
{
	return (TetrominoType)math::randomRange((int)TetrominoType::I, (int)TetrominoType::Z + 1);
}

bool TetrisGame::startup()
{
	auto bgTex = m_resourceCache.loadTexture("data/gfx/background.png");
	if(bgTex == nullptr)
		return false;

	m_highscores->load();
	m_background.setTexture(*bgTex);

	if(!m_board.create(12, 20, m_resourceCache))
		return false;

	if(!m_menu.create(this, m_resourceCache))
		return false;

	m_board.scoreChanged.connect([this]()
	{
		scoreChanged.send();
	});
	m_board.levelChanged.connect([this]()
	{
		levelChanged.send();
	});
	m_board.numberOfClearedLinesChanged.connect([this]()
	{
		numberOfClearedLinesChanged.send();
	});

	return true;
}

void TetrisGame::fixedUpdate()
{
}

void TetrisGame::update(float deltaTime)
{
	auto app = Application::getInstance();
	auto inputManager = app->getInputManager();

	if(m_isGameRunning && !m_isGameOver && !m_isGamePaused)
	{
		m_gameTime += deltaTime;

		if(inputManager->getKeyDown(sf::Keyboard::Up))
			m_board.rotateTetromino();

		if(inputManager->getKeyDown(sf::Keyboard::Left))
			m_board.moveTetromino(Direction::Left);

		if(inputManager->getKeyDown(sf::Keyboard::Right))
			m_board.moveTetromino(Direction::Right);

		if(inputManager->getKeyDown(sf::Keyboard::Down))
			m_board.toggleTurboGravity(true);

		if(inputManager->getKeyUp(sf::Keyboard::Down))
			m_board.toggleTurboGravity(false);

		m_board.update(deltaTime);

		if(m_board.isStable())
		{
			bool success = m_board.addTetromino(m_queuedTromino);
			if(success)
			{
				m_queuedTromino = chooseRandomTetromino();
				tetrominoQueueChanged.send();
			}
			else
			{
				onGameOver();
			}
		}
	}

	m_menu.update(deltaTime);
}

void TetrisGame::render(float deltaTime)
{
	auto app = Application::getInstance();
	app->draw(m_background);

	if(m_isGameRunning)
		m_board.render();

	m_menu.render();
}

void TetrisGame::shutdown()
{
}

void TetrisGame::onGameOver()
{
	m_isGameOver = true;
	gameOver.send();

	if(m_highscores->isHighscore(m_board.getScore()))
	{
		m_menu.showNewHighscoreScreen();
	}
}

void TetrisGame::startNewGame()
{
	m_board.reset();
	m_gameTime = 0.0f;
	m_isGameOver = false;
	m_isGamePaused = false;
	m_isGameRunning = m_board.addTetromino(chooseRandomTetromino());
	m_queuedTromino = chooseRandomTetromino();
	tetrominoQueueChanged.send();

	if(m_isGameRunning)
		gameStarted.send();
}

void TetrisGame::stopCurrentGame()
{
	m_board.reset();
	m_gameTime = 0.0f;
	m_isGameOver = false;
	m_isGameRunning = false;
	m_isGamePaused = false;

	gameStopped.send();
}

void TetrisGame::pauseCurrentGame()
{
	m_isGamePaused = true;
}

void TetrisGame::unpauseCurrentGame()
{
	m_isGamePaused = false;
}

void TetrisGame::quit()
{
	auto app = Application::getInstance();

	m_highscores->save();
	app->quit();
}

std::shared_ptr<HighscoreManager> TetrisGame::getHighscores() const
{
	return m_highscores;
}

TetrominoType TetrisGame::getQueuedTetromino() const
{
	return m_queuedTromino;
}

float TetrisGame::getGameTime() const
{
	return m_gameTime;
}

int TetrisGame::getScore() const
{
	return m_board.getScore();
}

int TetrisGame::getLevel() const
{
	return m_board.getLevel();
}

int TetrisGame::getNumberOfClearedLines() const
{
	return m_board.getNumberOfClearedLines();
}

bool TetrisGame::isGameRunning() const
{
	return m_isGameRunning;
}

bool TetrisGame::isGameOver() const
{
	return m_isGameOver;
}

bool TetrisGame::isGamePaused() const
{
	return m_isGamePaused;
}

