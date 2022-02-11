#pragma once

#include "entity.h"
#include <vector>

class  fruit
{
	game_Obj fr;
	char value;
	bool exist = false;
	void moveFruit(board& map, ofstream& steps, int mode);
	void makeFruit(board& map, ofstream& steps, int mode);
	void deleteFruit(board& map);
public:
	bool moveFruit(int dir, int mode, board& map);
	void makeFruit(int x, int y, int val, int mode, board& map);
	void updateFruit(board& map, game_Obj& pac_man, vector<Ghost> ghost,unsigned int& score, ofstream& steps, int mode);
};

