#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>

namespace tetris
{
	namespace ui
	{
		class MenuState;

		class MenuStateMachine : sf::NonCopyable
		{
			std::vector<std::shared_ptr<MenuState>> m_states;
			std::vector<std::shared_ptr<MenuState>> m_stateStack;
			int m_updateOrderStart;
			int m_renderOrderStart;

			std::shared_ptr<MenuState> findState(const std::string &stateID);
			void calculateUpdateOrder();
			void calculateRenderOrder();
		public:
			MenuStateMachine();

			void registerState(std::shared_ptr<MenuState> state);
			void update(float deltaTime);
			void render();
			void changeState(const std::string &stateID);
			void pushState(const std::string &stateID);
			void popState(const std::string &stateID);
			void clearAll();
		};
	}
}