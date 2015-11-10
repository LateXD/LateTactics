#include "Game.h"
#include "GameState.h"

Game::Game()
{
	window.create(sf::VideoMode::getDesktopMode(), "Tactics", sf::Style::None);
	window.setFramerateLimit(60);
}

Game::~Game()
{
	while (!states.empty())
	{
		popState();
	}
}

void Game::pushState(GameState* state)
{
	state->initialize();
	states.push(state);
	return;
}

void Game::popState()
{
	delete states.top();
	states.pop();
	return;
}

void Game::changeState(GameState* state)
{
	if (!states.empty())
	{
		popState();
	}
	pushState(state);
	return;
}

GameState* Game::peekState()
{
	if (states.empty())
	{
		return nullptr;
	}
	return states.top();
}

void Game::gameLoop()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
		{
			continue;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			peekState()->handleInput();
		}
		peekState()->update(dt);
		window.clear(sf::Color::White);
		peekState()->draw(dt);
		window.display();
	}
}