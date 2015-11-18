#ifndef GAME_H
#define GAME_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <stack>
#include <time.h>
#include <ctime>

class GameState;

class Game
{
public:
	Game();
	~Game();

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();
	void gameLoop();

	sf::Event event;
	sf::RenderWindow window;
	std::stack<GameState*> states;

	bool loadMap = false;
};

#endif
