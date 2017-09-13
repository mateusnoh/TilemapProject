#include <iostream>
#include <fstream>
#include "imagem.h"
#include "Tile.h"
#include "TileSet.h"

using namespace std;

TileSet::TileSet(void)
{
}

void TileSet::load(char *nome)
{
	ifstream mapSet;
	mapSet.open(nome);
	mapSet >> qntx >> qnty;

	//cria array do pela quantidade de tiles no mapa
	idTile = new int[qntx*qnty];

	for(int y = 0; y < qnty; y++)
	{
		for(int x = 0; x < qntx; x++)
		{
			//grava ID dos tiles no array
			mapSet >> idTile[x+y*qntx];
		}
	}

}

TileSet::~TileSet(void)
{
}
