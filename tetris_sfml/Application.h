#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "ApplicationSettings.h"
#include "InputManager.h"
#include "EventManager.h"

namespace tetris
{
	class ApplicationListener;

	class Application : sf::NonCopyable
	{
		std::shared_ptr<EventManager> m_eventManager;
		std::shared_ptr<InputManager> m_inputManager;
		std::shared_ptr<sf::RenderWindow> m_window;
		sf::Clock m_gameTime;
		sf::Color m_clearColor;
		sf::Vector2i m_windowSize;
		std::string m_windowTitle;
		unsigned int m_windowBPP;
		float m_deltaTime;
		float m_fpsUpdateElapsedTime;
		int m_frames;
		int m_fps;
		bool m_isRunning;
		bool m_isQuiting;

		void init(const ApplicationSettings &appSettings);
		void shutdown();
	public:
		Application();
		~Application();

		void run(ApplicationListener &appListener, const ApplicationSettings &appSettings);
		void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);
		void draw(const sf::Vertex *vertices, size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
		void changeResolution(int width, int height, bool fullscreen);
		void quit();
		void cancelQuit();
		void setView(const sf::View &view);
		const sf::View &getView() const;
		std::shared_ptr<const InputManager> getInputManager() const;
		std::shared_ptr<const EventManager> getEventManager() const;
		std::shared_ptr<sf::RenderWindow> getWindow() const;
		const sf::Clock &getGameTime() const;
		float getDeltaTime() const;
		float getAspect() const;
		int getFPS() const;

		static Application* getInstance();
	};
}
