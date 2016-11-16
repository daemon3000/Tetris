#include "MenuNewHighscoreScreen.h"
#include "MenuStateID.h"
#include "ResourceCache.h"
#include "MenuStateMachine.h"
#include "TetrisGame.h"
#include "TextAsset.h"

using namespace tetris;
using namespace tetris::ui;

MenuNewHighscoreScreen::MenuNewHighscoreScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine) :
	MenuState(stateMachine),
	m_game(game)
{
}

bool MenuNewHighscoreScreen::create(ResourceCache &resourceCache)
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

	if(!createMessage())
		return false;

	if(!createNameBox(resourceCache))
		return false;

	if(!createButtons(resourceCache))
		return false;

	return true;
}

bool MenuNewHighscoreScreen::createBackgroundPanel(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		tgui::Picture::Ptr bg = std::make_shared<tgui::Picture>();
		bg->setTexture({ *atlas, sf::IntRect(4, 4, 120, 120), sf::IntRect(16, 65, 88, 38) });
		bg->setPosition(sf::Vector2f(10.0f, 160.0f));
		bg->setSize(sf::Vector2f(364.0f, 320.0f));
		m_panel->add(bg);
		return true;
	}

	return false;
}

bool MenuNewHighscoreScreen::createTitle()
{
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	tgui::Label::Ptr titleShadow = std::make_shared<tgui::Label>();
	tgui::TextStyle style(sf::Text::Bold);

	title->setText("NEW HIGHSCORE!");
	title->setTextSize(28);
	title->setSize(sf::Vector2f(384.0f, 36.0f));
	title->setPosition(sf::Vector2f(10.0f, 168.0f));
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->getRenderer()->setTextStyle(style);
	title->getRenderer()->setTextColor({ 255, 255, 255, 255 });

	titleShadow->setText("NEW HIGHSCORE!");
	titleShadow->setTextSize(28);
	titleShadow->setSize(sf::Vector2f(384.0f, 36.0f));
	titleShadow->setPosition(sf::Vector2f(12.0f, 170.0f));
	titleShadow->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	titleShadow->getRenderer()->setTextStyle(style);
	titleShadow->getRenderer()->setTextColor({ 50, 50, 50, 255 });

	m_panel->add(titleShadow);
	m_panel->add(title);
	return true;
}

bool MenuNewHighscoreScreen::createMessage()
{
	tgui::Label::Ptr message = std::make_shared<tgui::Label>();
	message->setText("Enter your name:");
	message->setTextSize(16);
	message->setSize(sf::Vector2f(324.0f, 30.0f));
	message->setPosition(sf::Vector2f(30.0f, 225.0f));
	message->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	message->getRenderer()->setTextColor({ 88, 88, 88, 255 });

	m_panel->add(message);
	return true;
}

bool MenuNewHighscoreScreen::createNameBox(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		m_nameBox = std::make_shared<tgui::EditBox>();
		m_nameBox->setMaximumCharacters(10);
		m_nameBox->setTextSize(16);
		m_nameBox->setInputValidator("[a-z0-9_]*");
		m_nameBox->getRenderer()->setPadding({ 10, 10, 10, 10 });
		m_nameBox->getRenderer()->setBorders({ 0, 0, 0, 0 });
		m_nameBox->getRenderer()->setTexture({ *atlas, { 126, 55, 190, 45 }, { 15, 15, 160, 15 } });
		m_nameBox->getRenderer()->setTextureHover({ *atlas, { 126, 55, 190, 45 }, { 15, 15, 160, 15 } });
		m_nameBox->getRenderer()->setTextureDisabled({ *atlas, { 126, 55, 190, 45 }, { 15, 15, 160, 15 } });
		m_nameBox->setSize(sf::Vector2f(324.0f, 49.0f));
		m_nameBox->setPosition(sf::Vector2f(25.0f, 265.0f));

		m_panel->add(m_nameBox);
		return true;
	}

	return false;
}

bool MenuNewHighscoreScreen::createButtons(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("data/ui/tetris_ui.png");
	if(atlas != nullptr)
	{
		tgui::Button::Ptr button = std::make_shared<tgui::Button>();
		button->setText("Continue");
		button->setTextSize(16);
		button->setPosition(sf::Vector2f(97.0f, 421.0f));
		button->setSize(sf::Vector2f(190.0f, 49.0f));
		button->getRenderer()->setBorders({ 0, 0, 0, 0 });
		button->getRenderer()->setTextColor({ 88, 88, 88, 255 });
		button->getRenderer()->setTextColorHover({ 88, 88, 88, 255 });
		button->getRenderer()->setTextColorDown({ 88, 88, 88, 255 });
		button->getRenderer()->setTexture({ *atlas, sf::IntRect(126, 4, 190, 45) });
		button->getRenderer()->setTextureHover({ *atlas, sf::IntRect(126, 4, 190, 45) });
		button->getRenderer()->setTextureDown({ *atlas, sf::IntRect(318, 4, 190, 49) });

		button->connect("pressed", [this]()
		{
			if(m_nameBox->getText().getSize() > 0)
			{
				saveNewHighscore();
				m_game->stopCurrentGame();
				if(auto sm = m_stateMachine.lock())
					sm->popState();
			}
		});

		m_panel->add(button);
		return true;
	}

	return false;
}

void MenuNewHighscoreScreen::saveNewHighscore()
{
	auto highscores = m_game->getHighscores();
	highscores->add(m_nameBox->getText(), m_game->getScore());
}

void MenuNewHighscoreScreen::onFocusEnter()
{
	MenuState::onFocusEnter();
	m_panel->enable();
}

void MenuNewHighscoreScreen::onFocusExit()
{
	MenuState::onFocusExit();
	m_panel->disable(false);
}

void MenuNewHighscoreScreen::onShow()
{
	MenuState::onShow();
	m_panel->show();
}

void MenuNewHighscoreScreen::onHide()
{
	MenuState::onHide();
	m_panel->hide();
}

std::string MenuNewHighscoreScreen::getID() const
{
	return MenuStateID::NEW_HIGHSCORE_SCREEN;
}

MenuStackFlags MenuNewHighscoreScreen::getStackFlags() const
{
	return MenuStackFlags::DrawOnly;
}
