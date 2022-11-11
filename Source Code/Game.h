#pragma once
#include "MapMaker.h"

class Game
{
private:
	//member variables
	sf::RenderWindow m_Window;
	MapMaker m_MapMaker;
	sf::Clock m_Clock;

	//member functions
	void initVariables();
	void pollEvent();
	void update(const float& dt);
	void render();

public:
	Game(const sf::VideoMode& Resolution, const sf::String& AppName);
	~Game();
	void run();
};

