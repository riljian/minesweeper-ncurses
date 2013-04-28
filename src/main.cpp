#include <cstring>
#include "cursesFunc.h"
#include "minesweeper.h"
#include "processInput.h"
#include "scoreBoard.h"
using namespace std;

int main(){
	int maxy, maxx, y, x, first, count_time, found;
	char curMap[20][35], method;
	chtype c;
	cursesInit();
	getmaxyx(stdscr, maxy, maxx);
	while(1){
		scoreBoard winBoard;
		nodelay(stdscr, TRUE);
		erase();
		memset(curMap, 0, sizeof(curMap));
		x = y = first = 1;
		found = 0;
		printMiddle("What do you want ? q.Quit | p.Play | r.Record");
		mvprintw(maxy/2+1, maxx/2-12, "Please press q , p or r");
		while((method = getch())!='q'&&method!='p'&&method!='r');
		if(method=='r'){
			winBoard.showRecord(maxy, maxx);
			erase();
			refresh();
		}
		if(method=='q'){
			endwin();
			return 0;
		}
		printMiddle("Level: b.Beginner | i.Intermediate | e.Expert | q.Quit");
		mvprintw(maxy/2+1, maxx/2-13, "Please press b, i, e or q");
		while((method = getch())!='b'&&method!='i'&&method!='e'&&method!='q');
		if(method=='q'){
			endwin();
			return 0;
		}
		minesweeper game(method, maxy, maxx);
		erase();
		game.drawTable();
		mvaddstr(game.y+4, 0, "Time you have used :");
		mvprintw(game.y+5, 0, "Still have %2d mines.", game.num_mine);
		while(1){
			move(y, x);
			c = getch();
			if(c==' '&&first){
				game.setMap(y, x);
				first = 0;
			}
			count_time++;
			if(first==0 && !(count_time%25000))
				mvprintw(game.y+4, 22, "%03d:%02d", game.getTime()/60, game.getTime()%60);
			if(processInput(c, &y, &x, &game, curMap, &found)){
				game.loseMessage();
				break;
			}
			if(found == game.win){
				winBoard.readRecord(method);
				winBoard.setWinnerMessage(maxx, game.getTime());
				winBoard.showRecord(maxy, maxx, method);
				break;
			}
		}
	}
}
