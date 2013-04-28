#include <cstdio>
#include "processInput.h"
#include "cursesFunc.h"
#include "minesweeper.h"
#define curMapyx curMap[*y][*x]

int processInput(chtype c, int* y, int* x, minesweeper* game, char curMap[20][35], int* found){
	int T=10000;
	switch(c){
		case 'q':
			return 1;
		case KEY_LEFT:
			--*x;
			if(*x<1)
				*x += game->x;
			break;
		case KEY_RIGHT:
			++*x;
			if(*x>game->x)
				*x -= game->x;
			break;
		case KEY_UP:
			--*y;
			if(*y<1)
				*y += game->y;
			break;
		case KEY_DOWN:
			++*y;
			if(*y>game->y)
				*y -= game->y;
			break;
		case 'f':
			if(curMapyx=='F'){
				addch(' ');
				curMapyx = 0;
				game->num_mine++;
				mvprintw(game->y+5, 11, "%2d", game->num_mine);
			}
			else if(game->num_mine<=0)
				break;
			else if(curMapyx==0||curMapyx=='?'){
				printStrInColor(7, "F");
				curMapyx = 'F';
				game->num_mine--;
				mvprintw(game->y+5, 11, "%2d", game->num_mine);
			}
			break;
		case 'h':
			T=10000;
			if(game->mine_map[*y][*x]=='B')
				while(T--){
					move(8, game->x+5);
					printStrInColor(7, "B");
					refresh();
				}
			else
				while(T--){
					mvprintw(8, game->x+5, "Safe");
					refresh();
				}
			mvprintw(8, game->x+5, "    ");
			break;
		case '/':
			if(curMapyx==0){
				addch('?');
				curMapyx = '?';
			}
			else if(curMapyx=='?'){
				addch(' ');
				curMapyx = 0;
			}
			break;
		case ' ':
			if(curMapyx=='F')
				break;
			else if(game->Press(*y, *x, curMap, found))
				return game->pressB(curMap);
	}
	refresh();
	return 0;
}
