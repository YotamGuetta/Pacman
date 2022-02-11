#pragma once


using namespace std;
class position {
	int x;
	int y;
public:
	position() = default;
	position(int x, int y);
	void set_x(int& x_val);
	void set_y(int& y_val);
	int get_x() const;
	int get_y() const;
	void set_xy(int x, int y);
};

