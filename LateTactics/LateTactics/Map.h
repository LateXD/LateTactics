#ifndef MAP_H
#define MAP_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdlib.h> 
#include <fstream>

class Map
{
public:
	Map(sf::Vector3i size);
	~Map();

	void rotateMapClockwise();
	void rotateMapCounterClockwise();
	void setTextureRect(int xPos, int yPos, int zPos, int textureNumber);
	void loadMap();

	int getTextureNumber(int xPos, int yPos, int zPos);
	int getAmountOfTextures();
	sf::Vector2i getPictureSize();
	sf::Vector3i getMapSize();
	sf::Vector2f getSpritePosition(int xPos, int yPos, int zPos);
	sf::IntRect getTextureRect(int xPos, int yPos, int zPos);
	sf::Sprite getSprite(int xPos, int yPos, int zPos);
	sf::Sprite getTransparentTile();

private:
	int amountOfTextures = 10, scale = 1;
	sf::Vector2i pictureSize;
	sf::Vector3i mapSize, mapFix, spriteMovement = { 14, 7, 8 };
	sf::Sprite tileSprite;
	sf::Texture texture;
	std::vector<std::vector<std::vector<sf::Sprite>>>tiles, tileMemory;
};

#endif