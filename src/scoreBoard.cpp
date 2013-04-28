#include <cstdio>
#include <ctime>
#include <cstring>
#include <ncurses.h>
#include <string>
#include <fstream>
#include "scoreBoard.h"
using namespace std;

void scoreBoard::readRecord(char level){
	struct record tmp;
	string fileName="record.dat";
	fileName.insert(fileName.begin()+6, level);
	ifstream fpr(fileName.c_str(), ios::in);
	while(fpr >> tmp.playerName >> tmp.usedTime)
		recordQueue.push(tmp);
	fpr.close();
}

void scoreBoard::setWinnerMessage(int maxx, long int utime){
	struct record tmp;
	nodelay(stdscr, FALSE);
	echo();
	keypad(stdscr, FALSE);
	tmp.usedTime = utime;
	while(1){
		erase();
		mvprintw(3, (maxx-10)/2, "You Win!!!");
		mvprintw(6, (maxx-24)/2, "Please input your name.");
		mvprintw(7, (maxx-20)/2, "(14 letters at most)");
		refresh();
		move(9, maxx/2-15);
		getstr(tmp.playerName);
		if(strlen(tmp.playerName)<=14)
			break;
		else{
			printw("\nYour name is too long. Please input 't' to try again.");
			while(getch()!='t');
		}
	}
	recordQueue.push(tmp);
	nodelay(stdscr, TRUE);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

void scoreBoard::showRecord(int maxy, int maxx, char level){
	char t;
	if(level==0){
		erase();
		mvprintw(maxy/2, maxx/2-13, "Whilch level do you want?");
		mvprintw(maxy/2+1, maxx/2-20, "b.Beginner | i.Intermediate | e.Expert");
		refresh();
		while((t=getch())!='b'&&t!='i'&&t!='e');
		level = t;
		readRecord(level);
	}
	erase();
	string fileName="record.dat";
	fileName.insert(fileName.begin()+6, level);
	ofstream fpr(fileName.c_str(), ios::out);
	struct record tmp;
	mvprintw(3, maxx/2-17, "Rank          Name      Used Time");
	for(int i=1;!recordQueue.empty()&&i<=maxy-8;i++){
		tmp = recordQueue.top();
		mvprintw(4+i, maxx/2-17, " %2d   %14s     %3d:%02d", i, tmp.playerName, tmp.usedTime/60, tmp.usedTime%60);
		fpr << tmp.playerName << " " << tmp.usedTime << endl;
		recordQueue.pop();
	}
	while(!recordQueue.empty())
		recordQueue.pop();
	mvprintw(maxy-1, maxx/2-11, "Input 't' to continue.");
	mvprintw(maxy-2, maxx/2-16, "Input 'd' to delete the record.");
	fpr.close();
	refresh();
	while((t=getch())!='t'&&t!='d');
	if(t=='d'){
		fpr.open(fileName.c_str(), ios::out);
		fpr.close();
	}
}
