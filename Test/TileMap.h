#include "Tile.h"
#include "TileSet.h"

#pragma once
class TileMap
{
public:

	imagem mapa;
	int rgba;
	int alpha;
	int posMapx, posMapy;

	Tile t;
	TileSet ts;

	void loadMap(char *nameTile, int tamTileX, int tamTileY, char *nameTileSet);
	void drawMap(int x, int y);
	void putTile(int posx, int posy, int idTile);
	bool isWalkable(int coordTile, int tileWalkable);

	TileMap(void);
	~TileMap(void);
};

