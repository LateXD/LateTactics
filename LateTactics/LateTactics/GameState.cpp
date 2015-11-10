#include "GameState.h"


GameState::GameState()
{
	initialized = false;
}

GameState::~GameState()
{

}

void GameState::onInitialize()
{

}

void GameState::initialize()
{
	if (initialized)
	{
		return;
	}
	onInitialize();
	initialized = true;
}

