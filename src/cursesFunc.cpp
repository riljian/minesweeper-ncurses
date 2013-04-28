#include <ncurses.h>
#include <cstring>
#include "cursesFunc.h"

void cursesInit(){
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_BLACK);
	init_pair(8, COLOR_YELLOW, COLOR_BLUE);
	init_pair(9, COLOR_BLUE, COLOR_RED);
	init_pair(12, COLOR_BLACK, COLOR_WHITE);
}

void printStrInColor(int i, const char *str){
	attron(COLOR_PAIR(i));
	addstr(str);
	attroff(COLOR_PAIR(i));
}

void printMiddle(const char *str){
	int x, y;
	erase();
	getmaxyx(stdscr, y, x);
	mvaddstr(y/2, (x-strlen(str))/2, str);
	refresh();
}
