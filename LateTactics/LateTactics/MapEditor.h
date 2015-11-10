#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "GameState.h"
#include "Map.h"

class MapEditor : public GameState
{
public:
	MapEditor(Game* g);
	~MapEditor();

	void onInitialize();
	void handleInput();
	void update(const float dt);
	void draw(const float dt);

	void updateLayer();
	void switchLayer();
	void emptyLayer();

private:
	Map *map;
	int currentLayerNumber = 0, layersShown, spriteNum, currentTool = 1;
	sf::Vector2f mouse;
	sf::Vector3i mapSize = { 20, 20, 20 }; // Keep mapSize.x and mapSize.y as the same number to avoid problems with rotation
	sf::RectangleShape currentToolMark;
	sf::Sprite hiddenTile, topTile, bottomTile, tileBox;
	sf::Texture texture;
	sf::View isometricView, layerView, interfaceView;
	std::vector<sf::Sprite> toolBar;
	std::vector<std::vector<sf::Sprite>> currentLayer;
};

#endif