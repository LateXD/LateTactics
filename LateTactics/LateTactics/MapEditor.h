#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "GameState.h"
#include "Map.h"

#include <fstream>

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
	void copyLayer();
	void paintBucket(int x, int y, int tool);
	void saveMap();

private:
	Map *map;
	int currentLayerNumber = 0, layersShown, spriteNum, currentTool = 1, currentPaintTool = 1;
	sf::Vector2f mouse;
	sf::Vector3i mapSize = { 20, 20, 20 }; // Keep mapSize.x and mapSize.y as the same number to avoid problems with rotation
	sf::RectangleShape currentToolMark, currentPaintToolMark, layersShownBox;
	sf::Sprite hiddenTile, topTile, bottomTile, tileBox, paintTools;
	sf::Texture texture, paintToolTexture;
	sf::View isometricView, layerView, interfaceView;
	std::vector<sf::Sprite> toolBar;
	std::vector<sf::RectangleShape> layersShownBoxes;
	std::vector<std::vector<sf::Sprite>> currentLayer;
};

#endif