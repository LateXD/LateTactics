#include "MainMenu.h"


MainMenu::MainMenu(Game* g)
{
	game = g;
}


MainMenu::~MainMenu()
{

}

void MainMenu::onInitialize()
{
	// Making menuboxes
	//-------------------------
	menuSelectionBox.setFillColor(sf::Color::White);
	menuSelectionBox.setOutlineColor(sf::Color::Black);
	menuSelectionBox.setOutlineThickness(1);
	menuSelectionBox.setSize(sf::Vector2f(game->window.getSize().x / 2, game->window.getSize().y / 2 / numberOfMenuBoxes));
	menuSelectionBox.setOrigin(menuSelectionBox.getSize().x / 2, menuSelectionBox.getSize().y / 6);
	menuSelectionBox.setPosition(game->window.getSize().x / 2, menuSelectionBox.getSize().y / 1.5);
	for (int i = 0; i < numberOfMenuBoxes; i++)
	{
		menuSelectionBoxes.push_back(menuSelectionBox);
		menuSelectionBox.move(0, menuSelectionBox.getSize().y * 2);
	}
	menuSelectionBoxes[currentBox].setFillColor(sf::Color::Green);

	// Making text
	//-------------------------
	font.loadFromFile("..\\Graphics\\Arctik5.ttf");
	text.setFont(font);
	text.setCharacterSize(menuSelectionBoxes[0].getSize().y);
	text.setColor(sf::Color::Black);

	text.setString("Play");
	text.setPosition(menuSelectionBoxes[0].getPosition().x, menuSelectionBoxes[0].getPosition().y);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	menuText.push_back(text);

	text.setString("Map Editor");
	text.move(0, menuSelectionBox.getSize().y * 2);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	menuText.push_back(text);

	text.setString("Exit");
	text.move(0, menuSelectionBox.getSize().y * 2);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	menuText.push_back(text);
}

void MainMenu::handleInput()
{
	// Going up and down on menu screen
	//-------------------------
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		menuSelectionBoxes[currentBox].setFillColor(sf::Color::White);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentBox > 0)
		{
			currentBox--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentBox < numberOfMenuBoxes - 1)
		{
			currentBox++;
		}
		menuSelectionBoxes[currentBox].setFillColor(sf::Color::Green);
	}

	// Selecting something on menu screen
	//-------------------------
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if (currentBox == 0)
		{
			// Not ready yet
		}
		else if (currentBox == 1)
		{
			game->pushState(new MapEditor(game));
		}
		else if (currentBox == 2)
		{
			game->window.close();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mouse = sf::Mouse::getPosition();
		for (int i = 0; i < menuSelectionBoxes.size(); i++)
		{			
			if (mouse.x > menuSelectionBoxes[i].getPosition().x - menuSelectionBoxes[i].getGlobalBounds().width / 2 && mouse.x < menuSelectionBoxes[i].getPosition().x + menuSelectionBoxes[i].getGlobalBounds().width / 2 &&
				mouse.y > menuSelectionBoxes[i].getPosition().y - menuSelectionBoxes[i].getGlobalBounds().height / 6 && mouse.y < menuSelectionBoxes[i].getPosition().y + menuSelectionBoxes[i].getGlobalBounds().height - menuSelectionBoxes[i].getGlobalBounds().height / 6)
			{
				if (i == 0)
				{
					// Not ready yet
				}
				else if (i == 1)
				{
					game->pushState(new MapEditor(game));
				}
				else if (i == 2)
				{
					game->window.close();
				}
			}
		}
	}
}

void MainMenu::update(const float dt)
{
	if (game->loadMap)
	{
		game->pushState(new MapEditor(game));
	}
}

void MainMenu::draw(const float dt)
{
	for (int i = 0; i < numberOfMenuBoxes; i++)
	{
		game->window.draw(menuSelectionBoxes[i]);
	}
	game->window.draw(menuSelectionBox);

	for (int i = 0; i < menuText.size(); i++)
	{
		game->window.draw(menuText[i]);
	}
}
