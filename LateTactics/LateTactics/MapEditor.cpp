#include "MapEditor.h"


MapEditor::MapEditor(Game* g)
{
	game = g;
}

MapEditor::~MapEditor()
{
	delete map;
}

void MapEditor::onInitialize()
{
	map = new Map(mapSize);

	// Making of currentLayer which is used to manipulate the map
	//-------------------------
	currentLayer.resize(mapSize.x);
	for (int i = 0; i < mapSize.x; i++)
	{
		currentLayer[i].resize(mapSize.y);
	}
	updateLayer();

	// Making of the area which shows tiles on top and under the tile which is currently pointed
	//-------------------------
	texture.loadFromFile("..\\Graphics\\EditorUpDown.png");
	tileBox.setTexture(texture);
	tileBox.scale(2,2);
	tileBox.setPosition(game->window.getSize().x - tileBox.getGlobalBounds().width, 0);

	topTile = map->getSprite(0, 0, 0);
	topTile.scale(2, 2);
	topTile.setPosition(tileBox.getPosition().x + 5 * topTile.getScale().x, tileBox.getPosition().y + 10 * topTile.getScale().y);
	bottomTile = map->getSprite(0, 0, 0);
	bottomTile.scale(2, 2);
	bottomTile.setPosition(tileBox.getPosition().x + 5 * bottomTile.getScale().x, tileBox.getPosition().y + 44 * bottomTile.getScale().y);

	// Preparing for hiding layers
	//-------------------------
	layersShown = mapSize.z;
	hiddenTile = map->getTransparentTile();

	// Making of texture toolbar
	//-------------------------
	for (int i = 0; i < map->getAmountOfTextures() - 1; i++)
	{
		toolBar.push_back(map->getSprite(0,0,0));
		toolBar[i].scale(2, 2);
		toolBar[i].setPosition(i * (currentLayer[0][0].getGlobalBounds().width + 1) * toolBar[i].getScale().x, game->window.getSize().y - toolBar[i].getGlobalBounds().height);
		toolBar[i].setTextureRect(sf::IntRect(i * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
	}

	currentToolMark.setSize(sf::Vector2f(10, 10));
	currentToolMark.setFillColor(sf::Color::Red);
	currentToolMark.setOutlineColor(sf::Color::Black);
	currentToolMark.setOutlineThickness(1);
	currentToolMark.setPosition(toolBar[currentTool].getPosition());


	// Setting up views
	//-------------------------
	isometricView.setViewport(sf::FloatRect(0,0,0.5,1.0));
	isometricView.setSize(game->window.getSize().x / 2, game->window.getSize().y);
	isometricView.setCenter(map->getSpritePosition(mapSize.x / 2, mapSize.y / 2, 0));
	layerView.setViewport(sf::FloatRect(0.5, 0, 0.5, 1.0));
	layerView.setSize(game->window.getSize().x / 2, game->window.getSize().y);
	layerView.setCenter(currentLayer[mapSize.x / 2][mapSize.y / 2].getPosition());
	interfaceView = game->window.getDefaultView();
}

void MapEditor::handleInput()
{
	// Mouse commands
	//-------------------------
	if (game->event.type == sf::Event::MouseWheelMoved)
	{
		if (game->event.mouseWheel.delta == 1 && currentLayerNumber < mapSize.z - 1)
		{
			currentLayerNumber++;
			switchLayer();
		}
		else if (game->event.mouseWheel.delta == -1 && currentLayerNumber > 0)
		{
			currentLayerNumber--;
			switchLayer();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		emptyLayer();
	}

	// Mouse movements on layerview area
	//-------------------------
	game->window.setView(layerView);
	mouse = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window));

	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			if (mouse.x > currentLayer[i][j].getPosition().x && mouse.x < currentLayer[i][j].getPosition().x + currentLayer[i][j].getGlobalBounds().width &&
				mouse.y > currentLayer[i][j].getPosition().y && mouse.y < currentLayer[i][j].getPosition().y + currentLayer[i][j].getGlobalBounds().height)
			{
				if (currentLayerNumber < mapSize.z - 1)
				{
					topTile.setTextureRect(map->getTextureRect(i, j, currentLayerNumber + 1));
				}
				else
				{
					topTile.setTextureRect(sf::IntRect(0 * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
				}
				if (currentLayerNumber > 0)
				{
					bottomTile.setTextureRect(map->getTextureRect(i, j, currentLayerNumber - 1));
				}
				else
				{
					bottomTile.setTextureRect(sf::IntRect(0 * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					currentLayer[i][j].setTextureRect(sf::IntRect(currentTool * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
					map->setTextureRect(i, j, currentLayerNumber, currentTool);
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					currentLayer[i][j].setTextureRect(sf::IntRect(0 * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
					map->setTextureRect(i, j, currentLayerNumber, 0);
				}
			}
		}
	}

	// Mouse movements on interface area
	//-------------------------
	game->window.setView(interfaceView);
	mouse = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window));

	for (int i = 0; i < toolBar.size(); i++)
	{
		if (mouse.x > toolBar[i].getPosition().x && mouse.x < toolBar[i].getPosition().x + toolBar[i].getGlobalBounds().width &&
			mouse.y >toolBar[i].getPosition().y && mouse.y < toolBar[i].getPosition().y + toolBar[i].getGlobalBounds().height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				currentToolMark.setPosition(toolBar[i].getPosition());
				currentTool = i;
			}
		}
	}

	// Keyboard commands
	//-------------------------
	if (game->event.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			map->rotateMapCounterClockwise();
			updateLayer();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			map->rotateMapClockwise();
			updateLayer();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && layersShown < mapSize.z)
		{
			layersShown++;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && layersShown > 1)
		{
			layersShown--;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game->popState();
		}
	}
}

void MapEditor::update(const float dt)
{
	
}

void MapEditor::draw(const float dt)
{
	// Isometric view
	//-------------------------
	game->window.setView(isometricView);

	for (int i = 0; i < map->getMapSize().x; i++)
	{
		for (int j = 0; j < map->getMapSize().y; j++)
		{
			for (int k = 0; k < layersShown; k++)
			{
				if (map->getTextureNumber(i, j, k) != 0)
				{
					game->window.draw(map->getSprite(i, j, k));
				}
				if (layersShown < mapSize.z && map->getTextureNumber(i, j, k + 1) != 0 && map->getTextureNumber(i, j, k) != 0)
				{
					hiddenTile.setPosition(map->getSpritePosition(i, j, k));
					game->window.draw(hiddenTile);
				}
			}
		}
	}

	// Layer view
	//-------------------------
	game->window.setView(layerView);

	for (int i = 0; i < map->getMapSize().x; i++)
	{
		for (int j = 0; j < map->getMapSize().y; j++)
		{
			game->window.draw(currentLayer[i][j]);
		}
	}

	// Interface view
	//-------------------------
	game->window.setView(interfaceView);

	game->window.draw(tileBox);
	game->window.draw(topTile);
	game->window.draw(bottomTile);
	for (int i = 0; i < toolBar.size(); i++)
	{
		game->window.draw(toolBar[i]);
	}
	game->window.draw(currentToolMark);
}

void MapEditor::updateLayer() // Updates the layer, used while initializing and when the map is rotated
{
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			currentLayer[i][j] = map->getSprite(i, j, currentLayerNumber);
			currentLayer[i][j].setPosition(i * (currentLayer[i][j].getGlobalBounds().width + 1), j * (currentLayer[i][j].getGlobalBounds().height + 1));
		}
	}
}

void MapEditor::switchLayer() // Switches to next layer
{
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			currentLayer[i][j].setTextureRect(map->getTextureRect(i, j, currentLayerNumber));
		}
	}
}

void MapEditor::emptyLayer() // Empties the current layer
{
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			map->setTextureRect(i, j, currentLayerNumber, 0);
			currentLayer[i][j].setTextureRect(sf::IntRect(0 * map->getPictureSize().x, 0, map->getPictureSize().x, map->getPictureSize().y));
		}
	}
}