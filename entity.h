#pragma once
#include "ghostMoveStrategy.h"
#include "InputParser.h"
const int TOTAL_CRUMS = 354;
const int Ghost_Num = 2;

const enum keys { S = 115, UP = 119, DOWN = 120, LEFT = 97, RIGHT = 100, ESC = 27 };
const enum keys2 { S2 = 83, UP2 = 87, DOWN2 = 88, LEFT2 = 65, RIGHT2 = 68};
//s or S for stop
//w or W for Up 
//x or X for Down
//a or A for Left 
//d or D for Right 
//Esc for pause

class entity {
public:

	void printGameObj(const game_Obj& pac_man, const char& avatar);
	void printGameObj(vector<Ghost> ghosts);
	void moveGhost(Ghost& ghost, board& map, game_Obj& pac_man, int diff);
	void movePac_ManTo(game_Obj& pac_man, int toX, int toY, board& map, int mode);
	void movePac_Man(game_Obj& pac_man, char comm, board& map, ofstream& steps, int mode);
	bool hitsTheGhost(vector<Ghost> ghost, const game_Obj& pac_man);
	bool hitsTheGhost(game_Obj ghost, const game_Obj& pac_man);
};
