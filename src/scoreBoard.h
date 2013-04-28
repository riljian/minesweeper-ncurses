#ifndef scoreBoard_h
#define scoreBoard_h

#include <string>
#include <ctime>
#include <queue>
using namespace std;

struct record{
	char playerName[70];
	long int usedTime;
	bool operator < (const struct record &in) const{
		return usedTime > in.usedTime;
	}
};

class scoreBoard{
	public:
		void readRecord(char);
		void setWinnerMessage(int, long int);
		void showRecord(int, int, char =0);
	private:
		priority_queue<struct record> recordQueue;
};

#endif
