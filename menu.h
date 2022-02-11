#pragma once
#include "fruit.h"
class menu {
	void noFilesFound(int mode);
	int diffecultyMenu();
	void presentInstructions();
	void boardsMenu(const vector<string>& file_names, int mode);
	void playAllGames(const vector<string>& file_names, int mode);
	bool startGame(int diffeculty, const string& file_Name, unsigned int& score, unsigned int& pac_man_lives, ofstream& result, ofstream& steps, int mode);
	void playerWon(unsigned int score);
	void playerLost(unsigned int score);
	void playerWonAllBoards(unsigned int score);
	void clearscreen();
	bool loadFile(vector<string> file_names, int mode);
	int getKey();
	void errorMsg(string msg);
	void readBoardfromFile(const string& fileName, position& score, int& size, vector<string>& newBoard, int& colSize, int& rowSize);
	void CheckBoardChar(vector<string>& newBoard, char c, int col, int row, bool& doSkip20, position& scorePos, int& count_ghosts, bool& onePacman);
	int countBreadCrumbs(board& map);
	position* readBoard(vector<string>& new_board, position& scorePos, int boardSize, int& pos_size);
	int findNumberFrom(const string& word, int& ind);
	bool pac_man_Did_Not_Hit_A_Ghost(game_Obj& pac_man, vector<Ghost>& game_ghosts, int mode, unsigned int& pac_man_lives, position* start_pos, int Psize, board& map, ifstream& result_f, ofstream& result, int& countframe);
public:
	void gameMenu(int argc, char** argv);
};