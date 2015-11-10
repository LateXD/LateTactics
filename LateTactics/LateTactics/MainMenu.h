#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameState.h"
#include "MapEditor.h"

class MainMenu : public GameState
{
public:
	MainMenu(Game* g);
	~MainMenu();

	void onInitialize();
	void handleInput();
	void update(const float dt);
	void draw(const float dt);

private:
	int numberOfMenuBoxes = 3, currentBox = 0;
	sf::Font font;
	sf::RectangleShape menuSelectionBox;
	sf::Text text;
	std::vector<sf::RectangleShape>menuSelectionBoxes;
	std::vector<sf::Text>menuText;
};

#endif