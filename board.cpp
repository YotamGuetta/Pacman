#include "board.h"

void board::setMap(vector<string>& f_map ){
	file_map = f_map;
	use_file_map = true;
}

char board::getMapChar(int x, int y) const {
	if(use_file_map)
		return file_map[x][y];
	return map[x][y];
}
void board::setMapChar(int x, int y, char c) {
	if (use_file_map)
		file_map[x][y] = c;
	else
		map[x][y] = c;
}
char** board::copyBoard() {
	int i, j, row = this->getMapRow(), col = this->getMapCol();
	char** tmp_map = new char* [row];
	
	for (i = 0; i < row; i++) {
		tmp_map[i] = new char[col];
		for (j = 0; j < col; j++)
			if (use_file_map)
				tmp_map[i][j] = file_map[i][j];

			else
				tmp_map[i][j] = map[i][j];
	}
	return tmp_map;
	

}
void board::gotoxy(int x, int y)
{

	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { y, x };
	cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


const int board::getMapRow() {
	if (use_file_map)
		return file_map.size();
	return ROW_SIZE;
}
const int board::getMapCol() {
	if (use_file_map)
		return file_map[0].size();
	return COL_SIZE;
}
void board::printBoard() const {
	int i, j, f_row, f_col;
	
	if (use_file_map) {
		f_row = file_map.size();
		f_col = file_map[0].size();
		for (i = 0; i < f_row; i++) {
			for (j = 0; j < f_col; j++) {
				cout << file_map[i][j];
			}
			cout << "\n";
		}
	}
	else {
		for (i = 0; i < ROW_SIZE; i++) {
			for (j = 0; j < COL_SIZE; j++) {
				cout << map[i][j];
			}
			cout << "\n";
		}
	}
}