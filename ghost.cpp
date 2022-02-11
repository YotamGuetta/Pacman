#include "ghost.h"

Ghost::Ghost(position& p) {
	gObj.set_Pos(p);
	last_pac_man_pos.set_x(0);
	last_pac_man_pos.set_y(0);
}

Ghost::Ghost(int x, int y) {
	game_Obj obj(x, y);
	gObj = obj;
	last_pac_man_pos.set_x(0);
	last_pac_man_pos.set_y(0);
}

/// <summary>
/// A function to shows how the ghost AI thinks ingame.
/// </summary>
/// <param name="map">game map</param>
/// <param name="tmp_map">ghost view map</param>
void Ghost::printDeb(board& map, char** tmp_map) {
	int i, j, row = map.getMapRow(), col = map.getMapCol();
	Sleep(10);
	system("cls");
	map.gotoxy(0, 0);
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			cout << tmp_map[i][j];
		cout << endl;
	}

}
/// <summary>
/// blockes the moveable space for the ghost
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="wc"></param>
/// <param name="back"></param>
/// <param name="tmp_map"></param>
/// <param name="map"></param>
void Ghost::AddArray(int x, int y, int wc, int back, char** tmp_map, board& map) {
	if (x> 0 && y> 0&& x < map.getMapRow() && y < map.getMapCol()) {
		if (tmp_map[x][y] == ' ' || tmp_map[x][y] == '.') {
			tmp_map[x][y] = '#';
			walk tmp;
			tmp.x = x;
			tmp.y = y;
			tmp.walk_count = wc;
			tmp.back = back;
			BFSArray.push_back(tmp);
		}
	}
}
/// <summary>
/// fines the shortest route for the ghost to Pac Man by going every possible direction and blocking it to avoid him from going in circles.
/// </summary>
/// <param name="sx">ghost cord</param>
/// <param name="sy">ghost cord</param>
/// <param name="x">Pac Man cord</param>
/// <param name="y">Pac Man cord</param>
/// <param name="map">Game map</param>
void Ghost::FindPath(int sx, int sy, int x, int y, board& map) {
	int i, j;
	char** tmp_map = map.copyBoard();

	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);

	i = 0;
	while (i < BFSArray.size()) {
		if (BFSArray[i].x == x && BFSArray[i].y == y) {
				walk_queue.clear();
			target tmp2;
			while (BFSArray[i].walk_count != 0) {
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);
				i = BFSArray[i].back;
			}
			break;
		}
		//printDeb(map, tmp_map); // shows how the ghost AI functions
		;
		AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i, tmp_map, map);
		AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i, tmp_map, map);
		AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i, tmp_map, map);
		AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i, tmp_map, map);


		i++;
	}
	for (i = 0; i < map.getMapRow(); i++)
		delete[] tmp_map[i];
	delete[] tmp_map;
	BFSArray.clear();
}
void   Ghost::resetGhost(position oldPos, board& map) {
	int x = gObj.get_x(), y = gObj.get_y();
	map.gotoxy(x, y);
	cout << map.getMapChar(x, y);
	last_pac_man_pos.set_Pos(0, 0);
	gObj.set_Pos(oldPos);
}






int Ghost::get_x() const {
	return gObj.get_x();
}
int Ghost::get_y() const {
	return gObj.get_y();
}

game_Obj Ghost::getObj()const {
	return gObj;
}
int Ghost::getDir() const {
	return direction;
}
void Ghost::setObj(game_Obj obj) {
	gObj = obj;
}

void Ghost::set_Pos(int x, int y) {
	gObj.set_Pos(x, y);
}
void Ghost::setDir(int dir){
	direction = dir;
}
int Ghost::AIRandom(game_Obj& ghost, board& map) {
	bool* possible_Path = posibbleMoves(ghost, map);
	int x;

	//Looks for a valid move.

	do {
		x = rand() % 4;
	} while (!possible_Path[x]);

	moveObj(ghost, x, map);

	delete[] possible_Path;
	return x;
}
/// <summary>
/// moves an object a given direction, if possible.
/// </summary>
/// <param name="obj">the object</param>
/// <param name="direction">it's direction</param>
/// <param name="map">game map</param>
void Ghost::moveObj(game_Obj& obj, int direction, board& map) {
	int x_val, y_val;
	x_val = obj.get_x();
	y_val = obj.get_y();

	//Erase their last position.
	map.gotoxy(x_val, y_val);
	cout << map.getMapChar(x_val, y_val);

	//Update their new position.
	switch (direction) {
	case 0: --x_val; break;
	case 1: --y_val; break;
	case 2: ++x_val; break;
	case 3: ++y_val; break;
	}
	obj.set_Pos(x_val, y_val);
	map.gotoxy(map.getMapRow(), map.getMapCol());
}
void Ghost::moveObj(int direction, int mode, board& map) {
	const enum gameMode { Empty, save, load, silent, error };
	int x_val, y_val;
	x_val = gObj.get_x();
	y_val = gObj.get_y();

	if (mode != silent) {
		map.gotoxy(x_val, y_val);
		cout << map.getMapChar(x_val, y_val);
	}

	switch (direction) {
	case 0: gObj.set_Pos(position(--x_val,y_val)); break;
	case 1: gObj.set_Pos(position(x_val, --y_val)); break;
	case 2: gObj.set_Pos(position(++x_val, y_val)); break;
	case 3: gObj.set_Pos(position(x_val, ++y_val)); break;
	}
	if (mode != silent)
		map.gotoxy(map.getMapRow(), map.getMapCol());
}
bool* Ghost::posibbleMoves(game_Obj obj, board& map) {
	int x, y, i;
	bool* res = new bool[4];

	//Set all positions to be true.
	for (i = 0; i < 4; i++) {
		res[i] = true;
	}
	x = obj.get_Pos().get_x();
	y = obj.get_Pos().get_y();
	//Checks the valid moves per direction.
	if (x <= 0 || (map.getMapChar(x - 1, y) == '#' || map.getMapChar(x - 1, y) == '|' || map.getMapChar(x - 1, y) == 'G')) {
		res[0] = false;
	}
	if (y <= 0 || (map.getMapChar(x, y - 1) == '#' || map.getMapChar(x, y - 1) == '|' || map.getMapChar(x, y - 1) == 'G')) {
		res[1] = false;
	}
	if (x >= map.getMapRow() - 1 || (map.getMapChar(x + 1, y) == '#' || map.getMapChar(x + 1, y) == '|' || map.getMapChar(x + 1, y) == 'G')) {
		res[2] = false;
	}
	if (y >= map.getMapCol() - 1 || (map.getMapChar(x, y + 1) == '#' || map.getMapChar(x, y + 1) == '|' || map.getMapChar(x, y + 1) == 'G')) {
		res[3] = false;
	}
	return res;

}
/// <summary>
/// checks if the ghost was randomly moved to send him back to his path to Pac Man.(for good diffeculy)
/// </summary>
/// <returns>if he was moved randomly</returns>
bool Ghost::wasRandomlyMoved() {
	int x, y;

	if (walk_queue.size() != 0) {
		x = walk_queue.back().x;
		y = walk_queue.back().y;
	}
	else
		return true;
	if (x == gObj.get_x() && abs(y - gObj.get_y() == 1))
		return true;
	else if(y == gObj.get_y() && abs(x - gObj.get_x() == 1))
		return true;
	return false;

}
/// <summary>
/// finds the best path for the ghost to reach Pac Man.
/// </summary>
/// <param name="player">Pac Man</param>
/// <param name="map">The game Map</param>
void Ghost::smartGhostAI(game_Obj& player, board& map)
{

	bool moveG = true;
	enum move { UP, LEFT, DOWN, RIGHT };
	int x, y, min = direction;


	if ((wasRandomlyMoved()) || !(last_pac_man_pos.compare(last_pac_man_pos, player))) {
		FindPath(gObj.get_x(), gObj.get_y(), player.get_x(), player.get_y(), map);
		last_pac_man_pos = player;
	}

	 if (walk_queue.size() != 0) {
		x = walk_queue.back().x;
		y = walk_queue.back().y;
		walk_queue.pop_back();
	}
	else
		moveG = false;


	if (moveG) {

		if (x > gObj.get_x()) {
			min = DOWN;
		}
		else if (x < gObj.get_x()) {
			min = UP;
		}
		else if (y > gObj.get_y()) {
			min = RIGHT;
		}
		else {
			min = LEFT;
		}
	}

	direction = min;
}

