#include "TetrisMenu.h"
#include "MenuStateMachine.h"
#include "ResourceCache.h"
#include "MenuHomeScreen.h"
#include "TetrisGame.h"
#include "Application.h"

using namespace tetris;
using namespace tetris::ui;

TetrisMenu::TetrisMenu()
{
	m_gui = std::make_shared<tgui::Gui>();
	m_stateMachine = std::make_shared<MenuStateMachine>(m_gui);
}

bool TetrisMenu::create(TetrisGame *game, ResourceCache &resourceCache)
{
	auto app = Application::getInstance();
	auto font = resourceCache.loadFont("data/fonts/kenvector_future.ttf");
	auto homeScreen = std::make_shared<MenuHomeScreen>(game, m_stateMachine);

	m_gui->setWindow(*app->getWindow());
	m_gui->setView(sf::View({ 0.0f, 0.0f, 640.0f, 640.0f }));

	if(font != nullptr)
		m_gui->setFont(*font);

	if(!homeScreen->create(resourceCache))
		return false;

	m_stateMachine->registerState(homeScreen);
	m_stateMachine->changeState(homeScreen->getID());
	return true;
}

void TetrisMenu::update(float deltaTime)
{
	m_stateMachine->update(deltaTime);
}

void TetrisMenu::render()
{
	m_stateMachine->render();
}