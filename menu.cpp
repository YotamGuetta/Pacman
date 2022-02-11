#include "menu.h"
#include <experimental/filesystem>

namespace filesys = std::experimental::filesystem;

void menu::errorMsg(string msg) {
	clearscreen();
	cout << "Error: " << msg << endl;
	exit(1);
}

bool compareFunction(std::string a, std::string b) { return a < b; }
/// <summary>
/// Finds the files that have a ".screen" ending.
/// </summary>
/// <returns> The files names</returns>
vector<string> getFilesList(string fileType)
{

	vector<string>fList;
	auto path = filesys::current_path();
	std::string ext(fileType);
	for (auto& p : filesys::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext) 
			fList.push_back(p.path().stem().string());

	}

	sort(fList.begin(), fList.end(), compareFunction);

	return fList;
}


/// <summary>
/// The menu If No Game file Was Found
/// </summary>
void  menu::noFilesFound(int mode) {
	bool isplaying = true;//while the played didn't send 0.
	char choice;//The player choice
	int diffeculty;
	unsigned int score = 0, lives = 3;
	ofstream result("pacman_00.result");
	ofstream steps("pacman_00.steps");
	while (isplaying) {
		clearscreen();
		cout << "*******************************************************" << endl;
		cout << "* No Game Files Were Found..."<< endl;
		cout << "* 1 - Play a default Board" <<endl;
		cout << "* 2 - Exit" << endl;
		cout << "* ******************************************************" << endl;
		cin >> choice;
		if (choice == '1') {
			diffeculty = diffecultyMenu();
			if (startGame(diffeculty, "", score, lives, result, steps, mode))
				playerWon(score);
			else
				playerLost(score);
		}
		else if (choice == '2')
			break;
		else {
			clearscreen();
			cin.clear();
		}
			
	}
}
/// <summary>
/// loads the files
/// </summary>
/// <param name="file_names">The screen files</param>
/// <param name="mode"> the game mode</param>
/// <returns>passed or not</returns>
bool menu::loadFile(vector<string> file_names, int mode) {
	unsigned int i, score = 0, lives = 3;
	ofstream result;
	ofstream steps;
	bool good_result = true;
	for (i = 0; i < file_names.size() && good_result; i++) {
		good_result = startGame(0, file_names[i], score, lives, result, steps, mode);
	}
	if (mode == load) {
		if (good_result)
			playerWonAllBoards(score);
		else
			playerLost(score);
	}
	return good_result;
}

/// <summary>
/// The main game menu
/// </summary>
void menu::gameMenu(int argc, char** argv) {
	vector<string> file_names;
	bool isplaying = true, load_result;//while the played didn't send 0.
	char choice;//The player choice
	InputParser input(argc, argv);
	int mode = input.getInput();
	switch (mode)
	{
	case error: cout << "Invalid input. please use: Pac_man.exe -save|-load [-silent]" << endl; return; break;
	case load:
	case silent:file_names = getFilesList(".screen");
		load_result = loadFile(file_names, mode);
		if (mode == silent) {
			if (load_result)
				cout << "Test Passed"<<endl;
			else {
				cout << "Test Failed"<<endl;
			}
		}return;
	}
	file_names = getFilesList(".screen");
	if (file_names.size() == 0) {
		noFilesFound(mode);
	}
	else {
		while (isplaying) {
			cout << "*******************************************************" << endl;
			cout << "* 1 - Play All game Borads" << endl;
			cout << "* 2 - Play A Specific Board" << endl;
			cout << "* 8 - Present instructions and keys" << endl;
			cout << "* 9 - EXIT" << endl;
			cout << "* *****************************************************" << endl;
			cout << "* Weclome to Pac-Man The Game" << endl;
			cin >> choice;
			switch (choice) {
			case '1':
				playAllGames(file_names, mode); break;
			case '2':
				boardsMenu(file_names, mode); break;
			case '8': presentInstructions(); break;//Prints the game instructions
			case '9': isplaying = false; break;//Exits the game.
			default: clearscreen();
				cin.clear();
				break;

			}
		}
	}

}
/// <summary>
/// The menu if a specific file was chosen
/// </summary>
/// <param name="file_names">The game board files</param>
void menu::boardsMenu(const vector<string>& file_names,int mode) {
	bool isplaying = true;//while the played didn't send 0.
	int i, diffeculty;//The player choice
	char choice;
	unsigned int score = 0, lives = 3;
	ofstream result;
	ofstream steps;
	diffeculty = diffecultyMenu();
	if (diffeculty == -1) {
		clearscreen();
		isplaying = false;
	}
	while (isplaying) {

		clearscreen();
		cout << "*******************************************************" << endl;
		cout << "*Choose a board:" << endl;
		cout << "* 0 - Go Back" << endl;
		for (i = 0; i < file_names.size(); i++) 
			cout << "* " << i + 1 << " - " << file_names[i] << endl;
		cout << "* ******************************************************" << endl;
		cout << "* Weclome to Pac-Man The Game" << endl;
		cin >> choice;
		if (choice == '0') {
			steps << choice;
			clearscreen();
			break;
		}
		if (choice - '0' <= file_names.size() && choice > '0') {
			if (mode == save) {
				steps.open(file_names[choice - '0' - 1] + ".steps");
				result.open(file_names[choice - '0' - 1] + ".result");
			}
			if (startGame(diffeculty, file_names[choice - '0'-1], score, lives, result, steps, mode))
				playerWon(score);
			else
				playerLost(score);
			break;
		}
		else {
			clearscreen();
			cin.clear();
		}
	}
	if (mode == save) {
		result.close();
		steps.close();
	}
}
/// <summary>
/// The menu if all files was chosen
/// </summary>
/// <param name="file_names">The game board files</param>
void menu::playAllGames(const vector<string>& file_names, int mode) {
	int diffeculty = diffecultyMenu();
	bool won = true;
	unsigned int i, score = 0, lives = 3;
	ofstream result;
	ofstream steps;
	if (diffeculty == -1) {
		clearscreen();
		return;
	}
	clearscreen();
	for (i = 0; i < file_names.size() && won; i++) {
		if (mode == save) {
			steps.open(file_names[i] + ".steps");
			result.open(file_names[i] + ".result");
		}
		won = startGame(diffeculty, file_names[i], score, lives, result, steps, mode);
		if (mode == save) {
			result.close();
			steps.close();
		}
	}
	if (won)
		playerWonAllBoards(score);
	else
		playerLost(score);
	
}

/// <summary>
/// The menu to choose the game diffeculty
/// </summary>
/// <returns>The diffeculty / -1 if wasn't chosen</returns>
int menu::diffecultyMenu() {
	char choice;//The player choice
	bool isplaying = true;//while the played didn't send 0.
	clearscreen();
	while (isplaying) {
		cout << "*******************************************************" << endl;
		cout << "Select diffeculty:" << endl;
		cout << "* 0 - Novice" << endl;
		cout << "* 1 - Good" << endl;
		cout << "* 2 - Best" << endl;
		cout << "* 9 - Back" << endl;
		cout << "* ******************************************************" << endl;
		cin >> choice;
		switch (choice) {
		case '0':
		case '1':
		case '2':
			return choice - '0';
		case '9':
			return -1;
		default: clearscreen();
			cin.clear();
			break;
		}
	}
		
}
/// <summary>
/// game instructions
/// </summary>
void menu::presentInstructions() {
	clearscreen();
	cout << "Objective: clear all bread crumbs as Pac-Man without hitting ghosts, If your lives turns to 0 you LOSE :(" << endl;
	cout << "Keys: arrows: a - left" << endl << "              d - right" << endl << "              w - up" << endl << "              x - down" << endl << "      s - stop" << endl << "      ESC - pause" << endl;
}
/// <summary>
/// count the given board number of breadcrumbs
/// </summary>
/// <param name="map"></param>
/// <returns></returns>
int menu::countBreadCrumbs(board& map) {
	int i, j, count = 0;
	for (i = 0; i < map.getMapRow(); i++)
		for (j = 0; j < map.getMapCol(); j++)
			if (map.getMapChar(i, j) == '.')
				++count;
	return count;
}


/// <summary>
/// converts the char read from the file to a was of the game.
/// </summary>
/// <param name="newBoard"> The game board</param>
/// <param name="c">The char in the file </param>
/// <param name="col">the column</param>
/// <param name="row">the row</param>
/// <param name="doSkip20"> if the UI was found (&)</param>
/// <param name="scorePos">the UI cord</param>
void menu::CheckBoardChar(vector<string>& newBoard, char c, int col, int row, bool& doSkip20, position& scorePos, int& count_ghosts, bool& onePacman) {
	int strSize = newBoard[row].size();
	switch (c) {
	case '#': newBoard[row] += '#'; break;
	case '%':newBoard[row] += ' '; break;
	case '@':
		if (!onePacman) {
			newBoard[row] += 'P';
			onePacman = true;
		}
		else
			errorMsg("board can't have more then 1 Pacman");
		break;
	case '$':
		if (count_ghosts < 4) {
			newBoard[row] += 'G';
			count_ghosts++;
		}
		else
			errorMsg("board can't have more then 4 Ghosts");
		break;
	case'&': newBoard[row] += '#';
		scorePos.set_x(row);
		scorePos.set_y(col);
		doSkip20 = true;
		break;
	default: newBoard[row] += '.'; break;
	}
}



/// <summary>
/// reads the file to a string array with proper charecters
/// </summary>
/// <param name="fileName">The file name</param>
/// <param name="score">The position of the UI (returned value)</param>
/// <param name="size"> (returned value)</param>
/// <param name="newBoard"> (returned value)</param>
/// <param name="colSize"> (returned value)</param>
/// <param name="rowSize">(returned value)</param>
void menu::readBoardfromFile(const string& fileName, position& score, int& size, vector<string>& newBoard, int& colSize, int& rowSize) {

	ifstream infile;
	position scorePos;
	int i, j, count_ghosts = 0;
	char line[200];
	bool doSkip20 = false, gotColSize = false, gotRowSize = false, onePacMan = false;
	int row = 0;
	string file_tr = fileName + ".screen";

	colSize = 1;
	infile.open(file_tr);
	if(!infile) 
		errorMsg("The screen "+ fileName +" file failed to open");

	while (infile.getline(line, 200)) {
		newBoard.push_back("");
		for (i = 0; line[i] != '\0' && i < 80 && (row == 0 || i < colSize); i++) {
			if (row == 0) {
				colSize++;
				CheckBoardChar(newBoard, line[i], i, row, doSkip20, scorePos, count_ghosts, onePacMan);
			}
			else if(i< colSize)
				CheckBoardChar(newBoard, line[i], i, row, doSkip20, scorePos, count_ghosts, onePacMan);
		}
		if (i != colSize - 1)
			errorMsg("invalid screen file " + fileName);
		row++;
	}
	row--;
	
	if (doSkip20) {
		for (i = scorePos.get_x(); i < scorePos.get_x() + 3; i++) {
			if (row < i) {
				newBoard.push_back("");
				row++;
			}
			for (j = scorePos.get_y(); j < scorePos.get_y() + 20; j++) {
				if (newBoard[i].size() <= j)
					newBoard[i] += ' ';
				else
					newBoard[i][j] = ' ';
			}


			while (newBoard[i].size() <= j && j < colSize - 1) {
				newBoard[i] += '.';
				j++;
			}
			score = scorePos;
		}
	}
	
	size = row;
	infile.close();
}

/// <summary>
/// finds the position of objects in the board.
/// </summary>
/// <param name="new_board"></param>
/// <param name="scorePos"></param>
/// <param name="boardSize"></param>
/// <param name="pos_size"></param>
/// <returns></returns>
position* menu::readBoard(vector<string>& new_board, position& scorePos, int boardSize, int& pos_size) {
	int i, j,  currPosSize = 2;
	bool found_Obj = false;
	position* items = new position[6], temp;
	items[0] = scorePos;
	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < new_board[i].size(); j++) {
			if (new_board[i][j] == 'P') {
				found_Obj = true;
				break;
			}
		}
		if (found_Obj)
			break;
	}
	new_board[i][j] = ' ';
	temp.set_x(i);
	temp.set_y(j);
	items[1] = temp;

	for (i = 0; i < boardSize && currPosSize <= 6; i++) {
		for (j = 0; new_board[i][j] != '\0'; j++) {

			if (new_board[i][j] == 'G') {
				new_board[i][j] = ' ';
				temp.set_x(i);
				temp.set_y(j);
				items[currPosSize] = temp;
				currPosSize++;
			}
		}
	}
	pos_size = currPosSize;
	return items;
}
void printUI(position pos, board& map) {
	int i;
	i = pos.get_x();
	map.gotoxy(i, pos.get_y());
	cout << "press a key to start";
	map.gotoxy(i+1, pos.get_y());
	cout << "Score: 0            ";
	map.gotoxy(i+2, pos.get_y());
	cout << "Lives: 3            ";
	map.gotoxy(map.getMapRow(), map.getMapCol());
}
void copy_line_to_board(board& map, int x, int y, string line) {
	for (int i = 0; line[i] != '\0'; i++) {
		map.setMapChar(x, y+i, line[i]);
	}
}
/// <summary>
/// gets the fruit cordinates and value
/// </summary>
/// <param name="word">the values that where saved</param>
/// <param name="ind">read from</param>
/// <returns>the value as int</returns>
int menu::findNumberFrom(const string& word, int& ind) {
	int x;
	x = word[ind] - '0';
	ind++;
	if (word[ind] != ',' && word[ind] != ')') {
		x *= 10;
		x += word[ind] - '0';
		ind++;
	}
	ind++;
	return x;
}

/// <summary>
/// checks if the ghost hit Pacman:
/// if he was hit reset the positions
/// if it didn't happend in silent mode or if Pacman ran out of lives return false
/// </summary>

bool menu::pac_man_Did_Not_Hit_A_Ghost(game_Obj & pac_man, vector<Ghost>&game_ghosts, int mode, unsigned int& pac_man_lives, position * start_pos, int Psize, board & map, ifstream & result_f, ofstream & result, int& countframe) {
	int i, x;
	entity en;
	string res_word;
	if (en.hitsTheGhost(game_ghosts, pac_man)) {
		--pac_man_lives;
		if (mode != silent) {
			if (mode == save)
				result << "died: " << countframe << ' ';
				//Reset to the starting positions.
			pac_man.set_Pos(start_pos[1]);
			for (i = 2; i < Psize; i++) {

				game_ghosts[i - 2].resetGhost(start_pos[i], map);
			}
			printUI(start_pos[0], map);
			map.gotoxy(start_pos[0].get_x(), start_pos[0].get_y());
			cout << "                     ";


			map.gotoxy(start_pos[0].get_x() + 2, start_pos[0].get_y() + 7);
			cout << pac_man_lives;
			return false;
		}
		else {
			if (result_f >> res_word) {//checks if the results match.
				if (res_word != "died:")
					return false;
				if (result_f >> res_word) {
					x = stoi(res_word);
					if (x != countframe)
						return false;
				}
				else
					return false;

			}
			else
				return false;
		}
		if (!pac_man_lives) {//checks if the results match.
			if (result_f >> res_word)
				return false;
			return true;
		}
		//Reset to the starting positions.
		pac_man.set_Pos(start_pos[1]);
		for (i = 2; i < Psize; i++) {
			game_ghosts[i - 2].set_Pos(start_pos[i].get_x(), start_pos[i].get_y());
		}
	}
	return true;
}



/// <summary>
/// This function playes the game and ends when the player won/lost.
/// </summary>
/// <returns>True if the player won, false if he lost</returns>
bool menu::startGame(int diffeculty, const string& file_Name, unsigned int& score, unsigned int& pac_man_lives, ofstream& result, ofstream& steps, int mode) {
	ifstream steps_f;
	ifstream result_f;

	//read the result and steps file if load mode or silent mode
	if (mode == load || mode == silent) {
		steps_f.open(file_Name + ".steps");
		result_f.open(file_Name + ".result");
		if (!(steps_f && result_f)) {
			errorMsg("The steps or result file of " + file_Name +" failed to open" );
		}
	}

	int Vsize,Rsize, Csize, Psize, i, total_breadcrumbs, curr_breadcrumbs = 0;
	position* p, scoreT;
	vector<Ghost> game_ghosts;
	vector<string> b;
	string number;
	char** g_board;
	int countframe = 0, x, y, v;
	string word, res_word;
	bool pWon = false, ghost_turn = true, fruitEaten = false, did_not_hit_a_ghost;//The fist parameter checks if the player won. The second moves the ghosts one at a time.
	char comm, newComm, newkey;//The first parameter is the user last valid key pressed. The second is the last key the player pressed.
	fruit fr;
	entity en;
	board map;
	game_Obj pac_man(10, 10);
	// defult screen
	if (file_Name == "" || file_Name =="pacman_00") {
		p = new position[4];
		p[0].set_xy(ROW_SIZE - 5,1);
		p[1].set_xy(10, 10);
		p[2].set_xy(2, 3);
		p[3].set_xy(2, 7);
		Psize = 4;
	}
	else {

		readBoardfromFile(file_Name, scoreT, Vsize, b, Csize, Rsize);
		p = readBoard(b, scoreT, Vsize, Psize);
		map.setMap(b);
	}

	if (mode != silent) {
		clearscreen();//clears the screen.
		map.printBoard();//prints the game frame.
	}
	comm = newComm = S;
	total_breadcrumbs = countBreadCrumbs(map);
	
	pac_man.set_Pos(p[1]);
	for (i = 2; i < Psize; i++) {
		game_ghosts.push_back(p[i]);
	}

	// print UI
	if (mode != silent) {
		printUI(p[0], map);
		copy_line_to_board(map, p[0].get_x() + 1, p[0].get_y(), "Score: ");
		copy_line_to_board(map, p[0].get_x() + 2, p[0].get_y(), "Lives: ");
	}

	while (!(_kbhit()) && mode != silent && mode != load)//Awaits for the player to press any key.
		Sleep(500);
	if (mode != silent) {
		map.gotoxy(p[0].get_x(), p[0].get_y());
		cout << "                    ";
	}
	while (!pWon) {//As long as the player didn't win.

		if (mode == save) {
			if (countframe % 20 == 19) {
				steps << endl;
			}
		}


		if (mode != silent) {
			map.gotoxy(map.getMapRow(), map.getMapCol());
			Sleep(200);//Waits before continuing to the next command.
		}

		if (mode != silent && mode != load) {
			if (_kbhit())//Adds the new key pressed value.
				newComm = getKey();
		}

		//If the player presseed ESC pause the game until he presses it again.
		if (newComm == ESC) {

			//Pause message.
			map.gotoxy(p[0].get_x(), p[0].get_y());
			cout << "Paused - Press Esc  ";
			newkey = 0;
			while (newComm != newkey)
			{
				Sleep(500);
				if (_kbhit())
					newkey = getKey();
			}

			//Removes pause message.
			map.gotoxy(p[0].get_x(), p[0].get_y());
			cout << "                    ";
			newComm = 0;
		}


		if (newComm == LEFT || newComm == RIGHT || newComm == UP || newComm == DOWN || newComm == S || newComm == LEFT2 || newComm == RIGHT2 || newComm == UP2 || newComm == DOWN2 || newComm == S2)
			comm = newComm;//Checks if the key is an arrow key or S.
		//read Pacman's step from file
		if (mode == load || mode == silent) {
			if (word.size() != 0 || steps_f >> word) {
				if (word == "LEFT") {
					comm = LEFT;
					word.clear();
				}
				else if (word == "RIGHT") {
					comm = RIGHT;
					word.clear();
				}
				else if (word == "UP") {
					comm = UP;
					word.clear();
				}
				else if (word == "DOWN") {
					comm = DOWN;
					word.clear();
				}
				else if (word == "S") {
					comm = S;
					word.clear();
				}
			}
		}

		en.movePac_Man(pac_man, comm, map, steps, mode);//Move the pac man on the last arrow stroke direction.


		//If the Pac Man hit a ghost substract a life. If he ran out of lives or the silent test faild - end with a lost.
		did_not_hit_a_ghost = pac_man_Did_Not_Hit_A_Ghost(pac_man, game_ghosts, mode, pac_man_lives, p, Psize, map, result_f, result, countframe);
		if (did_not_hit_a_ghost) {
			if (mode == silent && !pac_man_lives)
				return true;
		}
		else if (mode != silent) {
			if (!pac_man_lives)
				return false;
		}
		else
			return false;
		
		
		//Update the score.
		
		if (map.getMapChar(pac_man.get_x(), pac_man.get_y()) == '.') {
			map.setMapChar(pac_man.get_x(), pac_man.get_y(), ' ');
			++score;
			++curr_breadcrumbs;
		}
		if (mode != silent) {
			map.gotoxy(p[0].get_x() + 1, p[0].get_y() + 7);
			cout << score;
		}

		//Win condition.
		if (curr_breadcrumbs == total_breadcrumbs) {
			if (mode == save)
				result << "Finished_Screen: " << countframe << ' ';
			if (mode == silent) {
				if (result_f >> res_word) {
					if (res_word == "Finished_Screen:") {
						if (result_f >> res_word) {
							x = stoi(res_word);
							if (x == countframe)
								return true;
						}
					}
				}
				return false;
			}
			pWon = true;
			break;
		}

		//read fruit position or step
		if (word.size() != 0 || steps_f >> word) {
			i = 0;
			if (word[i] == '(') {
				i++;
				x = findNumberFrom(word, i);
				y = findNumberFrom(word, i);
				v = findNumberFrom(word, i);
				fr.makeFruit(x, y, v, mode, map);
				word.clear();
			}
			else if (word[i] == 'f') {
				if (!(fr.moveFruit(word[1] - '0', mode, map))) 
					errorMsg("Moving a none exsisting fruit");
				
				word.clear();
			}
		}

		if(mode != silent && mode != load)
			fr.updateFruit(map, pac_man, game_ghosts, score, steps, mode);
		

		//Moves each ghost one at a time and pac man with swiching symbles.
		if (ghost_turn) {

			ghost_turn = false;
			if (mode != silent && mode != load) {
				if (Psize >= 4) {
					en.moveGhost(game_ghosts[1], map, pac_man, diffeculty);
					if (mode == save)
						steps <<  game_ghosts[1].getDir() << ' ';
					if (Psize == 6) {
						en.moveGhost(game_ghosts[3], map, pac_man, diffeculty);
						if (mode == save)
							steps <<  game_ghosts[3].getDir() << ' ';
					}
				}
			}
			else {//load silent mode
				if (word.size() != 0 || steps_f >> word) {
					if (Psize >= 4 && word.size() == 1 && word != "S") {
						game_ghosts[1].setDir(word[0] - '0');
						x = game_ghosts[1].getDir();
						game_ghosts[1].moveObj(x, mode, map);
						word.clear();
					}
				}
				if (word.size() != 0 || steps_f >> word) {
					if (Psize == 6 && word.size() == 1 && word != "S") {
						game_ghosts[3].setDir(word[0] - '0');
						x = game_ghosts[3].getDir();
						game_ghosts[3].moveObj(x, mode, map);
						word.clear();
					}
				}

			}
			if (mode != silent)
				en.printGameObj(pac_man, 'C');
		}
		else {
			ghost_turn = true;
			if (mode != silent && mode != load) {
				if (Psize >= 3) {
					en.moveGhost(game_ghosts[0], map, pac_man, diffeculty);
					if (mode == save)
						steps <<  game_ghosts[0].getDir() << ' ';

					if (Psize >= 5) {
						en.moveGhost(game_ghosts[2], map, pac_man, diffeculty);
						if (mode == save)
							steps <<  game_ghosts[2].getDir() << ' ';
					}
				}
			}
			else {//load silent mode
				if (word.size() != 0 || steps_f >> word) {
					if (Psize >= 3 &&word.size() == 1 && word != "S") {
						game_ghosts[0].setDir(word[0] - '0');
						x = game_ghosts[0].getDir();
						game_ghosts[0].moveObj(x, mode, map);
						word.clear();
					}
				}
				if (word.size() != 0 || steps_f >> word) {
					if (Psize >= 5 && word.size() == 1 && word != "S") {
						game_ghosts[2].setDir(word[0] - '0');
						x = game_ghosts[2].getDir();
						game_ghosts[2].moveObj(x, mode, map);
						word.clear();
					}
				}

			}
			if (mode != silent)
				en.printGameObj(pac_man, 'O');
		}
		if (mode != silent) 
			en.printGameObj(game_ghosts);//prints the current ghosts position.

		//check if he was hit afther the ghost moved for a more accurate result.
		did_not_hit_a_ghost = pac_man_Did_Not_Hit_A_Ghost(pac_man, game_ghosts, mode, pac_man_lives, p, Psize, map, result_f, result, countframe);
		if (did_not_hit_a_ghost) {
			if (mode == silent && !pac_man_lives)
				return true;
		}
		else if (mode != silent) {
			if (!pac_man_lives)
				return false;
		}
		else
			return false;
		countframe++;
	}
	return pWon;
}
/// <summary>
/// won all game boards message
/// </summary>
/// <param name="score"></param>
void menu::playerWonAllBoards(unsigned int score) {
	clearscreen();
	char key;
	board map;
	map.gotoxy(2, 5);
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "	             Well Done !! You Won All The Game Boards" << endl;
	cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "                  Your Score Is : " << score << endl;
	cout << "                       Press Any Key To Continue." << endl;
	map.gotoxy(10, 0);
	while (!(_kbhit()))//Awaits for the player to press any key.
		Sleep(500);
	key = getKey();
	clearscreen();
}
/// <summary>
///  Prints the victory message.
/// </summary>
void menu::playerWon(unsigned int score) {
	char key;	
	board map;
	clearscreen();
	map.gotoxy(2, 5);
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "	             YOU WON" << endl;
	cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "          Your Score Is :" << score << endl;
	cout << "         Press Any Key To Continue." << endl;
	map.gotoxy(8, 0);
	while (!(_kbhit()))//Awaits for the player to press any key.
		Sleep(500);
	key = getKey();
	clearscreen();
}
/// <summary>
/// Prints the defeat message.
/// </summary>
void menu::playerLost(unsigned int score) {
	char key;
	board map;
	clearscreen();
	map.gotoxy(2, 5);
	cout << "##################################" << endl;
	cout << "  	            GAME OVER" << endl;
	cout << "     ##################################" << endl;
	cout << "          Your Score Is :" << score << endl;
	cout << "         Press Any Key To Continue." << endl;
	map.gotoxy(8, 0);
	while (!(_kbhit()))//Awaits for the player to press any key.
		Sleep(500);
	key = getKey();
	clearscreen();
}

/// <summary>
/// This function gets keyCodes for special keys such as arrows , escape and others
/// </summary>
/// <returns>It returns the Key code such as 72 for arrow up, 27 for Escape... </returns>
int menu::getKey()
{
	char KeyStroke = _getch();
	if (KeyStroke == 0 || KeyStroke == -32)
		KeyStroke = _getch();
	return (KeyStroke);
}


/// <summary>
/// This function clears the board.
/// </summary>
void menu::clearscreen() {
	system("cls");
}