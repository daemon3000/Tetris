#pragma once

#include <SFML/Graphics.hpp>

namespace tetris
{
	enum class ButtonState
	{
		Pressed, JustPressed, Released, JustReleased
	};

	enum class MouseButton
	{
		Left, Right, Middle
	};

	class EventManager;

	class InputManager : sf::NonCopyable
	{
		static const int MOUSE_BUTTON_LEFT = 0;
		static const int MOUSE_BUTTON_RIGHT = 1;
		static const int MOUSE_BUTTON_MIDDLE = 2;
		static const int MOUSE_BUTTON_COUNT = 3;

		ButtonState m_mouseButtonStates[MOUSE_BUTTON_COUNT];
		ButtonState m_keyStates[sf::Keyboard::KeyCount];

	public:
		InputManager();
		~InputManager() { }

		void update(const EventManager &eventManager);
		sf::Vector2i getMousePosition() const;
		bool getMouseButton(MouseButton mouseButton) const;
		bool getMouseButtonDown(MouseButton mouseButton) const;
		bool getMouseButtonUp(MouseButton mouseButton) const;
		bool getKey(sf::Keyboard::Key key) const;
		bool getKeyDown(sf::Keyboard::Key key) const;
		bool getKeyUp(sf::Keyboard::Key key) const;
	};
}
