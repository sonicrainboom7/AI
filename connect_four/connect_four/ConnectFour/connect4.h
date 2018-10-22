#ifndef _CONNECT4_H_
#define _CONNECT4_H_

#include <iostream>
#include <string>

/*
	Pelilaudan dimensiot.
*/
#define COLUMNS	7
#define ROWS	6

/*
	Kiekot.
*/
#define RED		1
#define BLUE	-1
#define	EMPTY	0

/*
	Numeroidaan sarakkeet "vasemmalta oikealle" 0,1,2,...
	Yksi siirto voidaan siten kuvata kokonaisluvulla
	(=mihin sarakkeeseen kiekko tiputettiin).
	Periaatteessa yksinkertaistettu luennon Move-luokka
	Tic-Tac-Toe:ssa.
*/
#define Move	int


/*
	AI-yliluokka (periaatteessa sama kuin Position-luokka
	luennon Tic-Tac-Toe:ssa).
*/
class C4_AI
{
public:

	int _board[COLUMNS][ROWS];	// pelilauta, [0][0] on vasen alanurkka
	int _to_move;				// siirtovuoro, RED tai BLUE


	// Palauttaa AI:n "parhaan" siirron. 
	// Toteuta omassa aliluokassasi!
	virtual Move select_best_move() = 0;


	// Kertoo AI:n nimen kilpailua varten.
	// Toteuta omassa aliluokassasi!
	virtual void get_AI_name(std::string &name) const = 0;


	// Siirtogeneraattori etsii lailliset siirrot.
	// Palauttaa siirtojen lukumaaran (voi olla 0,
	// jos pelilauta on taynna).
	virtual int gen_moves(Move *movelist) const
	{
		int nof_moves = 0;

		for (int c = 0; c < COLUMNS; ++c)
			for (int r = 0; r < ROWS; ++r)
				if (_board[c][r] == EMPTY)
				{
					movelist[nof_moves++] = c;
					break;
				}

		return nof_moves;
	}


	// Tekee siirron.
	virtual void make_move(Move m) {
		int r = 0;
		while (_board[m][r] != EMPTY) ++r;
		_board[m][r] = _to_move;
		_to_move = (_to_move == RED ? BLUE : RED);
	}


	// Peruu siirron.
	virtual void undo_move(Move m) {
		int r = ROWS - 1;
		while (_board[m][r] == EMPTY) --r;
		_board[m][r] = EMPTY;
		_to_move = (_to_move == RED ? BLUE : RED);
	}


	// Konstruktori asettaa pelin alkutilanteen.
	// RED aloittaa.
	C4_AI()
	{
		for (int c = 0; c < COLUMNS; ++c)
			for (int r = 0; r < ROWS; ++r)
				_board[c][r] = EMPTY;
		_to_move = RED;
	}


	// Destruktori.
	virtual ~C4_AI() {}


	// Palauttaa pelin voittajan, RED (1) tai BLUE (-1).
	// Palauttaa 0 jos kumpikaan pelaaja ei ole voittanut.
	int check_result() const
	{
		// Suunnat joihin 4:n suoria tutkitaan (5 kpl).
		int deltas[5][2] = {{+1,0},{+1,+1},{0,+1},{-1,+1},{-1,0}};
		int in_a_row, nc, nr;

		for (int c = 0; c < COLUMNS; ++c)
			for (int r = 0; r < ROWS; ++r)
			{
				if (_board[c][r] == EMPTY)
					continue;
				for (int d = 0; d < 5; ++d)
				{
					in_a_row = 1;
					for (int i = 1; i <= 3; ++i)
					{
						nc = c + i * deltas[d][0];
						nr = r + i * deltas[d][1];
						if (nc < 0 || nc >= COLUMNS || nr < 0 || nr >= ROWS || _board[nc][nr] != _board[c][r])
							break;
						++in_a_row;
					}
					if (in_a_row == 4)
						return _board[c][r];
				}
			}

		return 0;
	}


	// Tulostaa pelitilanteen stdout:iin.
	void print() const
	{
		for (int c = 0; c < COLUMNS; ++c)
		{
			std::cout << " " << c;
		}
		std::cout << "\n";
		for (int c = 0; c < COLUMNS; ++c)
		{
			std::cout << "--";
		}
		std::cout << "-\n";
		for (int r = ROWS - 1; r >= 0; --r)
		{
			for (int c = 0; c < COLUMNS; ++c)
			{
				std::cout << "|";
				switch (_board[c][r])
				{
				case RED:
					std::cout << "X";
					break;
				case BLUE:
					std::cout << "O";
					break;
				default:
					std::cout << " ";
					break;
				}
			}
			std::cout << "|\n";
		}
		for (int c = 0; c < COLUMNS; ++c)
		{
			std::cout << "--";
		}
		std::cout << "-\n";
	}
};

#endif
