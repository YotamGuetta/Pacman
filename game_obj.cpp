
#include "game_obj.h"

game_Obj::game_Obj(int x_val, int y_val) {
	pos.set_x(x_val);
	pos.set_y(y_val);
}
void game_Obj::set_Pos(int x_val, int y_val) {
	pos.set_x(x_val);
	pos.set_y(y_val);
}
position game_Obj::get_Pos() const{
	int x, y;
	position res;
	x = pos.get_x();
	y = pos.get_y();
	res.set_x(x);
	res.set_y(y);
	return res;
}
int game_Obj::get_x() const{

	return pos.get_x();
}
int game_Obj::get_y() const{
	return  pos.get_y();
}
void game_Obj::set_Pos(const position& newPos) {
	pos = newPos;
}
void game_Obj::set_x(int x_val) {
	pos.set_x(x_val);
}
void game_Obj::set_y(int y_val) {
	pos.set_y(y_val);
}

bool game_Obj::compare(const game_Obj& obj1, const game_Obj& obj2)const {
	if (obj1.get_x() == obj2.get_x() && obj1.get_y() == obj2.get_y())
		return true;
	return false;
}