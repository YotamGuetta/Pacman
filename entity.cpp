#include "entity.h"






/// <summary>
/// This function prints the ghosts on the screen.
/// </summary>
/// <param name="snake">the ghosts array</param>
void entity::printGameObj(vector<Ghost> ghosts) {
	int i;
	board map;
	for (i = 0; i < ghosts.size(); i++) {
		map.gotoxy(ghosts[i].get_x(), ghosts[i].get_y());//Points the cursor at the current ghost location. Then prints 'n' there.
		cout << "n";
		map.gotoxy(map.getMapRow(), map.getMapCol());//Resets the cursor position.
	}

}

/// <summary>
/// This function prints Pac Man on the screen.
/// </summary>
/// <param name="pac_man">Pac Man with his position</param>
/// <param name="avatar">Pac Man symble</param>
void entity::printGameObj(const game_Obj& pac_man, const char& avatar) {
	board map;
	map.gotoxy(pac_man.get_x(), pac_man.get_y());//Points the cursor at Pac Man current location. Then prints his symble there.
	cout << avatar;
	map.gotoxy(map.getMapRow(), map.getMapCol());//Resets the cursor position.

}

/// <summary>
/// Moves the ghosts randomly.
/// </summary>
/// <param name="ghost">The ghosts positions</param>
void entity::moveGhost(Ghost& ghost, board& map, game_Obj& pac_man, int diff) {
	novice n;
	good g;
	best b;
	switch (diff)
	{
	case 0: n.GhostAI(ghost, map, pac_man); break;
	case 1: g.GhostAI(ghost, map, pac_man); break;
	case 2: b.GhostAI(ghost, map, pac_man); break;
	}
	
	
}



/// <summary>
/// Moves Pac_Man to the given position
/// </summary>
/// <param name="pac_man">Pac_Man</param>
/// <param name="toX">Given x to go to</param>
/// <param name="toY">Given y to go to</param>
/// <param name="map">The game map</param>
void entity::movePac_ManTo(game_Obj& pac_man, int toX, int toY, board& map, int mode) {
	int x_val = pac_man.get_x();
	int y_val = pac_man.get_y();
	if (mode != silent) {
		map.gotoxy(x_val, y_val);
		cout << map.getMapChar(x_val, y_val);
		map.gotoxy(map.getMapRow(), map.getMapCol());
	}
	pac_man.set_Pos(toX, toY);

}
/// <summary>
/// Moves Pac Man based on the last key stroke
/// </summary>
/// <param name="pac_man">Pac Man</param>
/// <param name="comm">Last key stroke</param>
void entity::movePac_Man(game_Obj& pac_man, char comm, board& map, ofstream& steps, int mode) {
	Ghost g;
	int x_val, y_val;
	bool* possible_Path = g.posibbleMoves(pac_man, map);
	x_val = pac_man.get_x();
	y_val = pac_man.get_y();

	switch (comm) {//Moves based on the key.
	case UP:
	case UP2:if (mode == save)
		steps << "UP" << ' ';
		if (possible_Path[0])
		movePac_ManTo(pac_man, --x_val, y_val, map, mode);
		   else
		if (x_val == 0 && map.getMapChar(map.getMapRow() - 1, y_val) != '#')
			movePac_ManTo(pac_man, map.getMapRow() - 1, y_val, map, mode); break;//moves throw invisible tunnel.

	case LEFT:
	case LEFT2:if (mode == save)
		steps << "LEFT"<< ' ';
		if (possible_Path[1])
		movePac_ManTo(pac_man, x_val, --y_val, map, mode);
			 else
		if (y_val == 0 && map.getMapChar(x_val, map.getMapCol() - 1) != '#')
			movePac_ManTo(pac_man, x_val, map.getMapCol() - 1, map, mode); break;//moves throw invisible tunnel.
	case DOWN:
	case DOWN2:if (mode == save)
		steps << "DOWN" << ' ';
		if (possible_Path[2])
		movePac_ManTo(pac_man, ++x_val, y_val, map, mode);
			 else
		if (x_val == map.getMapRow() - 1 && map.getMapChar(0, y_val) != '#')
			movePac_ManTo(pac_man, 0, y_val, map, mode); break; //moves throw invisible tunnel.	
	case RIGHT:
	case RIGHT2:if (mode == save)
		steps << "RIGHT" << ' ';
		if (possible_Path[3])
		movePac_ManTo(pac_man, x_val, ++y_val, map, mode);
			  else
		if ((y_val == map.getMapCol() - 1) && map.getMapChar(x_val, 0) != '#')
			movePac_ManTo(pac_man, x_val, 0, map, mode); break;//moves throw invisible tunnel.
	case S:
	case S2: if (mode == save)
		steps  << "S" << ' ';
		break;

	}
	delete[] possible_Path;
}
/// <summary>
/// Checks if a ghost hit Pac Man
/// </summary>
/// <param name="ghost">ghosts list</param>
/// <param name="pac_man">Pac Man</param>
/// <returns>true if he was hit, false otherwise</returns>
bool entity::hitsTheGhost(vector<Ghost> ghost, const game_Obj& pac_man) {
	int p_x, p_y, g_x, g_y, g_dir;
	enum move { UP, LEFT, DOWN, RIGHT };
	p_x = pac_man.get_x();
	p_y = pac_man.get_y();

	for (int i = 0; i < ghost.size(); i++) {
		g_x = ghost[i].get_x();
		g_y = ghost[i].get_y();
		g_dir = ghost[i].getDir();
		//if (ghost[i].get_x() == pac_man.get_x() && ghost[i].get_y() == pac_man.get_y())
		//	return true;
		if (g_x == p_x && g_y == p_y)
			return true;
		/*switch (g_dir)
		{
		case UP: if (--g_x == p_x && g_y == p_y)
			return true;
			break;
		case DOWN: if (++g_x == p_x && g_y == p_y)
			return true;
			break;
		case LEFT: if (g_x == p_x && --g_y == p_y)
			return true;
			break;
		case RIGHT: if (g_x == p_x && ++g_y == p_y)
			return true;
			break;

		}*/
	}
	return false;
}
bool entity::hitsTheGhost(game_Obj ghost, const game_Obj& pac_man) {
	if (ghost.get_x() == pac_man.get_x() && ghost.get_y() == pac_man.get_y())
		return true;
	return false;
}
