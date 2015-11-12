#include "Map.h"


Map::Map(sf::Vector3i size)
{
	// Loads tiletextures and sets rectangle to 0 (no texture)
	//-------------------------
	mapSize = size;
	texture.loadFromFile("..\\Graphics\\Tiles.png");
	pictureSize = sf::Vector2i(texture.getSize().x / amountOfTextures, texture.getSize().y);
	tileSprite.setTexture(texture);
	tileSprite.setTextureRect(sf::IntRect(0 * pictureSize.x, 0, pictureSize.x, pictureSize.y));

	// Making room for sprites
	//-------------------------
	tiles.resize(mapSize.x);
	for (int i = 0; i < mapSize.x; i++)
	{
		tiles[i].resize(mapSize.y);
		for (int j = 0; j < mapSize.y; j++)
		{
			tiles[i][j].resize(mapSize.z);
		}
	}

	// Inserting correct sprites to the 3d map vector
	//-------------------------
	for (int i = 0; i < mapSize.x; i++)
	{
		for (int j = 0; j < mapSize.y; j++)
		{
			mapFix.x = -spriteMovement.x * j;
			mapFix.y = spriteMovement.y * j;

			for (int k = 0; k < mapSize.z; k++)
			{
				mapFix.z = -spriteMovement.z * k;

				tileSprite.setPosition((mapSize.x - 1) * spriteMovement.x + i * spriteMovement.x + mapFix.x, (mapSize.z - 1) * spriteMovement.z + i * spriteMovement.y + mapFix.y + mapFix.z);
				tiles[i][j][k] = tileSprite;
			}
		}
	}
}

Map::~Map()
{
}

void Map::rotateMapClockwise() // Rotates the map by switching textures to the new positions
{
	tileMemory = tiles;
	for (int k = 0; k < mapSize.z; k++)
	{
		for (int j = 0; j < mapSize.y; j++)
		{
			for (int i = 0; i < mapSize.x; i++)
			{
				tileMemory[i][j][k].setTextureRect(tiles[j][mapSize.y - 1 - i][k].getTextureRect());
			}
		}
	}
	tiles = tileMemory;
}

void Map::rotateMapCounterClockwise() // Rotates the map by switching textures to the new positions
{
	tileMemory = tiles;
	for (int k = 0; k < mapSize.z; k++)
	{
		for (int j = 0; j < mapSize.y; j++)
		{
			for (int i = 0; i < mapSize.x; i++)
			{
				tileMemory[i][j][k].setTextureRect(tiles[mapSize.x - 1 - j][i][k].getTextureRect());
			}
		}
	}
	tiles = tileMemory;
}

void Map::setTextureRect(int xPos, int yPos, int zPos, int textureNumber)
{
	tiles[xPos][yPos][zPos].setTextureRect(sf::IntRect(textureNumber * pictureSize.x, 0, pictureSize.x, pictureSize.y));
}

void Map::loadMap()
{
	int mapData, position;
	std::vector<int>mapDataVector;
	std::ifstream myMap("..\\CustomMaps\\Map.txt");
	if (myMap.is_open())
	{	
		while (myMap >> mapData)
		{
			mapDataVector.push_back(mapData);
			if (myMap.peek())
			{
				myMap.ignore();
			}
		}

		mapSize.x = mapDataVector[0];
		mapSize.y = mapDataVector[1];
		mapSize.z = mapDataVector[2];

		tiles.resize(mapSize.x);
		for (int i = 0; i < mapSize.x; i++)
		{
			tiles[i].resize(mapSize.y);
			for (int j = 0; j < mapSize.y; j++)
			{
				tiles[i][j].resize(mapSize.z);
			}
		}

		position = 3;
		for (int i = 0; i < mapSize.x; i++)
		{
			for (int j = 0; j < mapSize.y; j++)
			{
				for (int k = 0; k < mapSize.z; k++)
				{
					setTextureRect(i, j, k, mapDataVector[mapData]);
					mapData++;
				}
			}
		}

		myMap.close();
	}
	else
	{
		std::cout << "Map file couldn't be loaded." << std::endl;
	}
}

int Map::getTextureNumber(int xPos, int yPos, int zPos)
{
	return tiles[xPos][yPos][zPos].getTextureRect().left / tiles[xPos][yPos][zPos].getTextureRect().width;
}

int Map::getAmountOfTextures()
{
	return amountOfTextures;
}

sf::Vector2i Map::getPictureSize()
{
	return pictureSize;
}

sf::Vector3i Map::getMapSize()
{
	return mapSize;
}

sf::Vector2f Map::getSpritePosition(int xPos, int yPos, int zPos)
{
	return tiles[xPos][yPos][zPos].getPosition();
}

sf::IntRect Map::getTextureRect(int xPos, int yPos, int zPos)
{
	return tiles[xPos][yPos][zPos].getTextureRect();
}

sf::Sprite Map::getSprite(int xPos, int yPos, int zPos)
{
	return tiles[xPos][yPos][zPos];
}

sf::Sprite Map::getTransparentTile() // Used for showing if there is a block on top of another block when the upper layer is hidden
{
	tileSprite.setTextureRect(sf::IntRect((amountOfTextures - 1) * pictureSize.x, 0, pictureSize.x, pictureSize.y));
	tileSprite.setColor(sf::Color(0, 0, 0, 200));
	return tileSprite;
}