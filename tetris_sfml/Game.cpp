#include "Game.h"
#include "Scene.h"

using namespace tetris;

Game::Game() :
	m_scene(nullptr),
	m_sceneToLoad(nullptr)
{
}

bool Game::startup()
{
	return true;
}

void Game::fixedUpdate()
{
	
}

void Game::update(float deltaTime)
{
	if(m_sceneToLoad)
	{
		m_scene = m_sceneToLoad;
		m_sceneToLoad = nullptr;

		if(!m_scene->create())
			m_scene = nullptr;
	}

	if(m_scene)
	{
		m_scene->update(deltaTime);
	}
}

void Game::render(float deltaTime)
{
	if(m_scene)
	{
		m_scene->render(deltaTime);
	}
}

void Game::shutdown()
{
}

void Game::setScene(std::shared_ptr<Scene> scene)
{
	m_sceneToLoad = scene;
}
