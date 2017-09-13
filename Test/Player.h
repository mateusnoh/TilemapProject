#pragma once
class Player
{
public:
	imagem pl;
	imagem mark[11];
	int markX[11];
	int markY[11];

	int contMark;

	int plx, ply,posX_final,posY_final;
	int posTile;
	bool stopWalkUp,stopWalkDown,stopWalkLeft,stopWalkRight;
	void load(char *nome, int pt);
	void draw();
	void moveCharacter(char *dir, TileMap *m);
	void updateCharacter();
	void addMark();
	void drawMark();
	int getMark();
	void resetPlayer();
	Player(void);
	~Player(void);
};

