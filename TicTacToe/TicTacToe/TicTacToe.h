// Ristinollapelin luokkien esittelyt.
//
// Historia:
// 22.01.2015 Ensimm‰inen versio kirjoitettu. (JL)
// 27.01.2015 Siistitty. (JL)
// 28.01.2015 Siistitty. (JL)
// 29.01.2015 Siistitty. (JL)

#ifndef _RISTINOLLA_H_
    #define _RISTINOLLA_H_

#include "Math.h"	// T‰m‰n pit‰‰ olla ennen glut.h:ta!
#include <glut.h>	// gl.h, glu.h ja glx.h tulevat automaattisesti mukana.
#include <vector>

#define WNDHEIGHT	((int) 600)	// Ikkunan korkeus pikselein‰.
#define WNDWIDTH	((int) 600)	// Ikkunan leveys pikselein‰.
#define WNDPOSX		((int) 500)	// Ikkunan vasemman yl‰nurkan x-koordinaatti pikselein‰.
#define WNDPOSY		((int) 50)	// Ikkunan vasemman yl‰nurkan y-koordinaatti pikselein‰.
#define PLAYER_O	((int) -1)	// Pelaaja O (ohjelman k‰ytt‰j‰).
#define PLAYER_X	((int) 1)	// Pelaaja X (ohjelma).
#define EMPTY		((int) 0)	// Tyhj‰ ruutu.

// Voittorivi:

class Line
{
	// Rivin alku:
	int row1;
	int col1;
	// Rivin loppu:
	int row2;
	int col2;
public:
	Line() {row1 = 0; col1 = 0; row2 = 0; col2 = 0;}
	void Clear() {row1 = 0; col1 = 0; row2 = 0; col2 = 0;}
	void Set(int r1, int c1, int r2, int c2);
	int GetRow1() const { return row1; }
	int GetCol1() const { return col1; }
	int GetRow2() const { return row2; }
	int GetCol2() const { return col2; }
};

// Pelitilanne:

class S
{
protected:
	int B[9];		// Pelilauta (alkiot EMPTY, PLAYER_O tai PLAYER_X).
	int p[2];		// Pistetilanne (p[0] pelaaja O, p[1] pelaaja X).
	int t;			// Siirtovuorossa oleva pelaaja.
public:
	S();
	int GetB(int row, int col) const;
	void SetB(int row, int col, int player);
	int Getp(int j) const;
	void Setp(int j, int score);
	int Gett() const;
	void Sett(int player);
	void Clear();
	bool GameOver() const; 
	int X();	// Satunnaismuuttuja.
	void T(int i);	// Tilasiirtym‰funktio.

	// TOOMAKSEN FUNKTIOT
	std::vector<short> testRow(short row, short botOrPlayer);
	std::vector<short> testLineDown(short line, short botOrPlayer);
	int testPossibleMoves();
};

class State : public S
{
	Line L;
public:
	State();
	void Clear();
	void WinCheck();
	void Display() const;
};

void DrawX(float x, float y, float size);
void DrawO(float x, float y, float size);

#endif