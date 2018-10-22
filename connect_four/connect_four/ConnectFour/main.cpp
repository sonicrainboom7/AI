#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "connect4.h"
#include "human.h"
#include "oma_ai.h"


// -----------------------------------------------------------------------
// Connect Four.
// -----------------------------------------------------------------------
int main()
{
	srand ((unsigned)time(NULL));
	Move movelist[COLUMNS];
	Move move;

	// Luo sellaiset pelaajat kuin haluat (esim. AI tai ihminen).
	// HUOM! Oma_AI tulee toteuttaa ensin!
	C4_AI *red				= new Oma_AI();
	//C4_AI *blue				= new Oma_AI();
	//C4_AI *red				= new Human();
	C4_AI *blue				= new Human();

	// Punainen aloittaa.
	C4_AI *active_player	= red;

	while (1)
	{
		// Tulosta tilanne ja tarkista lopputulos.
		active_player->print();
		if (active_player->gen_moves(movelist) == 0 || active_player->check_result())
			break;

		// Valitse paras siirto (tee molemmille pelaajille).
		move = active_player->select_best_move();
		red	->make_move(move);
		blue->make_move(move);
		active_player = active_player->_to_move == RED ? red : blue;
	}

	// Tulosta lopputulos.
	switch(active_player->check_result())
	{
	case RED:
		std::cout << "RED WON\n";
		break;
	case BLUE:
		std::cout << "BLUE WON\n";
		break;
	case 0:
		std::cout << "DRAW\n";
		break;
	}

	delete red;
	delete blue;
	return 0;
}
