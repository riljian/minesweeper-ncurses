#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "cursesFunc.h"
#include "minesweeper.h"
using namespace std;

minesweeper::minesweeper(const char input, int Maxy, int Maxx){
	switch(input){
		case 'b':
			y = 9;
			x = 9;
			num_mine = 10;
			break;
		case 'i':
			y = 16;
			x = 16;
			num_mine = 40;
			break;
		case 'e':
			y = 16;
			x = 30;
			num_mine = 99;
	}
	win = x * y - num_mine;
	maxy = Maxy;
	maxx = Maxx;
}

minesweeper::~minesweeper(){
	ofstream output("Mine.txt", ios::out);
	int i, j;
	for(i=1;i<=y;i++){
		for(j=1;j<=x;j++)
			output << mine_map[i][j];
		output << endl;
	}
	output.close();
}

void minesweeper::howToPlay(){
	mvprintw(1, x+5, "Press ' ' to open a grid and start");
	mvprintw(2, x+5, "Press 'q' to quit");
	mvprintw(3, x+5, "Press 'f' to set a flag");
	mvprintw(4, x+5, "Press '/' to put a question mark");
	mvprintw(5, x+5, "Press 'h' to get a hint");
	mvprintw(6, x+5, "If you want to cancel them press again");
}

void minesweeper::setMap(int yy, int xx){
	int i, j, count=0;
	memset(mine_map, '0', sizeof(mine_map));
	initTime = time(NULL);
	srand(time(NULL));
	while(count<num_mine){
		i = rand()%y + 1;
		j = rand()%x + 1;
		if(mine_map[i][j]=='0'){
			if(i!=yy||j!=xx){
				mine_map[i][j] = 'B';
				count++;
			}
		}
	}
	for(i=1;i<=y;i++)
	for(j=1;j<=x;j++)
		if(mine_map[i][j]=='B')
			for(int k=i-1;k<=i+1;k++)
			for(int l=j-1;l<=j+1;l++)
				if(mine_map[k][l]!='B')
					mine_map[k][l]++;
}

int minesweeper::Press(int nowy, int nowx, char curMap[20][35], int* found){
	int i, j, result=0, count=0;
	if(curMap[nowy][nowx]==0&&mine_map[nowy][nowx]=='0'){
		when0(nowy, nowx, curMap, found);
		return 0;
	}
	else if(mine_map[nowy][nowx]=='B'&&curMap[nowy][nowx]!='F')
		return 1;
	else if(curMap[nowy][nowx]==0){
		move(nowy, nowx);
		switch(mine_map[nowy][nowx]){
			case '1':	printStrInColor(2,"1"); break;
			case '2':	printStrInColor(3,"2"); break;
			case '3':	printStrInColor(4,"3"); break;
			case '4':	printStrInColor(5,"4"); break;
			case '5':	printStrInColor(6,"5"); break;
			case '6':	printStrInColor(7,"6"); break;
			case '7':	printStrInColor(8,"7"); break;
			case '8':	printStrInColor(9,"8"); break;
			default:;
		}
		curMap[nowy][nowx] = mine_map[nowy][nowx];
		(*found)++;
		return 0;
	}
	else if((curMap[nowy][nowx]-'0')==FSuround(nowy, nowx, curMap)){
		for(i=nowy-1;i<=nowy+1;i++)
			for(j=nowx-1;j<=nowx+1;j++){
				if(i<1||i>y||j<1||j>x||curMap[i][j]!=0)
					continue;
				result += Press(i, j, curMap, found);
			}
		return result;
	}
	return 0;
}

void minesweeper::when0(int u, int v, char curMap[20][35], int* found){
	int i, j;
	for(i=u-1;i<=u+1;i++)
		for(j=v-1;j<=v+1;j++){
			if(i<1||i>y||j<1||j>x||curMap[i][j]!=0)
				continue;
			move(i, j);
			switch(mine_map[i][j]){
				case '0':	printStrInColor(12,"0"); break;
				case '1':	printStrInColor(2,"1"); break;
				case '2':	printStrInColor(3,"2"); break;
				case '3':	printStrInColor(4,"3"); break;
				case '4':	printStrInColor(5,"4"); break;
				case '5':	printStrInColor(6,"5"); break;
				case '6':	printStrInColor(7,"6"); break;
				case '7':	printStrInColor(8,"7"); break;
				case '8':	printStrInColor(9,"8"); break;
				default:;
			}
			curMap[i][j] = mine_map[i][j];
			(*found)++;
			if(curMap[i][j]=='0')
				when0(i, j, curMap, found);
		}
	return;
}

int minesweeper::pressB(char curMap[20][35]){
	for(int i=1;i<=y;i++)
		for(int j=1;j<=x;j++)
			if(curMap[i][j]==0||curMap[i][j]=='F'||curMap[i][j]=='?'){
				if(mine_map[i][j]=='B'){
					if(curMap[i][j]=='F'){
						move(i, j);
						printStrInColor(5, "O");
					}
					else{
						move(i, j);
						printStrInColor(1, "B");
					}
				}
				else{
					if(curMap[i][j]=='F'){
						move(i, j);
						printStrInColor(7, "X");
					}
					else{
						move(i, j);
						switch(mine_map[i][j]){
							case '0':	printStrInColor(12,"0"); break;
							case '1':	printStrInColor(2,"1"); break;
							case '2':	printStrInColor(3,"2"); break;
							case '3':	printStrInColor(4,"3"); break;
							case '4':	printStrInColor(5,"4"); break;
							case '5':	printStrInColor(6,"5"); break;
							case '6':	printStrInColor(7,"6"); break;
							case '7':	printStrInColor(8,"7"); break;
							case '8':	printStrInColor(9,"8"); break;
							default:;
						}
					}
				}
			}
	return 1;
}

int minesweeper::FSuround(int u, int v, char curMap[20][35]){
	int i, j, result=0;
	for(i=u-1;i<=u+1;i++)
		for(j=v-1;j<=v+1;j++){
			if(i<1||i>y||j<1||j>x)
				continue;
			if(curMap[i][j]=='F')
				result++;
		}
	return result;
}

void minesweeper::drawTable(){
	int i;
	for(i=1;i<=y+1;i++){
		mvaddch(i, 0, '|');
		mvaddch(i, x+1, '|');
	}
	for(i=1;i<=x;i++){
		mvaddch(0, i, '_');
		mvaddch(y+1, i, '_');
	}
	howToPlay();
	return;
}

void minesweeper::loseMessage(){
	int y, x;
	getmaxyx(stdscr, y, x);
	nodelay(stdscr, FALSE);
	mvprintw(y/2, (x-11)/2, "You Lose!!!");
	mvprintw(y/2+1, (x-20)/2, "Press q to continue.");
	refresh();
	while(getch()!='q');
}

void minesweeper::winMessage(){
	int y, x;
	getmaxyx(stdscr, y, x);
	nodelay(stdscr, FALSE);
	mvprintw(y/2, (x-10)/2, "You Win!!!");
	mvprintw(y/2+1, (x-20)/2, "Press q to continue.");
	refresh();
	while(getch()!='q');
}

long int minesweeper::getTime(){
	return time(NULL) - initTime;
}
