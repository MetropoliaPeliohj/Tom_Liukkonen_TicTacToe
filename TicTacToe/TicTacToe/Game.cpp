// Ristinollapeli mallina yleisest‰ pelist‰.
// Toteutettu k‰ytt‰en OpenGL- ja GLUT-funktiokirjastoja.
//
// Historia:
// 22.01.2015 Ensimm‰inen versio kirjoitettu. (JL)
// 27.01.2015 Lis‰tty timer, siistitty. (JL)
// 28.01.2015 Siistitty. (JL)
// 29.01.2015 Siistitty. (JL)

#include "TicTacToe.h"

using std::cout;
using std::endl;

State s;

void myInit(void)
{
	// Asetetaan taustav‰ri:
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glLineWidth(2.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Asetetaan ikkunasta n‰kyv‰ alue antamalla nurkkapisteiden koordinaatit:
	gluOrtho2D(0, WNDWIDTH, 0, WNDHEIGHT);

	// Alustetaan satunnaislukugeneraattori:
	initrand();
}

// Helppi‰ k‰ytt‰j‰lle:

void myHelp()
{
	cout << "Hiiren vasen: piirr\x84 nolla." << endl;
	cout << "Hiiren oikea: aloita uusi peli." << endl << endl;
}

// Ikkunan display-funktio. Suoritetaan esim. kun ikkuna avataan ansimm‰isen
// kerran, palautetaan toisen ikkunan takaa tai palautetaan pienennyksen
// j‰lkeen alapalkin ikonista.

void myDraw(void)			
{
	// Kuvan tyhjennys:
	glClear(GL_COLOR_BUFFER_BIT);

	s.Display();

	glFlush();
}

// Timer-callback "miettimisajan" antamiseksi ohjelmalle:

void myTimer(int player_in_turn)
{

	if (player_in_turn == PLAYER_X)
	{
		//glutTimerFunc(1000, myTimer, PLAYER_O); // ORIGINAL
		glutTimerFunc(10, myTimer, PLAYER_O);
	}
	else
	{
		if (! s.GameOver()) s.T(s.X());
		s.Sett(PLAYER_O);
		s.WinCheck();
		glutPostRedisplay();
	}
}

// Hiiren callback:

void myMouse(int button, int state, int xMouse, int yMouse)
{
	if (state == GLUT_DOWN && s.Gett() == PLAYER_O)		// Painettiin hiiren jotain painiketta
	{
		float x = (float) xMouse;
		float y = (float) (WNDHEIGHT - yMouse);

		if (button == GLUT_LEFT_BUTTON)	// Vasen painike
		{
			int row = floor((WNDHEIGHT - y) / (WNDHEIGHT / 3.0));
			int col = floor(x / (WNDWIDTH / 3.0));
			if (row < 0) row = 0; else if (row > 2) row = 2;
			if (col < 0) col = 0; else if (col > 2) col = 2;
			if (! s.GameOver() && s.GetB(row, col) == 0)	
			{
				s.T(row * 3 + col);
				s.Sett(PLAYER_X);
				s.WinCheck();
				glutPostRedisplay();
				glutTimerFunc(100, myTimer, PLAYER_X);
			}

		}
		else if (button == GLUT_RIGHT_BUTTON)	// Oikea painike
		{
			s.Clear();
		}
		else if (button == GLUT_MIDDLE_BUTTON)	// Keskipainike
		{
		}

		glutPostRedisplay();	// Display-callbackin vienti suoritusjonoon
	}

	return;
}

// Reshape-callback. Estet‰‰n ikkunan koon muuttaminen:

void myReshape(int w, int h)
{
	glutReshapeWindow(WNDWIDTH, WNDHEIGHT);
}

// P‰‰ohjelma:

void main()
{
	glutInitDisplayMode(GLUT_SINGLE);	// Kaksoispuskurointi (est‰‰ animaation v‰lkkymisen).
	glutInitWindowSize(WNDWIDTH, WNDHEIGHT);
	glutInitWindowPosition(WNDPOSX, WNDPOSY);
	glutCreateWindow("Ristinollapeli"); 	// Avataan grafiikkaikkuna otsikolla.

	// Rekisterˆid‰‰n ikkunan display callback:
	glutDisplayFunc(myDraw);
	// Rekisterˆid‰‰n hiiren callback:
	glutMouseFunc(myMouse);
	// Rekisterˆid‰‰n reshape callback:
	glutReshapeFunc(myReshape);

	// Alkuasetukset:
	myInit();
	// Helppi‰ k‰ytt‰j‰lle:
	myHelp();
	// Lopuksi meno p‰‰silmukkaan:
	glutMainLoop();
}