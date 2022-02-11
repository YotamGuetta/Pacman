#include "fruit.h"

/// <summary>
/// Returns an array of the empty squares in the map for the frute to be in
/// </summary>
/// <param name="map">The game map</param>
/// <returns>positions array</returns>
vector<position> emptySquares(board& map) {
	int i, j;
	position pos;
	vector<position> arr;
	for (i = 1; i < map.getMapRow() - 1; i++) {
		for (j = 1; j < map.getMapCol() - 1; j++) {
			if (map.getMapChar(i, j) == '.' || map.getMapChar(i, j) == ' ') {
				pos.set_x(i);
				pos.set_y(j);
				arr.push_back(pos);
			}
		}
	}
	return arr;
}


void fruit::moveFruit(board& map, ofstream& steps, int mode) {
	Ghost g;
	if (mode == save)
		steps << "f" << g.AIRandom(this->fr, map) << ' ';

}

bool fruit::moveFruit(int dir, int mode, board& map) {
	if (exist) {
		enum move { UP, LEFT, DOWN, RIGHT };
		if (mode != silent) {
			map.gotoxy(fr.get_x(), fr.get_y());
			cout << map.getMapChar(fr.get_x(), fr.get_y());
		}
		switch (dir)
		{
		case UP: fr.set_x(fr.get_x() - 1); break;
		case DOWN: fr.set_x(fr.get_x() + 1); break;
		case LEFT: fr.set_y(fr.get_y() - 1); break;
		case RIGHT: fr.set_y(fr.get_y() + 1); break;
		}
		if (mode != silent) {
			map.gotoxy(fr.get_x(), fr.get_y());
			cout << value;
			map.gotoxy(map.getMapRow(), map.getMapRow());
		}
	}
	return exist;
}
/// <summary>
/// has a 10% chance of making a fruit every frame
/// </summary>
/// <param name="map"></param>
void fruit::makeFruit(board& map, ofstream& steps, int mode) {
	int x;
	vector<position> possibleSquares;
	if (!exist) {
		x = rand() % 10;
		if (x == 0) {
			possibleSquares = emptySquares(map);
			x = rand() % possibleSquares.size() - 1;
			fr.set_Pos(possibleSquares[x]);
			value = '0' + 5 + rand() % 5;
			if (mode == save)
				steps << '(' << fr.get_x() << ',' << fr.get_y() << ','<< value << ')'<< ' ';
			exist = true;

			possibleSquares.clear();
		}
	}
	else {
		
	}
}
void fruit::makeFruit(int x, int y, int val, int mode, board& map) {
	fr.set_Pos(position(x, y));
	value = val + '0';
	exist = true;
	if (mode != silent) {
		map.gotoxy(x, y);
		cout << val;
		map.gotoxy(map.getMapRow(), map.getMapRow());	
	}
}
/// <summary>
/// makes , moves or delets the fruit
/// </summary>
/// <param name="map"></param>
/// <param name="pac_man"></param>
/// <param name="ghost"></param>
/// <param name="score"></param>
void fruit::updateFruit(board& map, game_Obj& pac_man, vector<Ghost> ghost, unsigned int& score, ofstream& steps, int mode) {
	Ghost g;
	static int upTime = 0;
	entity en;
	bool wasEaten = false;
	if (en.hitsTheGhost(pac_man, fr)) {
		wasEaten = true;
		score += (value - '0');
	}
	else
		wasEaten = en.hitsTheGhost(ghost, fr);


	if (exist) {
		if (wasEaten) {
			deleteFruit(map);
			upTime = 0;
		}
		else {
			if (upTime % 6 == 5)
				moveFruit(map, steps, mode);
		}
	}
	else {
		makeFruit(map, steps, mode);
	}
	if (exist) {
		map.gotoxy(fr.get_x(), fr.get_y());
		cout << value;
		upTime++;
	}

}
void fruit::deleteFruit(board& map) {
	int x, y;
	x = fr.get_x();
	y = fr.get_y();
	map.gotoxy(x, y);
	cout << map.getMapChar(x, y);
	exist = false;
}

