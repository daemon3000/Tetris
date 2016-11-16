#include <sstream>
#include "MenuHighscoreScreen.h"
#include "MenuStateID.h"
#include "ResourceCache.h"
#include "MenuStateMachine.h"
#include "TetrisGame.h"
#include "TextAsset.h"

using namespace tetris;
using namespace tetris::ui;

MenuHighscoreScreen::MenuHighscoreScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine) :
	MenuState(stateMachine),
	m_game(game)
{
}

bool MenuHighscoreScreen::create(ResourceCache &resourceCache)
{
	m_panel = std::make_shared<tgui::Panel>();
	m_panel->setPosition(sf::Vector2f(0, 0));
	m_panel->setSize(sf::Vector2f(640.0f, 640.0f));
	m_panel->hide();
	m_panel->disable();
	m_gui->add(m_panel);

	if(!createBackgroundPanel(resourceCache))
		return false;

	if(!createTitle())
		return false;

	if(!createHighscores())
		return false;

	if(!createButtons(resourceCache))
		return false;

	return true;
}

bool MenuHighscoreScreen::createBackgroundPanel(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		tgui::Picture::Ptr bg = std::make_shared<tgui::Picture>();
		bg->setTexture({ *atlas, sf::IntRect(4, 4, 120, 120), sf::IntRect(16, 65, 88, 38) });
		bg->setPosition(sf::Vector2f(0.0f, 0.0f));
		bg->setSize(sf::Vector2f(384.0f, 640.0f));
		m_panel->add(bg);
		return true;
	}

	return false;
}

bool MenuHighscoreScreen::createTitle()
{
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	tgui::Label::Ptr titleShadow = std::make_shared<tgui::Label>();
	tgui::TextStyle style(sf::Text::Bold);

	title->setText("HIGHSCORES");
	title->setTextSize(28);
	title->setSize(sf::Vector2f(384.0f, 36.0f));
	title->setPosition(sf::Vector2f(0.0f, 8.0f));
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->getRenderer()->setTextStyle(style);
	title->getRenderer()->setTextColor({ 255, 255, 255, 255 });

	titleShadow->setText("HIGHSCORES");
	titleShadow->setTextSize(28);
	titleShadow->setSize(sf::Vector2f(384.0f, 36.0f));
	titleShadow->setPosition(sf::Vector2f(2.0f, 10.0f));
	titleShadow->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	titleShadow->getRenderer()->setTextStyle(style);
	titleShadow->getRenderer()->setTextColor({ 50, 50, 50, 255 });

	m_panel->add(titleShadow);
	m_panel->add(title);
	return true;
}

bool MenuHighscoreScreen::createHighscores()
{
	auto hsm = m_game->getHighscores();
	std::string text;

	m_numberLabel = std::make_shared<tgui::Label>();
	m_numberLabel->setTextSize(18);
	m_numberLabel->setPosition(sf::Vector2f(20.0f, 85.0f));
	m_numberLabel->setSize(sf::Vector2f(40.0f, 570.0f));
	m_numberLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	m_numberLabel->getRenderer()->setTextColor({ 88, 88, 88, 255 });

	m_nameLabel = std::make_shared<tgui::Label>();
	m_nameLabel->setTextSize(18);
	m_nameLabel->setPosition(sf::Vector2f(60.0f, 85.0f));
	m_nameLabel->setSize(sf::Vector2f(170.0f, 570.0f));
	m_nameLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	m_nameLabel->getRenderer()->setTextColor({ 88, 88, 88, 255 });

	m_scoreLabel = std::make_shared<tgui::Label>();
	m_scoreLabel->setTextSize(18);
	m_scoreLabel->setPosition(sf::Vector2f(230.0f, 85.0f));
	m_scoreLabel->setSize(sf::Vector2f(134.0f, 570.0f));
	m_scoreLabel->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
	m_scoreLabel->getRenderer()->setTextColor({ 88, 88, 88, 255 });

	for(int i = 0; i < hsm->maxCount(); i++)
	{
		text += std::to_string(i + 1) + ".\n\n";
	}
	m_numberLabel->setText(text);

	text = "";
	for(int i = 0; i < hsm->maxCount(); i++)
	{
		if(i < hsm->count())
		{
			auto hs = hsm->getAt(i);
			text += hs.name + "\n\n";
		}
		else
		{
			text += "		-\n\n";
		}
	}
	m_nameLabel->setText(text);
	
	text = "";
	for(int i = 0; i < hsm->maxCount(); i++)
	{
		if(i < hsm->count())
		{
			auto hs = hsm->getAt(i);
			text += std::to_string(hs.score) + "\n\n";
		}
		else
		{
			text += "0\n\n";
		}
	}
	m_scoreLabel->setText(text);

	m_panel->add(m_numberLabel);
	m_panel->add(m_nameLabel);
	m_panel->add(m_scoreLabel);
	return true;
}

bool MenuHighscoreScreen::createButtons(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		tgui::Button::Ptr button = std::make_shared<tgui::Button>();
		button->setPosition(sf::Vector2f(8, 8));
		button->setSize(sf::Vector2f(36.0f, 36.0f));
		button->getRenderer()->setBorders({ 0, 0, 0, 0 });
		button->getRenderer()->setTexture({ *atlas, sf::IntRect(5, 228, 36, 36) });
		button->getRenderer()->setTextureHover({ *atlas, sf::IntRect(5, 228, 36, 36) });
		button->getRenderer()->setTextureDown({ *atlas, sf::IntRect(5, 228, 36, 36) });
		button->connect("pressed", [this]()
		{
			if(auto sm = m_stateMachine.lock())
				sm->popState();
		});

		m_panel->add(button);
		return true;
	}

	return false;
}

void MenuHighscoreScreen::onEnter()
{
	MenuState::onEnter();
	if(!m_game->isGamePaused())
	{
		m_game->pauseCurrentGame();
		m_wasPaused = false;
	}
	else
	{
		m_wasPaused = true;
	}
}

void MenuHighscoreScreen::onExit()
{
	MenuState::onExit();
	if(!m_wasPaused)
		m_game->unpauseCurrentGame();
}

void MenuHighscoreScreen::onFocusEnter()
{
	MenuState::onFocusEnter();
	m_panel->enable();
}

void MenuHighscoreScreen::onFocusExit()
{
	MenuState::onFocusExit();
	m_panel->disable(false);
}

void MenuHighscoreScreen::onShow()
{
	MenuState::onShow();
	m_panel->show();
}

void MenuHighscoreScreen::onHide()
{
	MenuState::onHide();
	m_panel->hide();
}

std::string MenuHighscoreScreen::getID() const
{
	return MenuStateID::HIGHSCORE_SCREEN;
}

MenuStackFlags MenuHighscoreScreen::getStackFlags() const
{
	return MenuStackFlags::DrawOnly;
}
