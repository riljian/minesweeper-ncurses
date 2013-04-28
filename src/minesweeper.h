#ifndef mine_h
#define mine_h

#include <ctime>

class minesweeper{
	public:
		minesweeper(const char, int, int);
		~minesweeper();
		void setMap(int, int);
		void drawTable();
		int Press(int ,int ,char[20][35], int*);
		int pressB(char [20][35]);
		void winMessage();
		void loseMessage();
		long int getTime();
		char mine_map[20][35];
		int num_mine, win, y, x;
	private:
		int FSuround(int ,int ,char [20][35]);
		void when0(int, int, char [20][35], int*);
		void howToPlay();
		time_t initTime;
		int maxy, maxx;
};

#endif
