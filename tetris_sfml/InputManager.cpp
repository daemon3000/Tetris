#include "InputManager.h"
#include "EventManager.h"

using namespace tetris;

InputManager::InputManager()
{
	for (int i = 0; i < MOUSE_BUTTON_COUNT; i++)
		m_mouseButtonStates[i] = ButtonState::Released;
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
		m_keyStates[i] = ButtonState::Released;
}

void InputManager::update(const EventManager &eventManager)
{
	for (int i = 0; i < MOUSE_BUTTON_COUNT; i++)
	{
		if (m_mouseButtonStates[i] == ButtonState::JustPressed)
			m_mouseButtonStates[i] = ButtonState::Pressed;
		else if (m_mouseButtonStates[i] == ButtonState::JustReleased)
			m_mouseButtonStates[i] = ButtonState::Released;
	}

	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		if (m_keyStates[i] == ButtonState::JustPressed)
			m_keyStates[i] = ButtonState::Pressed;
		else if (m_keyStates[i] == ButtonState::JustReleased)
			m_keyStates[i] = ButtonState::Released;
	}

	eventManager.forEachEvent([this](const sf::Event &evt)
	{
		if(evt.type == sf::Event::MouseButtonPressed)
		{
			if(evt.mouseButton.button == sf::Mouse::Button::Left && !getMouseButton(MouseButton::Left))
				m_mouseButtonStates[MOUSE_BUTTON_LEFT] = ButtonState::JustPressed;
			else if(evt.mouseButton.button == sf::Mouse::Button::Right && !getMouseButton(MouseButton::Right))
				m_mouseButtonStates[MOUSE_BUTTON_RIGHT] = ButtonState::JustPressed;
			else if(evt.mouseButton.button == sf::Mouse::Button::Middle && !getMouseButton(MouseButton::Middle))
				m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] = ButtonState::JustPressed;
		}
		else if(evt.type == sf::Event::MouseButtonReleased)
		{
			if(evt.mouseButton.button == sf::Mouse::Button::Left && getMouseButton(MouseButton::Left))
				m_mouseButtonStates[MOUSE_BUTTON_LEFT] = ButtonState::JustReleased;
			else if(evt.mouseButton.button == sf::Mouse::Button::Right && getMouseButton(MouseButton::Right))
				m_mouseButtonStates[MOUSE_BUTTON_RIGHT] = ButtonState::JustReleased;
			else if(evt.mouseButton.button == sf::Mouse::Button::Middle && getMouseButton(MouseButton::Middle))
				m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] = ButtonState::JustReleased;
		}

		if(evt.type == sf::Event::KeyPressed)
		{
			if(evt.key.code >= 0 && evt.key.code < sf::Keyboard::KeyCount && !getKey(evt.key.code))
				m_keyStates[evt.key.code] = ButtonState::JustPressed;
		}
		else if(evt.type == sf::Event::KeyReleased)
		{
			if(evt.key.code >= 0 && evt.key.code < sf::Keyboard::KeyCount && getKey(evt.key.code))
				m_keyStates[evt.key.code] = ButtonState::JustReleased;
		}
	});
}

sf::Vector2i InputManager::getMousePosition() const
{
	return sf::Mouse::getPosition();
}

bool InputManager::getMouseButton(MouseButton mouseButton) const
{
	if (mouseButton == MouseButton::Left)
	{
		return m_mouseButtonStates[MOUSE_BUTTON_LEFT] == ButtonState::Pressed ||
			m_mouseButtonStates[MOUSE_BUTTON_LEFT] == ButtonState::JustPressed;
	}
	else if (mouseButton == MouseButton::Right)
	{
		return m_mouseButtonStates[MOUSE_BUTTON_RIGHT] == ButtonState::Pressed ||
			m_mouseButtonStates[MOUSE_BUTTON_RIGHT] == ButtonState::JustPressed;
	}
	else
	{
		return m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] == ButtonState::Pressed ||
			m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] == ButtonState::JustPressed;
	}
}

bool InputManager::getMouseButtonDown(MouseButton mouseButton) const
{
	if (mouseButton == MouseButton::Left)
		return m_mouseButtonStates[MOUSE_BUTTON_LEFT] == ButtonState::JustPressed;
	else if (mouseButton == MouseButton::Right)
		return m_mouseButtonStates[MOUSE_BUTTON_RIGHT] == ButtonState::JustPressed;
	else
		return m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] == ButtonState::JustPressed;
}

bool InputManager::getMouseButtonUp(MouseButton mouseButton) const
{
	if (mouseButton == MouseButton::Left)
		return m_mouseButtonStates[MOUSE_BUTTON_LEFT] == ButtonState::JustReleased;
	else if (mouseButton == MouseButton::Right)
		return m_mouseButtonStates[MOUSE_BUTTON_RIGHT] == ButtonState::JustReleased;
	else
		return m_mouseButtonStates[MOUSE_BUTTON_MIDDLE] == ButtonState::JustReleased;
}

bool InputManager::getKey(sf::Keyboard::Key key) const
{
	if (key >= 0 && key < sf::Keyboard::KeyCount)
		return m_keyStates[key] == ButtonState::Pressed || m_keyStates[key] == ButtonState::JustPressed;
	else
		return false;
}

bool InputManager::getKeyDown(sf::Keyboard::Key key) const
{
	if (key >= 0 && key < sf::Keyboard::KeyCount)
		return m_keyStates[key] == ButtonState::JustPressed;
	else
		return false;
}

bool InputManager::getKeyUp(sf::Keyboard::Key key) const
{
	if (key >= 0 && key < sf::Keyboard::KeyCount)
		return m_keyStates[key] == ButtonState::JustReleased;
	else
		return false;
}
