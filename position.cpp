#include <iostream>
#include "position.h"
position::position(int x, int y) {
	this->x = x;
	this->y = y;
}
void position::set_x(int& x_val) {
	x = x_val;
}
void position::set_y(int& y_val) {
	y = y_val;
}
int position::get_x() const{
	return x;
}
int position::get_y() const{
	return y;
}
void position::set_xy(int x, int y) {
	this->x = x;
	this->y = y;
}