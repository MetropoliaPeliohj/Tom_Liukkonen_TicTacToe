// Ristinollapelin luokkien metodien määrittelyt.
//
// Historia:
// 22.01.2015 Ensimmäinen versio kirjoitettu. (JL)
// 27.01.2015 Siistitty. (JL)
// 28.01.2015 Siistitty. (JL)
// 29.01.2015 Siistitty. (JL)
// 03.02.2015 Muutettu pistetilanteen tulkintaa (-1 = peli kesken). (JL)

#include "TicTacToe.h"
#include <vector>

void Line::Set(int r1, int c1, int r2, int c2)
{
	row1 = r1; col1 = c1; row2 = r2; col2 = c2;
}

S::S()
{
	for (int i = 0; i < 9; i++)	B[i] = EMPTY;
	p[0] = -1; p[1] = -1;
	t = PLAYER_O;
}

int S::GetB(int row, int col) const
{
	return B[row * 3 + col];
}

void S::SetB(int row, int col, int player)
{
	B[row * 3 + col] = player;
}

int S::Getp(int j) const
{
	return p[j];
}

void S::Setp(int j, int score)
{
	p[j] = score;
}

int S::Gett() const
{
	return t;
}

void S::Sett(int player)
{
	t = player;
}

void S::Clear()
{
	for (int i = 0; i < 9; i++) B[i] = EMPTY;
	p[0] = -1; p[1] = -1;
	t = PLAYER_O;
}

bool S::GameOver() const
{
	int i = 0, count = 0;
	while (i < 9 && count == 0)
	{
		if (B[i++] == EMPTY) count++;
	}

	return (count == 0 || p[0] + p[1] >= 0) ? true : false;
}

// Ohjelman seuraava veikkaus:

int S::X()
{
	int available[9];
	int i, count = 0;

	for (i = 0; i < 9; i++)
	{
		if (B[i] == EMPTY) available[count++] = i;
	}

	// Checking here
	int possibleMove = testPossibleMoves(0); // Checking bot
	if (possibleMove != -1) return possibleMove;

	possibleMove = testPossibleMoves(1); // Checking player
	if (possibleMove != -1) return possibleMove;

	int paikka;
	if (count == 0 || p[0] + p[1] >= 0) {
		paikka = -1;
	}
	else
	{
		paikka = available[randint(0, count - 1)];
	}

	return paikka;
}

/**
*	This function checks for possible critic situations. 
*	Not using trees
*/
int S::testPossibleMoves(short botOrPlayer)
{
	int move = -1;
	short index;

	// Testing if we have a row.
	std::vector<short> botRow;
	
	for (index = 0; index < 3; index++)
	{
		botRow = TestNextMove(index, botOrPlayer, 0); // Test row
		if (botRow.size() != 0) return botRow[0] * 3 + botRow[1];
	}

	for (index = 0; index < 3; index++)
	{
		botRow = TestNextMove(index, botOrPlayer, 1); // Test line
		if (botRow.size() != 0) return botRow[0] * 3 + botRow[1];
	}

	botRow = TestNextMove(index, botOrPlayer, 2); // Test titled from upper left to lower right 
	if (botRow.size() != 0) return botRow[0] * 3 + botRow[1];

	botRow = TestNextMove(index, botOrPlayer, 3); // titled from lower left to upped right
	if (botRow.size() != 0) return botRow[0] * 3 + botRow[1];


	return move;
}



/**
*	Testing for the possibility to win. Row: goes from left to right, line: up down
*	Params:
*		short rowOrLine: row or line to test - 0,1,2
*		byte botOrPlayer: 0-bot, 1-player
*		short type: 0- rows, 1- lines, 2- titled from upper left to lower right, 3- titled from lower left to upped right
*/
std::vector<short> S::TestNextMove(short rowOrLine, short botOrPlayer, short type)
{
	std::vector<short> position;

	short player = (botOrPlayer == 0) ? (short)PLAYER_X : (short)PLAYER_O;
	short firstPosition;
	short secondPosition;
	short thirdPosition;

	if (type == 0) // rows
	{
		firstPosition = GetB(rowOrLine, 0);
		secondPosition = GetB(rowOrLine, 1);
		thirdPosition = GetB(rowOrLine, 2);
	}
	else if (type == 1) // lines
	{
		firstPosition = GetB(0, rowOrLine);
		secondPosition = GetB(1, rowOrLine);
		thirdPosition = GetB(2, rowOrLine);
	}
	else if (type == 2) // titled from upper left to lower right
	{
		firstPosition = GetB(0, 0);
		secondPosition = GetB(1, 1);
		thirdPosition = GetB(2, 2);
	}
	else if (type == 3) // titled from lower left to upped right
	{
		firstPosition = GetB(2, 0);
		secondPosition = GetB(1, 1);
		thirdPosition = GetB(0, 2);
	}
	else
	{
		return position;
	}

	if (firstPosition == player && secondPosition == player && thirdPosition == EMPTY
		|| firstPosition == player && secondPosition == EMPTY && thirdPosition == player
		|| firstPosition == EMPTY && secondPosition == player && thirdPosition == player)
	{
		if (firstPosition == EMPTY)
		{
			if (type == 0) // Rows
			{
				position.push_back(rowOrLine); position.push_back(0);
			}
			else if (type == 1) // lines
			{
				position.push_back(0); position.push_back(rowOrLine);
			}
			else if (type == 2) // titled from upper left to lower right
			{
				position.push_back(0); position.push_back(0);
			}
			else if (type == 3) // titled from lower left to upped right
			{
				position.push_back(2); position.push_back(0);
			}
		}
		else if (secondPosition == EMPTY)
		{
			if (type == 0) // rows
			{
				position.push_back(rowOrLine); position.push_back(1);
			}
			else if (type == 1) // lines
			{
				position.push_back(1); position.push_back(rowOrLine);
			}
			else if (type == 2) // titled from upper left to lower right
			{
				position.push_back(1); position.push_back(1);
			}
			else if (type == 3) // titled from lower left to upped right
			{
				position.push_back(1); position.push_back(1);
			}
		}
		else if (thirdPosition == EMPTY)
		{
			if (type == 0) // rows
			{
				position.push_back(rowOrLine); position.push_back(2);
			}
			else if (type == 1) // lines
			{
				position.push_back(2); position.push_back(rowOrLine);
			}
			else if (type == 2) // titled from upper left to lower right
			{
				position.push_back(2); position.push_back(2);
			}
			else if (type == 3) // titled from lower left to upped right
			{
				position.push_back(0); position.push_back(2);
			}
		}
	}

	return position;
}



void S::T(int i)
{
	if (0 <= i && i < 9) B[i] = t;
}

State::State()
{
	L.Clear();
}

// Alkutilanteen palautus:

void State::Clear()
{
	S::Clear();
	L.Clear();
}

// Kolmen suoran tarkistus:
	
void State::WinCheck()
{
	int winner = 0;

	// Ensimmäinen vaakarivi:
	if (GetB(0, 0) != EMPTY && GetB(0, 0) == GetB(0, 1) && GetB(0, 1) == GetB(0, 2))
	{
		winner = GetB(0, 0);
		L.Set(0, 0, 0, 2);
	}
	// Toinen vaakarivi:
	if (GetB(1, 0) != EMPTY && GetB(1, 0) == GetB(1, 1) && GetB(1, 1) == GetB(1, 2))
	{
		winner = GetB(1, 0);
		L.Set(1, 0, 1, 2);
	}
	// Kolmas vaakarivi:
	if (GetB(2, 0) != EMPTY && GetB(2, 0) == GetB(2, 1) && GetB(2, 1) == GetB(2, 2))
	{
		winner = GetB(2, 0);
		L.Set(2, 0, 2, 2);
	}
	// Ensimmäinen pystyrivi:
	if (GetB(0, 0) != EMPTY && GetB(0, 0) == GetB(1, 0) && GetB(1, 0) == GetB(2, 0))
	{
		winner = GetB(0, 0);
		L.Set(0, 0, 2, 0);
	}
	// Toinen pystyrivi:
	if (GetB(0, 1) != EMPTY && GetB(0, 1) == GetB(1, 1) && GetB(1, 1) == GetB(2, 1))
	{
		winner = GetB(0, 1);
		L.Set(0, 1, 2, 1);
	}
	// Kolmas pystyrivi:
	if (GetB(0, 2) != EMPTY && GetB(0, 2) == GetB(1, 2) && GetB(1, 2) == GetB(2, 2))
	{
		winner = GetB(0, 2);
		L.Set(0, 2, 2, 2);
	}
	// Oikealle laskeva vinorivi:
	if (GetB(0, 0) != EMPTY && GetB(0, 0) == GetB(1, 1) && GetB(1, 1) == GetB(2, 2))
	{
		winner = GetB(0, 0);
		L.Set(0, 0, 2, 2);
	}
	// Oikealle nouseva vinorivi:
	if (GetB(2, 0) != EMPTY && GetB(2, 0) == GetB(1, 1) && GetB(1, 1) == GetB(0, 2))
	{
		winner = GetB(2, 0);
		L.Set(2, 0, 0, 2);
	}

	if (winner)
	{
		// Jompikumpi voitti.
		p[0] = 0; p[1] = 0;
		p[(winner == PLAYER_O) ? 0 : 1] = 1;
	}
	else if (GameOver())
	{
		// Tasapeli.
		p[0] = 0; p[1] = 0;
	}
}

// Pelitilanteen näyttäminen kuvaruudulla:

void State::Display() const
{
	int row, col;
	float x, y, s = WNDWIDTH / 3.0, size = 0.8 * s;

	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
		for (row = 0; row <= 3; row++)
		{
			x = 3 * s;
			y = (3 - row) * s;
			glVertex2f(0.0, y);
			glVertex2f(x, y);
			glVertex2f(y, 0.0);
			glVertex2f(y, x);
		}
	glEnd();

	glColor3f(0, 0, 0);

	for (row = 0; row < 3; row++)
		for (col = 0; col < 3; col++)
		{
			x = (0.5 + col) * s;
			y = (2.5 - row) * s;
			switch (GetB(row, col))
			{
			case PLAYER_O:
				DrawO(x, y, size);
				break;
			case PLAYER_X:
				DrawX(x, y, size);
				break;
			}
		}

	glColor3f(0, 1, 0);
	glLineWidth(4.0);

	if (GameOver())
	{
		glBegin(GL_LINES);
			x = (0.5 + L.GetCol1()) * s;
			y = (2.5 - L.GetRow1()) * s;
			glVertex2f(x, y);
			x = (0.5 + L.GetCol2()) * s;
			y = (2.5 - L.GetRow2()) * s;
			glVertex2f(x, y);
		glEnd();
	}

	glLineWidth(2.0);
	glColor3f(1, 1, 1);
}

// Ristin piirtäminen:

void DrawX(float x, float y, float size)
{
	float r = 0.5 * size;
	glBegin(GL_LINES);
		glVertex2f(x - r, y - r);
		glVertex2f(x + r, y + r);
		glVertex2f(x - r, y + r);
		glVertex2f(x + r, y - r);
	glEnd();
}

// Nollan piirtäminen:

void DrawO(float x, float y, float size)
{
	int k, n = 40;
	float alpha = 0.0, dalpha = 2 * PI / n, r = 0.5 * size;

	glBegin(GL_LINE_LOOP);
		for (k = 0; k < n; k++)
		{
			alpha += dalpha;
			glVertex2f(x + r*cos(alpha), y + r*sin(alpha));
		}
	glEnd();
}

