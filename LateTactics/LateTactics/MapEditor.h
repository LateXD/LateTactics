#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "GameState.h"
#include "Map.h"

#include <fstream>
#include <stack>


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
	void storeToStack(int x, int y);
	void undoOrRedo(bool undo);

private:
	Map *map;
	bool onionSkin = false;
	int currentLayerNumber = 0, layersShown, spriteNum, currentTool = 1, currentPaintTool = 1, numberOfPaintTools = 5, numberOfFileTools = 7;
	sf::Vector2f mouse;
	sf::Vector2i viewZooms = { 0, 0 };
	sf::Vector3i mapSize = { 30, 30, 30 }; // Keep mapSize.x and mapSize.y as the same number to avoid problems with rotation
	sf::RectangleShape currentToolMark, layersShownBox, tileToolBackground;
	sf::Sprite hiddenTile, topTile, bottomTile, tileBox, paintTool, fileTool;
	sf::Texture texture, paintToolTexture, fileToolTexture;
	sf::View isometricView, layerView, interfaceView;
	std::vector<sf::Sprite> toolBar, fileToolBar, paintToolBar;
	std::vector<sf::RectangleShape> layersShownBoxes;
	std::vector<std::vector<sf::Sprite>> currentLayer, lowerLayer;
	std::deque<std::vector<int>> undoDeque, redoDeque;
};

#endif