#pragma once

#include <memory>
#include "ApplicationListener.h"

namespace tetris
{
	class Scene;

	class Game : public ApplicationListener
	{
		std::shared_ptr<Scene> m_scene;
		std::shared_ptr<Scene> m_sceneToLoad;

	public:
		Game();
		virtual ~Game() {}

		virtual bool startup() override;
		virtual void fixedUpdate() override;
		virtual void update(float deltaTime) override;
		virtual void render(float deltaTime) override;
		virtual void shutdown() override;
		void setScene(std::shared_ptr<Scene> scene);
	};
}