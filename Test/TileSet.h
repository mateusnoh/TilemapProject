#pragma once
class TileSet
{
public:

	int qntx, qnty;
	int *idTile;

	void load(char *nome);

	int getQntX()
	{
		return qntx;
	}

	int getQntY()
	{
		return qnty;
	}

	int getId(int posx, int posy)
	{
		return idTile[posx+posy*qntx];
	}

	TileSet(void);
	~TileSet(void);
};

