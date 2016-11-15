#include "TetrisMenu.h"
#include "MenuStateMachine.h"
#include "ResourceCache.h"
#include "MenuHomeScreen.h"
#include "TetrisGame.h"

using namespace tetris;
using namespace tetris::ui;

TetrisMenu::TetrisMenu() :
	m_stateMachine(std::make_shared<MenuStateMachine>())
{
}

bool TetrisMenu::create(TetrisGame *game, ResourceCache &resourceCache)
{
	auto homeScreen = std::make_shared<MenuHomeScreen>(game, m_stateMachine);

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