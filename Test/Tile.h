#pragma once
class Tile
{
public:
	int *id;
	int rgba;
	int tamx, tamy;

	imagem imgTiles;
	imagem *tile;

	void load(char *nome, int tamTileX, int tamTileY);
	
	//tamanho do tile em X
	int getTileSizeX()
	{
		return tamx;
	}

	//tamanho do tile em Y
	int getTileSizeY()
	{
		return tamy;
	}

	void putTile(int pos);

	Tile(void);
	~Tile(void);
};

