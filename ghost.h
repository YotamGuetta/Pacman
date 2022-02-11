#pragma once
#include "game_obj.h"

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};
class Ghost
{
	vector<walk> BFSArray;
	game_Obj gObj;
	int direction = 0;
	vector<target> walk_queue;
	game_Obj last_pac_man_pos;

	void FindPath(int sx, int sy, int x, int y, board& map);
	bool wasRandomlyMoved();
	void AddArray(int x, int y, int wc, int back, char** tmp_map, board& map);
	void printDeb(board& map, char** tmp_map);
public:
	Ghost(position&);
	Ghost() = default;
	Ghost(int x, int y);
	int get_x() const;
	int get_y() const;
	void  resetGhost(position oldPos, board& map);
	game_Obj getObj()const;
	int getDir() const;
	void setObj(game_Obj);
	void set_Pos(int x, int y);
	void setDir(int dir);
	int AIRandom(game_Obj& ghost, board& map);
	bool* posibbleMoves(game_Obj obj, board& map);
	void moveObj(game_Obj& obj, int direction, board& map);
	void moveObj(int direction, int mode, board& map);
	virtual void GhostAI(Ghost& g, board& map, game_Obj& pac_man) { };
	void smartGhostAI(game_Obj& player, board& map);
};

