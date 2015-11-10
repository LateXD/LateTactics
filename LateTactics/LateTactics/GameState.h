#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

class GameState
{
public:
	GameState();
	~GameState();

	void initialize();

	virtual void draw(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void handleInput() = 0;

	Game* game;

private:
	bool initialized;

protected:
	virtual void onInitialize();
};

#endif