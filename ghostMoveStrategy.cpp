#include "ghostMoveStrategy.h"
/// <summary>
/// Moves the ghost based on the shortest route to Pac Man
/// </summary>
/// <param name="g">The ghost</param>
/// <param name="map">The game map</param>
/// <param name="pac_man">Pac Man</param>
void best::GhostAI(Ghost& g, board& map, game_Obj pac_man) {
	int  x;
	game_Obj obj = g.getObj();
	g.smartGhostAI(pac_man, map);
	x = g.getDir();
	g.moveObj(obj, x, map);
	g.setObj(obj);


}
/// <summary>
/// Moves the ghost smartly 20 moves and randomly 5 moves
/// </summary>
/// <param name="g">The ghost</param>
/// <param name="map">The game map</param>
/// <param name="pac_man">Pac Man</param>
void good::GhostAI(Ghost& g, board& map, game_Obj pac_man) {
	static int countFrames = 0;
	novice n;
	best b;
	if (countFrames < 20) 
			b.GhostAI(g, map, pac_man);
	else 
		n.GhostAI(g, map, pac_man);

	countFrames++;
	if (countFrames > 25) {
		countFrames = 0;
	}

}
/// <summary>
/// moves the ghost randomly
/// </summary>
/// <param name="g">The ghost</param>
/// <param name="map">The game map</param>
/// <param name="pac_man">Pac Man</param>
void novice::GhostAI(Ghost& g, board& map, game_Obj pac_man) {
	int x = g.getDir();
	game_Obj obj = g.getObj();
	bool* possible_moves = g.posibbleMoves(obj, map);
	if (possible_moves[x]) {
		g.moveObj(obj, x, map);
		g.setObj(obj);
	}
	else {
		g.setDir(g.AIRandom(obj, map));
		g.setObj(obj);
	}
	delete[] possible_moves;
}
