#include <iostream>
#include <Windows.h>
#include <glut.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>
#include "imagem.h"
#include "TileMap.h"
#include "Player.h"

using namespace std;

int winWidth=960, winHeight=540;

//posição mapa

//mapa
TileMap mapa;

//player
Player player;
imagem telaMenu;
int timer;

bool menu = true;
bool jogo = false;
bool pause = false;
bool over = false;

time_t contador, atual;
int cont;
string tempo;
stringstream ss;

string contMark;

imagem fundoMapa;
imagem telaPause;
imagem telaOver;
imagem tileFinal;

void drawString(float x, float y, void *font, string str) 
{
	glColor3f(0, 0, 0);
	glRasterPos2f(x,y);

	for (string::iterator c = (&str)->begin(); c != (&str)->end(); ++c) 
	{
		glutBitmapCharacter(font, *c);
	}
	glEnd();
}

void ChangeSize(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

	winWidth = w;
	winHeight= h;

    glViewport(0, 0, w, h);
        
	// Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    // Set the clipping volume
    gluOrtho2D(0.0, (GLfloat) w, 0.0, (GLfloat) h);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init (void){
    // Black background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	//carregar mapa
	mapa.loadMap("TilesTest.ptm", 64, 32, "mapSet.txt");

	//carregar player
	player.load("pl.ptm", 28);
	telaMenu.load("menu.ptm"); // @@@ tentei carregar a imagem aqui

	fundoMapa.load("fundoMapa.ptm");
	telaPause.load("pause.ptm");
	telaOver.load("over.ptm");
	tileFinal.load("final.ptm");
}

void finish(void)
{
	/*if(stone != NULL)
		delete(image);*/
}

void update(int value)
{

}

void RenderScene(void){
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glPixelZoom( 1.0, -1.0 );
	//----- TELA MENU
	if (menu == true)
	{

		telaMenu.draw(0,0); // @@@ era pra mostrar a imagem do "menu". O menu teoricamente está funcionando, pois se tu apertar x ele muda pro jogo, porem esta sem imagem, só uma tela branca. Talvez seja por alguma peculiaridade do teu código que não percebi
		contador = time(NULL);
	}
	//----- TELA GAME
	if (jogo == true)
	{
		atual = time(0);
		cont = atual-contador;
		ss << cont;
		ss >> tempo;
		ss.clear();

		ss << player.getMark();
		ss >> contMark;
		ss.clear();
		fundoMapa.draw(0, 0);

		if ( glutGet(GLUT_ELAPSED_TIME)/1000 - timer < 15) // @@@ 5 segundos pra sumir o mapa, o contador começa a contar a partir do momento que tu sai do "MENU", ou seja, quando aperta X pra começar o jogo
		{
			mapa.drawMap(0, 60);
		}

		tileFinal.draw(448, 476);

		if(tileFinal.collide(&player.pl))
		{
			over = true;
			jogo = false;
		}

		player.drawMark();
		player.draw();
		player.updateCharacter(); // @@@ Adicionei updateCharacter aqui pra ele ficar atualizando sempre. Essa RenderScene roda a cada frame pois o PostRedisplay e o SwapBuffers tão no final dela agora

		drawString(400, 25, GLUT_BITMAP_HELVETICA_18, "Tempo: "+tempo);
		drawString(80, 25, GLUT_BITMAP_HELVETICA_18, "Marcas: "+contMark+"/10");

	}
	//----- TELA PAUSE
	if(pause == true)
	{
		telaPause.draw(0, 0);
	}
	//----- TELA OVER
	if(over == true)
	{
		telaOver.draw(0, 0);
		drawString(480, 270, GLUT_BITMAP_HELVETICA_18, "Tempo: "+tempo);
	}

	glutPostRedisplay();
	glutSwapBuffers();
}

void mouse (int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
    {
	
	}

	glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y) {
	switch (key) 
	{
		case 'Q':
		case 'q':
			finish();
			exit(0);
			break;
		case 'R':
		case 'r':
			if(over == true)
			{
				timer = 0;
				bool menu = true;
				bool jogo = false;
				bool pause = false;
				bool over = false;
				player.resetPlayer();
			}
		case 'P':
		case 'p':
			if(jogo == true)
			{
				pause = true;
				jogo = false;
			}
			else
			{
				jogo = true;
				pause = false;
			}
			break;
		case 'F':
		case 'f':
			player.addMark();
			break;
		case 'W':
		case 'w':
			player.moveCharacter("up", &mapa);
			break;
		case 'S':
		case 's':
			player.moveCharacter("down", &mapa);
			break;
		case 'D':
		case 'd':
			player.moveCharacter("right", &mapa);
			break;
		case 'A':
		case 'a':
			player.moveCharacter("left", &mapa);
			break;
		case 'X':
		case 'x': // @@@ Aperta x pra iniciar o jogo. Sai do menu e inicia o timer do mapa.
			if (menu == true)
			{
			menu = false;
			jogo = true;
			timer = glutGet(GLUT_ELAPSED_TIME)/1000;
			}
			break;
		case 't':
			cout << glutGet(GLUT_ELAPSED_TIME)/1000 << endl;
	}
	//glutPostRedisplay(); // @@@ Mudei o postRedisplay e swapbuffers de lugar pra acabar com a zoeira da tela piscar preto
	//glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	// inicialização da glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
	glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("OpenGL Image drawing example");


	// especifica qual a função que trata da alteração da janela
    glutReshapeFunc(ChangeSize);

	// especifica qual é a função de renderização da tela
    glutDisplayFunc(RenderScene);

	// especifica qual é a função de tratamento de eventos de teclado
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

   
	// carrega imagem para a memória
	// iniciliza parâmetros
    init();

	// inicia looping do OpenGL
    glutMainLoop();

	// limpa memória ao final do looping
	finish();

	return 0;
}