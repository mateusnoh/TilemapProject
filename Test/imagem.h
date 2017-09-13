#pragma once
class imagem
{
public:
	
	char buffer[256];
	int com, maxColor;
	int red, green, blue, alpha;
	//pixels imagem total
	int *pixels;
	//pixels imagem recorte
	int *pixelsRec;
	int width, height;
	int widthRec, heightRec;
	int positionX, positionY;

	bool rec;

	int posMin, posMax;

	int x2, y2, w2, h2;

	void setRGB(int x, int y, int rgba)
	{
		pixels[x + y * width] = rgba;
	}
	
	void setRGBRec(int x, int y, int rgba)
	{
		pixelsRec[x + y * widthRec] = rgba;
	}

	int getPixel(int x, int y)
	{
		return pixels[x+y*width];
	}

	//retorna pixels do recorte
	int getPixelRec(int x, int y)
	{
		return pixelsRec[x+y*widthRec];
	}

	void setSize(int x, int y);

	void load(char *nome);
	void draw(int x, int y);
	void cut(int posx, int posy, int tamx, int tamy);
	bool collide(imagem *a);

	imagem(void);
	~imagem(void);
};

