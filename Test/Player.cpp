#include <iostream>
#include "imagem.h"
#include "TileMap.h"
#include "Player.h"

using namespace std;

Player::Player(void)
{
}

void Player::load(char *nome, int pt)
{
	pl.load(nome);
	posTile = pt;
	plx=448;
	ply=92;
	stopWalkUp = true;
	stopWalkLeft = true;
	stopWalkDown = true;
	stopWalkRight = true;

	for(int i = 0; i < 10; i++)
	{
		mark[i].load("mark.ptm");
	}
	contMark = 0;
}

void Player::resetPlayer()
{
	posTile = 18;
	plx=448;
	ply=92;
	stopWalkUp = true;
	stopWalkLeft = true;
	stopWalkDown = true;
	stopWalkRight = true;
	contMark = 0;
}

void Player::draw()
{
	pl.draw(plx, ply);
}

void Player::updateCharacter() // @@@ Criei uma função  UpdateChar pra poder incrementar o X e o Y e fazer o personagem andar suave de tile pra tile. Ela vai incrementando x e y até chegar na posição definida na hora que o movimento foi iniciado
{
		if (stopWalkUp == false)
		{

			if (plx < posX_final)
			{
				plx++;
			}
			if (ply < posY_final)
			{
				ply++;
			}
			if (ply == posY_final && plx == posX_final)
			{
				stopWalkUp = true;
			}
		}
				if (stopWalkLeft == false)
		{

			if (plx > posX_final)
			{
				plx--;
			}
			if (ply < posY_final)
			{
				ply++;
			}
			if (ply == posY_final && plx == posX_final)
			{
				stopWalkLeft = true;
			}
		}
				if (stopWalkDown == false)
		{

			if (plx > posX_final)
			{
				plx--;
			}
			if (ply > posY_final)
			{
				ply--;
			}
			if (ply == posY_final && plx == posX_final)
			{
				stopWalkDown = true;
			}
		}

				if (stopWalkRight == false)
		{

			if (plx < posX_final)
			{
				plx++;
			}
			if (ply > posY_final)
			{
				ply--;
			}
			if (ply == posY_final && plx == posX_final)
			{
				stopWalkRight = true;
			}
		}

}

void Player::moveCharacter(char *dir, TileMap *m) // @@@ Mudei um pouco o moveCharacter pra poder utilizar o UpdateChar que fiz acima, a diferença é que agora ao invés de mover o personagem, essa função define pra qual posição o personagem deve ir e libera a bool StopWalk pro UpdateChar funcionar.
{
	//int posX_final,posY_final;
	if(dir == "up")
	{
		if(m->isWalkable(posTile+15, 1))
		{
			//quantidade tiles em x
			posTile+=15;

			posX_final = plx + 32;
			posY_final = ply + 16;
			stopWalkUp = false;
			
		}
		//dir = "l";
	}

		if(dir == "left")
	{
		if(m->isWalkable(posTile-1, 1))
		{
			//quantidade tiles em x
			posTile--;
			posX_final = plx - 32;
			posY_final = ply + 16;
			stopWalkLeft = false;
		}
	}
				if(dir == "down")
	{
		if(m->isWalkable(posTile-15, 1))
		{
			//quantidade tiles em x
			posTile-=15;
			posX_final = plx - 32;
			posY_final = ply - 16;
			stopWalkDown = false;
		}
	}
				if(dir == "right")
	{
		if(m->isWalkable(posTile+1, 1))
		{
			//quantidade tiles em x
			posTile++;
			posX_final = plx + 32;
			posY_final = ply - 16;
			stopWalkRight = false;
		}
	}
}

void Player::drawMark()
{
	if(contMark >= 0)
	{
		mark[0].draw(448, 92);
	}

	if(contMark >= 1)
	{
		mark[1].draw(markX[1], markY[1]);
	}

	if(contMark >= 2)
	{
		mark[2].draw(markX[2], markY[2]);
	}

	if(contMark >= 3)
	{
		mark[3].draw(markX[3], markY[3]);
	}

	if(contMark >= 4)
	{
		mark[4].draw(markX[4], markY[4]);
	}

	if(contMark >= 5)
	{
		mark[5].draw(markX[5], markY[5]);
	}

	if(contMark >= 6)
	{
		mark[6].draw(markX[6], markY[6]);
	}

	if(contMark >= 7)
	{
		mark[7].draw(markX[7], markY[7]);
	}

	if(contMark >= 8)
	{
		mark[8].draw(markX[8], markY[8]);
	}

	if(contMark >= 9)
	{
		mark[9].draw(markX[9], markY[9]);
	}

	if(contMark >= 10)
	{
		mark[10].draw(markX[10], markY[10]);
	}
}

void Player::addMark()
{
	if(contMark < 10)
	{
		contMark++;

		markX[contMark] = plx;
		markY[contMark] = ply;
	}
}

int Player::getMark()
{
	return contMark;
}

Player::~Player(void)
{
}
