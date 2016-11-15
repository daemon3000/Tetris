#include "MenuStateMachine.h"
#include "MenuState.h"
#include "easylogging++.h"

using namespace tetris::ui;

MenuStateMachine::MenuStateMachine() :
	m_updateOrderStart(0),
	m_renderOrderStart(0)
{
}

void MenuStateMachine::registerState(std::shared_ptr<MenuState> state)
{
	m_states.push_back(state);
}


void MenuStateMachine::update(float deltaTime)
{
	for(size_t i = m_updateOrderStart; i < m_stateStack.size(); i++)
	{
		m_stateStack[i]->onUpdate(deltaTime);
	}
}

void MenuStateMachine::render()
{
	for(size_t i = m_renderOrderStart; i < m_stateStack.size(); i++)
	{
		m_stateStack[i]->onRender();
	}
}

void MenuStateMachine::changeState(const std::string &stateID)
{
	auto state = findState(stateID);

	clearAll();
	if(state != nullptr)
	{
		state->onEnter();
		m_stateStack.push_back(state);
	}
	else
	{
		LOG(INFO) << "Could not find menu state with ID '" << stateID << "'";
	}
}

void MenuStateMachine::pushState(const std::string &stateID)
{
	auto state = findState(stateID);

	if(state != nullptr)
	{
		switch(state->getStackFlags())
		{
		case MenuStackFlags::DrawOnly:
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onFocusExit();
				if(m_stateStack[i]->getStackFlags() != MenuStackFlags::DrawAndUpdate)
					break;
			}
			break;
		case MenuStackFlags::HideAndDontUpdate:
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onFocusExit();
				if(m_stateStack[i]->getStackFlags() != MenuStackFlags::DrawAndUpdate)
					break;
			}
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onHide();
				if(m_stateStack[i]->getStackFlags() == MenuStackFlags::HideAndDontUpdate)
					break;
			}
			break;
		default:
			break;
		}

		state->onEnter();
		m_stateStack.push_back(state);
		calculateUpdateOrder();
		calculateRenderOrder();
	}
	else
	{
		LOG(INFO) << "Could not find menu state with ID '" << stateID << "'";
	}
}

void MenuStateMachine::popState(const std::string &stateID)
{
	if(m_stateStack.size() > 0)
	{
		auto state = m_stateStack[m_stateStack.size() - 1];
		state->onExit();
		m_stateStack.pop_back();

		switch(state->getStackFlags())
		{
		case MenuStackFlags::DrawOnly:
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onFocusEnter();
				if(m_stateStack[i]->getStackFlags() != MenuStackFlags::DrawAndUpdate)
					break;
			}
			break;
		case MenuStackFlags::HideAndDontUpdate:
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onFocusEnter();
				if(m_stateStack[i]->getStackFlags() != MenuStackFlags::DrawAndUpdate)
					break;
			}
			for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
			{
				m_stateStack[i]->onShow();
				if(m_stateStack[i]->getStackFlags() == MenuStackFlags::HideAndDontUpdate)
					break;
			}
			break;
		default:
			break;
		}

		calculateUpdateOrder();
		calculateRenderOrder();
	}
}

void MenuStateMachine::clearAll()
{
	for(size_t i = 0; i < m_stateStack.size(); i++)
	{
		m_stateStack[i]->onExit();
	}
	m_stateStack.clear();
	m_updateOrderStart = 0;
	m_renderOrderStart = 0;
}

void MenuStateMachine::calculateUpdateOrder()
{
	m_updateOrderStart = 0;
	for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
	{
		if(m_stateStack[i]->getStackFlags() != MenuStackFlags::DrawAndUpdate)
		{
			m_updateOrderStart = i;
			break;
		}
	}
}

void MenuStateMachine::calculateRenderOrder()
{
	m_renderOrderStart = 0;
	for(size_t i = m_stateStack.size() - 1; i >= 0; i--)
	{
		if(m_stateStack[i]->getStackFlags() == MenuStackFlags::HideAndDontUpdate)
		{
			m_renderOrderStart = i;
			break;
		}
	}
}

std::shared_ptr<MenuState> MenuStateMachine::findState(const std::string &stateID)
{
	if(stateID.size() > 0)
	{
		for(size_t i = 0; i < m_states.size(); i++)
		{
			if(m_states[i]->getID() == stateID)
				return m_states[i];
		}
	}

	return nullptr;
}