#include "MenuHomeScreen.h"
#include "Application.h"
#include "ResourceCache.h"
#include "TetrisGame.h"
#include "Tileset.h"

using namespace tetris;
using namespace tetris::ui;

MenuHomeScreen::MenuHomeScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine) :
	MenuState(stateMachine),
	m_game(game)
{
}

bool MenuHomeScreen::create(ResourceCache &resourceCache)
{
	auto app = Application::getInstance();
	auto font = resourceCache.loadFont("data/fonts/kenvector_future.ttf");
	m_tileset = resourceCache.loadTileset("data/gfx/tileset.xml");

	if(font == nullptr || m_game == nullptr || m_tileset == nullptr)
		return false;

	m_queuedTetromino.setType(m_game->getQueuedTetromino());
	m_game->tetrominoQueueChanged.connect([this]()
	{
		m_queuedTetromino.setType(m_game->getQueuedTetromino());
	});

	m_gui.setWindow(*app->getWindow());
	m_gui.setFont(font);

	if(!createBackgroundPanel(resourceCache))
		return false;
	
	if(!createTitle())
		return false;

	if(!createButtons(resourceCache))
		return false;

	if(!createGameplayStats())
		return false;
	
	if(!createGameOverLabel())
		return false;

	return true;
}

bool MenuHomeScreen::createBackgroundPanel(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		tgui::Picture::Ptr bg = std::make_shared<tgui::Picture>();
		bg->setTexture({ *atlas, sf::IntRect(4, 4, 100, 100), sf::IntRect(20, 20, 60, 60) });
		bg->setPosition(sf::Vector2f(384.0f, 0.0f));
		bg->setSize(sf::Vector2f(256.0f, 640.0f));
		m_gui.add(bg);
		return true;
	}

	return false;
}

bool MenuHomeScreen::createTitle()
{
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	tgui::Label::Ptr titleShadow = std::make_shared<tgui::Label>();
	tgui::TextStyle style(sf::Text::Bold);

	title->setText("TETRIS");
	title->setTextSize(50);
	title->setSize(sf::Vector2f(256.0f, 50.0f));
	title->setPosition(sf::Vector2f(384.0f, 8.0f));
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->getRenderer()->setTextStyle(style);
	title->getRenderer()->setTextColor({ 255, 204, 0, 255 });

	titleShadow->setText("TETRIS");
	titleShadow->setTextSize(50);
	titleShadow->setSize(sf::Vector2f(256.0f, 50.0f));
	titleShadow->setPosition(sf::Vector2f(386.0f, 10.0f));
	titleShadow->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	titleShadow->getRenderer()->setTextStyle(style);
	titleShadow->getRenderer()->setTextColor({ 50, 50, 50, 255 });

	m_gui.add(titleShadow);
	m_gui.add(title);
	return true;
}

bool MenuHomeScreen::createButtons(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		auto newGameButton = createButton(atlas, "NEW GAME", { 414.0f, 100.0f });
		newGameButton->connect("pressed", [this]()
		{
			m_game->startNewGame();
		});

		m_pauseButton = createButton(atlas, "PAUSE", { 414.0f, 155.0f });
		m_pauseButton->connect("pressed", [this]()
		{
			if(m_game->isGameRunning() && !m_game->isGameOver())
			{
				if(m_game->isGamePaused())
				{
					m_game->unpauseCurrentGame();
					m_pauseButton->setText("PAUSE");
				}
				else
				{
					m_game->pauseCurrentGame();
					m_pauseButton->setText("RESUME");
				}
			}
		});

		createButton(atlas, "HIGHSCORES", { 414.0f, 210.0f });
		createButton(atlas, "ABOUT", { 414.0f, 265.0f });
		return true;
	}

	return false;
}

tgui::Button::Ptr MenuHomeScreen::createButton(std::shared_ptr<sf::Texture> atlas, std::string text, sf::Vector2f position)
{
	tgui::Button::Ptr button = std::make_shared<tgui::Button>();
	button->setText(text);
	button->setTextSize(16);
	button->setPosition(position);
	button->setSize(sf::Vector2f(190.0f, 49.0f));
	button->getRenderer()->setBorders({ 0, 0, 0, 0 });
	button->getRenderer()->setTextColor({ 88, 88, 88, 255 });
	button->getRenderer()->setTextColorHover({ 88, 88, 88, 255 });
	button->getRenderer()->setTextColorDown({ 88, 88, 88, 255 });
	button->getRenderer()->setTexture({ *atlas, sf::IntRect(4, 157, 190, 45) });
	button->getRenderer()->setTextureHover({ *atlas, sf::IntRect(4, 157, 190, 45) });
	button->getRenderer()->setTextureDown({ *atlas, sf::IntRect(4, 106, 190, 49) });
	
	m_gui.add(button);
	return button;
}

bool MenuHomeScreen::createGameplayStats()
{
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	title->setText("STATISTICS:");
	title->setTextSize(20);
	title->setSize(sf::Vector2f(220, 30.0f));
	title->setPosition(sf::Vector2f(414.0f, 484.0f));
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	title->getRenderer()->setTextColor({ 255, 102, 0, 255 });

	m_levelStat = createStatLable("LEVEL  :", { 424.0f, 520 });
	m_levelStat->setText(std::to_string(m_game->getLevel()));
	m_game->levelChanged.connect([this]()
	{
		m_levelStat->setText(std::to_string(m_game->getLevel()));
	});

	m_scoreStat = createStatLable("SCORE  :", { 424.0f, 545 });
	m_scoreStat->setText(std::to_string(m_game->getScore()));
	m_game->scoreChanged.connect([this]()
	{
		m_scoreStat->setText(std::to_string(m_game->getScore()));
	});

	m_linesStat = createStatLable("LINES    :", { 424.0f, 570 });
	m_linesStat->setText(std::to_string(m_game->getNumberOfClearedLines()));
	m_game->numberOfClearedLinesChanged.connect([this]()
	{
		m_linesStat->setText(std::to_string(m_game->getNumberOfClearedLines()));
	});

	m_timeStat = createStatLable("TIME      :", { 424.0f, 595 });
	m_timeStat->setText(std::to_string((int)m_game->getGameTime()));

	m_gui.add(title);
	return true;
}

tgui::Label::Ptr MenuHomeScreen::createStatLable(std::string text, sf::Vector2f position)
{
	tgui::Label::Ptr label = std::make_shared<tgui::Label>();
	label->setText(text);
	label->setTextSize(16);
	label->setSize(sf::Vector2f(80.0f, 20.0f));
	label->setPosition(position);
	label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	label->getRenderer()->setTextColor({ 255, 102, 0, 255 });

	tgui::Label::Ptr content = std::make_shared<tgui::Label>();
	content->setText("999999");
	content->setTextSize(16);
	content->setSize(sf::Vector2f(125.0f, 20.0f));
	content->setPosition({ position.x + 85.0f, position.y });
	content->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	content->getRenderer()->setTextColor({ 255, 102, 0, 255 });

	m_gui.add(label);
	m_gui.add(content);
	return content;
}

bool MenuHomeScreen::createGameOverLabel()
{
	m_gameOverLabel = std::make_shared<tgui::Label>();
	m_gameOverLabel->setText("GAME OVER!");
	m_gameOverLabel->setTextSize(24);
	m_gameOverLabel->setSize(sf::Vector2f(196.0f, 30.0f));
	m_gameOverLabel->setPosition(sf::Vector2f(414.0f, 390.0f));
	m_gameOverLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	m_gameOverLabel->getRenderer()->setTextColor({ 255, 102, 0, 255 });
	m_gameOverLabel->hide();

	m_gui.add(m_gameOverLabel);
	return true;
}

void MenuHomeScreen::onUpdate(float deltaTime)
{
	auto app = Application::getInstance();
	auto eventManager = app->getEventManager();

	eventManager->forEachEvent([this](const sf::Event &evt)
	{
		m_gui.handleEvent(evt);
	});

	m_timeStat->setText(std::to_string((int)m_game->getGameTime()));
	if(m_game->isGameRunning() && m_game->isGameOver())
	{
		if(!m_gameOverLabel->isVisible())
			m_gameOverLabel->show();
	}
	else 
	{
		if(m_gameOverLabel->isVisible())
			m_gameOverLabel->hide();
	}
}

void MenuHomeScreen::onRender()
{
	m_gui.draw();
	renderTetrominoPreview();
}

void MenuHomeScreen::renderTetrominoPreview()
{
	if(m_game->isGameRunning() && !m_game->isGameOver())
	{
		if(m_queuedTetromino.isValid())
		{
			auto app = Application::getInstance();
			auto tile = m_tileset->getTile(m_queuedTetromino.getColor());
			auto tileSize = m_tileset->getTileSize();
			auto tetrominoPos = sf::Vector2f(512.0f - (m_queuedTetromino.getWidth() * tileSize.x) / 2.0f, 
											 340.0f + ((m_queuedTetromino.getHeight() - (m_queuedTetromino.getPaddingTop() + m_queuedTetromino.getPaddingBottom())) * tileSize.y) / 2.0f);

			if(tile != nullptr)
			{
				for(int y = 0; y < m_queuedTetromino.getHeight(); y++)
				{
					for(int x = 0; x < m_queuedTetromino.getWidth(); x++)
					{
						if(m_queuedTetromino.isSolid(x, y))
						{
							tile->setPosition(tetrominoPos.x + x * tileSize.x, tetrominoPos.y + y * tileSize.y);
							app->draw(*tile);
						}
					}
				}
			}
		}
	}
}

std::string MenuHomeScreen::getID() const
{
	return "MenuHomeScreen";
}

MenuStackFlags MenuHomeScreen::getStackFlags() const
{
	return MenuStackFlags::HideAndDontUpdate;
}
