#pragma once

#include <memory>
#include <SFML\Graphics.hpp>
#include "MenuStackFlags.h"

namespace tetris
{
	class ResourceCache;
	
	namespace ui
	{
		class MenuStateMachine;

		class MenuState : public sf::NonCopyable
		{
		protected:
			std::weak_ptr<MenuStateMachine> m_stateMachine;
			bool m_isHidden;
			bool m_hasFocus;

		public:
			MenuState(std::weak_ptr<MenuStateMachine> stateMachine);
			virtual ~MenuState() {}

			virtual bool create(ResourceCache &resourceCache) = 0;
			virtual void onUpdate(float deltaTime) = 0;
			virtual void onRender() = 0;
			virtual std::string getID() const = 0;
			virtual MenuStackFlags getStackFlags() const = 0;

			virtual void onEnter();
			virtual void onExit();
			virtual void onFocusEnter();
			virtual void onFocusExit();
			virtual void onShow();
			virtual void onHide();
			bool isHidden() const;
			bool hasFocus() const;
		};
	}
}