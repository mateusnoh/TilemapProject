#include <windows.h>	
#include <glut.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <string>
#include "imagem.h"

using namespace std;


imagem::imagem(void)
{
	rec = false;
}

void imagem::load(char *nome)
{
	ifstream img;
    //carregar arquivo ptm
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	img.open(nome);
	if (!img.is_open())
	{
	cout << "N abriu " << nome << endl;
	}
	img >> buffer >> width >> height >> com >> maxColor;
	pixels = new int[width*height];

	srand((unsigned int)time(NULL));
	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			img >> red >> green >> blue >> alpha;
			if(red == 255 && green == 0 && blue == 255)
			{
				alpha = 0;
			}
			int rgba = (alpha << 24) | (red << 16) | (green << 8) | blue;
			setRGB(x, y, rgba);
		}
	}
	img.close();
}

void imagem::draw(int x, int y)
{
	// Use Window coordinates to set raster position
	positionX = x;
	positionY = y;

	glRasterPos2i(positionX, positionY+height);
    // Draw the pixmap
	if(!rec)
	{
		glDrawPixels(width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);
	}

	//recorte
	if(rec)
	{
		glDrawPixels(widthRec, heightRec, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixelsRec);
	}
}

bool imagem::collide(imagem *a)
{
	x2 = a->positionX;
	y2 = a->positionY;
	w2 = a->width;
	h2 = a->height;

	return (!( ((positionX)>=(x2)+(w2)) || ((x2)>=(positionX)+(width)) || ((positionY)>=(y2)+(h2)) || ((y2)>=(positionY)+(height)) ));
}

void imagem::cut(int posx, int posy, int tamx, int tamy)
{
	//recorte de imagem
	if(!rec)
	{
		widthRec = tamx;
		heightRec = tamy;
		pixelsRec = new int[widthRec*heightRec];
		rec = true;
	}

	for(int y = posy; y < posy+tamy; y++)
	{
		for(int x = posx; x < posx+tamx; x++)
		{
			
			int rgba = getPixel(x, y);
			setRGBRec(x-posx,y-posy,rgba);
		}
	}

}

void imagem::setSize(int x, int y)
{
	//iniciar imagem vazia
		pixels = new int[x*y];
		width = x;
		height = y;
		for(int j=0; j<height; j++)
	{
		for(int i=0; i<width; i++)
		{
			int rgba = (0 << 24) | (0 << 16) | (0 << 8) | 0;
			setRGB(i, j, rgba);
		}
	}
}
imagem::~imagem(void)
{
	delete[] pixels;
}
