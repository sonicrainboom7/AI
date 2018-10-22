#include <stdlib.h>
#include "connect4.h"


/*
	Oma AI-luokka.
*/

	
class Oma_AI : public C4_AI
{
private:

	const double evaluationTable[6][7] = {
		/*{ 7, 5, 4, 3, 4, 5, 7 },
		{ 10, 8, 6, 4, 6, 8, 10 },
		{ 13, 11, 8, 5, 8, 11, 13 },
		{ 13, 11, 8, 5, 8, 11, 13 },
		{ 10, 8, 6, 4, 6, 8, 10 },
		{ 7, 5, 4, 3, 4, 5, 7 } };
		*/
	{3, 4, 5, 7, 5, 4, 3},
	{ 4, 6, 8, 10, 8, 6, 4 },
	{ 5, 8, 11, 13, 11, 8, 5 },
	{ 5, 8, 11, 13, 11, 8, 5 },
	{ 4, 6, 8, 10, 8, 6, 4 },
	{ 3, 4, 5, 7, 5, 4, 3 }};


public:

	// -----------------------------------------------------------------------
	// Oman AI:n toteutus!
	//
	// Pelin tilannetta varten ks. yliluokan C4_AI muuttujat:
	//
	// int _board[COLUMNS][ROWS];	pelilauta, [0][0] on vasen alanurkka
	// int _to_move;				siirtovuoro, RED tai BLUE
	//
	// _board:n arvoina voivat olla vakiot RED (1), BLUE (-1) tai EMPTY (0).
	// Vakiot COLUMNS ja ROWS asettavat pelilaudan dimensiot.
	//
	// Move on periaatteessa vain kokonaisluku, joka kertoo
	// mihin sarakkeesseen kiekko tiputetaan. Sarakkeet numeroidaan
	// vasemmalta oikealle 0,1,2,...
	//
	// Toteuta yliluokan puhtaat virtuaalifunktiot (= 0).
	//
	// Voit luonnollisesti myos lisata omia funktioitasi AI-luokkaasi.
	// Kirjoita kaikkien funktioiden toteutukset tahan samaan tiedostoon.
	// -----------------------------------------------------------------------
	virtual Move select_best_move()
	{
		// lailliset siirrot
		
		MinMaxVal retval = minimax(this, 4);
		return retval._move;

		
	}

	virtual void get_AI_name(std::string &name) const {
		name = "Plastic Explosive Bot feat Mellon"; 
	}

	 double evaluate() {
		double utility = 138;
		double sum = 0;
		for (int i = 0; i < ROWS; i++) {

			for (int j = 0; j < COLUMNS; j++) {
				if (_board[i][j] == RED) {
					sum += evaluationTable[i][j];
				}
				else if (_board[i][j] == BLUE) {
					sum -= evaluationTable[i][j];
				}
			}
			//printf("\n");
		}

		//printf("tulos %d", sum+/13utility);
		return    (utility + sum )/ 1000;
	}
	
	typedef struct { double _minmax; Move _move; } MinMaxVal;

	
	MinMaxVal minimax(Oma_AI* p, int depth)
	{
		
		MinMaxVal retval;
		
		Move movelist[COLUMNS];
		
		int nof_moves = gen_moves(movelist);
		
		retval._minmax = check_result();
		

		// Rekursion kantatapaus 1 (peli on päättynyt)
		if (nof_moves == 0 || retval._minmax != 0) {
			
			return retval;
			
		}
		// Rekursion kantatapaus 2 (katkaisuvyydessä)
		if (depth == 0)
		{
			
			retval._minmax = evaluate();
			//printf("%f", retval);
			return retval;
		}

		// Rekursioaskeleet (kokeillaan siirtovaihtoehdot)
		
		MinMaxVal best_value;
		
		best_value._minmax = _to_move == RED ? -1 : 1; // mahdollisimman huono alkuarvo
		
		for (int i = 0; i < nof_moves; ++i)
		{
			make_move(movelist[i]);
			retval = minimax(this, depth - 1);
			undo_move(movelist[i]);

			if (_to_move == RED && retval._minmax >= best_value._minmax)
			{
				best_value._minmax = retval._minmax;
				best_value._move = movelist[i];
			}
			if (_to_move == BLUE && retval._minmax <= best_value._minmax)
			{
				best_value._minmax = retval._minmax;
				best_value._move = movelist[i];
			}
		}
		return best_value;
	}
};
