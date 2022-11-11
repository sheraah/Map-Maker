#include "Game.h"

//constructor that creates the window
Game::Game(const sf::VideoMode& Resolution, const sf::String& AppName)
{
	m_Window.create(Resolution, AppName, sf::Style::Close);

	initVariables();
}

//destructor 
Game::~Game()
{

}

//initalize variables for the game object
void Game::initVariables()
{
	m_MapMaker.init(&m_Window);
}

//update the events
void Game::pollEvent()
{
	sf::Event evnt;

	while (m_Window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed) m_Window.close();

		m_MapMaker.pollEvents(evnt);
	}
}

//update the game
void Game::update(const float& dt)
{
	m_MapMaker.update(dt);
}

//render the game
void Game::render()
{
	m_Window.clear();

	m_MapMaker.draw();

	m_Window.display();
}

//runs the game with a loop
void Game::run()
{
	while (m_Window.isOpen())
	{
		const float deltaTime = m_Clock.restart().asSeconds();

		pollEvent();

		update(deltaTime);

		render();
	}
}
