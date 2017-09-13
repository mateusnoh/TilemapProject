#include <windows.h>	
#include <glut.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include "imagem.h"
#include "Tile.h"
#include "TileSet.h"
#include "TileMap.h"

using namespace std;

TileMap::TileMap(void)
{
}

void TileMap::loadMap(char *nameTile, int tamTileX, int tamTileY, char *nameTileSet)
{
	//carrega tiles
	t.load(nameTile, tamTileX, tamTileY);
	//carrega tile set
	ts.load(nameTileSet);

	//cria imagem vazia
	mapa.setSize(t.getTileSizeX()*ts.getQntX(), t.getTileSizeY()*ts.getQntY());

	//colocar tiles na imagem vazia
	for(int y = 0; y < ts.getQntY(); y++)
	{
		for(int x = 0; x < ts.getQntX(); x++)
		{
			//mapa normal
			//putTile(x*t.getTileSizeX(), y*t.getTileSizeY(), ts.getId(x, y));

			//posição para mapa isométrico diamante
			posMapx = (x*(tamTileX/2))+(y*(tamTileX/2));
			//posição em y não está totalmente correta
			posMapy = 160+(tamTileY*2)+(x*(tamTileY/2))-(y*(tamTileY/2));

			//por tile na imagem
			putTile(posMapx, posMapy, ts.getId(x, y));
		}
	}
}

void TileMap::putTile(int posx, int posy, int idTile)
{
	for(int y = 0; y < t.getTileSizeY(); y++)
	{
		for(int x = 0; x < t.getTileSizeX(); x++)
		{
			rgba = t.tile[idTile-1].getPixel(x, y);
			alpha = rgba >> 24 & 0xff;
			if(alpha != 0)
			{
				mapa.setRGB(posx+x, posy+y, rgba);
			}
		}
	}
}

void TileMap::drawMap(int x, int y)
{
	mapa.draw(x, y);
}

bool TileMap::isWalkable(int coordTile, int tileWalkable)
{
	//id Tile
	if(ts.idTile[coordTile] == tileWalkable)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TileMap::~TileMap(void)
{
}
