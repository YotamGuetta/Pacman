#pragma once
#include "position.h"
#include "board.h"
class game_Obj {

	position pos;

public:
	int get_x() const;
	int get_y() const;
	void set_Pos(int x_val, int y_val);
	position get_Pos() const;
	void set_x(int x_val);
	void set_y(int y_val);
	void set_Pos(const position&);
	game_Obj() = default;
	game_Obj(int x_val, int y_val);
	bool compare(const game_Obj& obj1, const game_Obj& obj2)const;
};
