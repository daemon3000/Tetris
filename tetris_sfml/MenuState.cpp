#include "MenuState.h"
#include "MenuStateMachine.h"

using namespace tetris::ui;

MenuState::MenuState(std::weak_ptr<MenuStateMachine> stateMachine) : 
	m_stateMachine(stateMachine)
{
}

void MenuState::onEnter()
{
	onShow();
}

void MenuState::onExit()
{
	onHide();
}

void MenuState::onFocusEnter()
{
	m_hasFocus = true;
}

void MenuState::onFocusExit()
{
	m_hasFocus = false;
}

void MenuState::onShow()
{
	m_isHidden = false;
}

void MenuState::onHide()
{
	m_isHidden = true;
}

bool MenuState::isHidden() const
{
	return m_isHidden;
}

bool MenuState::hasFocus() const
{
	return m_hasFocus;
}
