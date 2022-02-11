#pragma once
#include "position.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;
const int ROW_SIZE = 18; // The max row of the board.
const int COL_SIZE = 32;// The max column of the board.
class board {
	bool use_file_map = false;
	vector<string> file_map;
	char map[ROW_SIZE][COL_SIZE+1] = {
	"+#############  ##############+",
	"|...............|.............|",
	"|...............|.............|",
	"|...########....|....#########|",
	"|...|.........................|",
	"|...|....|..######............|",
	"|........|..|....|............|",
	" ...######..|....|..... ...... ",
	" ............................. ",
	"|....................######...|",
	"|.........................|...|",
	"|.........................|...|",
	"|########............|........|",
	"|....................|........|",
	"|............|.......#########|",
	"|............|................|",
	"|............|................|",
	"+#############  ##############+"
	};
	public:
		board() = default;
		void setMap(vector<string>&);
		char getMapChar(int x, int y) const;
		void setMapChar(int x, int y, char c);
		const int getMapRow();
		const int getMapCol();
		void printBoard() const;
		void gotoxy(int x, int y);
		char** copyBoard();
	
};
