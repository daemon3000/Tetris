#include <memory>

#include "Application.h"
#include "ApplicationListener.h"
#include "EngineSettings.h"
#include "Math.h"

using namespace tetris;

Application::Application() :
	m_clearColor(0, 0, 0, 255),
	m_windowSize(800, 600),
	m_isRunning(false),
	m_isQuiting(false),
	m_inputManager(std::make_shared<InputManager>()),
	m_eventManager(std::make_shared<EventManager>()),
	m_window(std::make_shared<sf::RenderWindow>())
{
}

Application::~Application()
{
}

void Application::run(ApplicationListener &appListener, const ApplicationSettings &appSettings)
{
	init(appSettings);
	if (!appListener.startup())
	{
		shutdown();
		return;
	}

	sf::Clock updateClock;
	sf::Clock frameClock;
	sf::Int32 updates = 0;
	sf::Int32 maxUpdates = 5;
	sf::Int32 updateTime = 0;
	sf::Int32 nextUpdate = 0;

	nextUpdate = updateClock.getElapsedTime().asMilliseconds();
	m_isRunning = true;
	m_deltaTime = 0.0f;
	m_fpsUpdateElapsedTime = 0.0f;
	m_frames = 0;
	m_fps = 60;
	m_gameTime.restart();

	while (m_isRunning)
	{
		m_window->clear(m_clearColor);
		m_eventManager->update(*m_window);
		m_inputManager->update(*m_eventManager);

		updates = 0;
		updateTime = updateClock.getElapsedTime().asMilliseconds();
		while ((updateTime - nextUpdate) >= kPhysicsUpdateRate && updates < maxUpdates)
		{
			appListener.fixedUpdate();
			nextUpdate += kPhysicsUpdateRate;
		}

		m_deltaTime = frameClock.restart().asSeconds();
		if (m_deltaTime > kMaxDeltaTime)
			m_deltaTime = kMaxDeltaTime;

		m_fpsUpdateElapsedTime += m_deltaTime;
		if (m_fpsUpdateElapsedTime >= kFPSUpdateInterval)
		{
			m_fps = (int)(m_frames / kFPSUpdateInterval);
			m_fpsUpdateElapsedTime = 0.0f;
			m_frames = 0;
		}

		appListener.update(m_deltaTime);
		appListener.render(m_deltaTime);
		m_window->display();

		m_frames++;

		if (m_isQuiting)
			m_isRunning = false;
	}
	appListener.shutdown();

	shutdown();
}

void Application::init(const ApplicationSettings &appSettings)
{
	sf::Uint32 style = appSettings.fullscreen ? sf::Style::Fullscreen : sf::Style::Close;
	
	m_windowTitle = appSettings.title;
	m_windowSize.x = math::max(appSettings.windowSize.x, kMinWindowWidth);
	m_windowSize.y = math::max(appSettings.windowSize.y, kMinWindowHeight);
	m_clearColor = appSettings.backgroundColor;
	m_windowBPP = appSettings.bitsPerPixel;
	m_window->create(sf::VideoMode(m_windowSize.x, m_windowSize.y, m_windowBPP), m_windowTitle, style);
}

void Application::changeResolution(int width, int height, bool fullscreen)
{
	if (width < kMinWindowWidth || height < kMinWindowHeight)
		return;

	sf::Uint32 style = fullscreen ? sf::Style::Fullscreen : sf::Style::Close;
	m_windowSize.x = width;
	m_windowSize.y = height;
	m_window->create(sf::VideoMode(m_windowSize.x, m_windowSize.y, m_windowBPP), m_windowTitle, style);
}

void Application::shutdown()
{
	m_window->close();
}

void Application::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
	m_window->draw(drawable, states);
}

void Application::draw(const sf::Vertex *vertices, size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates &states)
{
	m_window->draw(vertices, vertexCount, type, states);
}

void Application::quit()
{
	m_isQuiting = true;
}

void Application::cancelQuit()
{
	m_isQuiting = false;
}

void Application::setView(const sf::View &view)
{
	m_window->setView(view);
}

const sf::View &Application::getView() const
{
	return m_window->getView();
}

std::shared_ptr<const InputManager> Application::getInputManager() const
{
	return m_inputManager;
}

std::shared_ptr<const EventManager> Application::getEventManager() const
{
	return m_eventManager;
}

std::shared_ptr<sf::RenderWindow> Application::getWindow() const
{
	return m_window;
}

const sf::Clock &Application::getGameTime() const
{
	return m_gameTime;
}

float Application::getDeltaTime() const
{
	return m_deltaTime;
}

float Application::getAspect() const
{
	auto size = m_window->getSize();
	return (float)size.x / (float)size.y;
}

int Application::getFPS() const
{
	return m_fps;
}

Application* Application::getInstance()
{
	static std::unique_ptr<Application> instance(new Application());
	return instance.get();
}
