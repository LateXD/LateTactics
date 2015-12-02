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
	void pushToDeque();
	void undo();
	void redo();
	void rotateToUndo(bool rotated);

private:
	Map *map;
	bool onionSkin = false, zoomCurrentLayer = false, mapChanged = true, switchedLayer = false;
	int currentLayerNumber = 0, layersShown, spriteNum, currentTool = 1, currentPaintTool = 1, numberOfPaintTools = 6, numberOfFileTools = 7, currentUndo = 0, currentRotation = 0, rotation = 0;
	sf::Vector2f mouse;
	sf::Vector2i viewZooms = { 0, 0 };
	sf::Vector3i mapSize = { 20, 20, 20 }; // Keep mapSize.x and mapSize.y as the same number to avoid problems with rotation
	sf::RectangleShape currentToolMark, layersShownBox, tileToolBackground;
	sf::Sprite hiddenTile, topTile, bottomTile, tileBox, paintTool, fileTool;
	sf::Texture texture, paintToolTexture, fileToolTexture;
	sf::View isometricView, layerView, interfaceView;
	std::vector<sf::Sprite> toolBar, fileToolBar, paintToolBar;
	std::vector<sf::RectangleShape> layersShownBoxes;
	std::vector<std::vector<sf::Sprite>> currentLayer, lowerLayer;
	std::vector<std::vector<int>>layerChanges;
	std::deque<std::vector<std::vector<int>>>undoRedoDeque;
	std::deque<int>undoRedoLayer;
};

#endif