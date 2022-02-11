#pragma once
#include "ghost.h"

class best : public Ghost
{
	Ghost g;
	
public:
	virtual void GhostAI(Ghost& g, board& map, game_Obj pac_man);

};
class good : public Ghost
{
	
public:
	virtual void GhostAI(Ghost& g, board& map, game_Obj pac_man);

};
class novice : public Ghost
{
	
public:
	virtual void GhostAI(Ghost& g, board& map, game_Obj pac_man);

};
