#include "MenuAboutScreen.h"
#include "MenuStateID.h"
#include "ResourceCache.h"
#include "MenuStateMachine.h"
#include "TetrisGame.h"
#include "TextAsset.h"

using namespace tetris;
using namespace tetris::ui;

MenuAboutScreen::MenuAboutScreen(TetrisGame *game, std::weak_ptr<MenuStateMachine> stateMachine) :
	MenuState(stateMachine),
	m_game(game)
{
}

bool MenuAboutScreen::create(ResourceCache &resourceCache)
{
	auto clickSound = resourceCache.loadSound("assets/audio/click.ogg");
	if(clickSound == nullptr)
		return false;

	m_clickSound.setBuffer(*clickSound);

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

	if(!createAboutMessage(resourceCache))
		return false;

	if(!createButtons(resourceCache))
		return false;

	return true;
}

bool MenuAboutScreen::createBackgroundPanel(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("assets/ui/tetris_ui.png");
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

bool MenuAboutScreen::createTitle()
{
	tgui::Label::Ptr title = std::make_shared<tgui::Label>();
	tgui::Label::Ptr titleShadow = std::make_shared<tgui::Label>();
	tgui::TextStyle style(sf::Text::Bold);

	title->setText("ABOUT");
	title->setTextSize(28);
	title->setSize(sf::Vector2f(384.0f, 36.0f));
	title->setPosition(sf::Vector2f(0.0f, 8.0f));
	title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	title->getRenderer()->setTextStyle(style);
	title->getRenderer()->setTextColor({ 255, 255, 255, 255 });

	titleShadow->setText("ABOUT");
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

bool MenuAboutScreen::createAboutMessage(ResourceCache &resourceCache)
{
	auto textAsset = resourceCache.loadTextAsset("assets/text/about.txt");
	if(textAsset != nullptr)
	{
		tgui::Label::Ptr message = std::make_shared<tgui::Label>();
		message->setText(textAsset->getText());
		message->setTextSize(16);
		message->setSize(sf::Vector2f(374.0f, 570.0f));
		message->setPosition(sf::Vector2f(20.0f, 85.0f));
		message->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
		message->getRenderer()->setTextColor({ 88, 88, 88, 255 });

		m_panel->add(message);
	}
	return true;
}

bool MenuAboutScreen::createButtons(ResourceCache &resourceCache)
{
	auto atlas = resourceCache.loadTexture("assets/ui/tetris_ui.png");
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
			m_clickSound.play();
			if(auto sm = m_stateMachine.lock())
				sm->popState();
		});

		m_panel->add(button);
		return true;
	}
	
	return false;
}

void MenuAboutScreen::onEnter()
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

void MenuAboutScreen::onExit()
{
	MenuState::onExit();
	if(!m_wasPaused)
		m_game->unpauseCurrentGame();
}

void MenuAboutScreen::onFocusEnter()
{
	MenuState::onFocusEnter();
	m_panel->enable();
}

void MenuAboutScreen::onFocusExit()
{
	MenuState::onFocusExit();
	m_panel->disable(false);
}

void MenuAboutScreen::onShow()
{
	MenuState::onShow();
	m_panel->show();
}

void MenuAboutScreen::onHide()
{
	MenuState::onHide();
	m_panel->hide();
}

std::string MenuAboutScreen::getID() const
{
	return MenuStateID::ABOUT_SCREEN;
}

MenuStackFlags MenuAboutScreen::getStackFlags() const
{
	return MenuStackFlags::DrawOnly;
}
