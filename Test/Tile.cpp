#include <windows.h>	
#include <glut.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include "imagem.h"
#include "Tile.h"

using namespace std;

Tile::Tile(void)
{
}

void Tile::load(char *nome, int tamTileX, int tamTileY)
{
	tamx = tamTileX;
	tamy = tamTileY;

	imgTiles.load(nome);

	//monta array de imagems para os tiles
	tile = new imagem[(imgTiles.width/tamx)*(imgTiles.height/tamy)];

	//recorta os tiles
	for(int y = 0; y < imgTiles.height/tamy; y++)
	{
		for(int x = 0; x < imgTiles.width/tamx; x++)
		{
			imgTiles.cut(x*tamx, y*tamy, tamx, tamy);
			putTile(x+y*imgTiles.width/tamx);
		}

	}
	
}

void Tile::putTile(int pos)
{
	tile[pos].setSize(tamx, tamy);
	for(int y = 0; y < tamy; y++)
	{
		for(int x = 0; x < tamx; x++)
		{
			rgba = imgTiles.getPixelRec(x, y);
			tile[pos].setRGB(x, y, rgba);
		}
	}
}

Tile::~Tile(void)
{
}
