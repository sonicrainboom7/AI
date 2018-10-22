#ifndef _HUMAN_H_
#define _HUMAN_H_

#include <iostream>
#include <string>
#include "connect4.h"


/*
	Ihmispelaaja.
*/
class Human : public C4_AI
{
public:

	// -----------------------------------------------------------------------
	// Lukee ja palauttaa pelaajan siirron stdio:sta.
	// Hyvaksyy vain lailliset siirrot.
	// -----------------------------------------------------------------------
	Move select_best_move()
	{
		Move move;
		int nof_moves;
		int not_legal;
		Move movelist[COLUMNS];

		nof_moves = gen_moves(movelist);
		not_legal = 1;
		while (not_legal)
		{
			std::cin >> move;
			for (int i = 0; (i < nof_moves) && not_legal; ++i)
				if (movelist[i] == move)
					not_legal = 0;
		}

		return move;
	}


	void get_AI_name(std::string &name) const
	{ 
		name = "Human Player";
	}
};

#endif
