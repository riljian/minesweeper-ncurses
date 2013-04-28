project1: main.o cursesFunc.o minesweeper.o processInput.o scoreBoard.o
	g++ main.o cursesFunc.o processInput.o minesweeper.o scoreBoard.o -o minesweeper -lncurses
	rm main.o cursesFunc.o processInput.o minesweeper.o scoreBoard.o
main.o: main.cpp minesweeper.h cursesFunc.h processInput.h scoreBoard.h
	g++ -c main.cpp
cursesFunc.o: cursesFunc.cpp cursesFunc.h
	g++ -c cursesFunc.cpp
minesweeper.o: minesweeper.cpp minesweeper.h cursesFunc.h
	g++ -c minesweeper.cpp
processInput.o: processInput.cpp processInput.h cursesFunc.h minesweeper.h
	g++ -c processInput.cpp
scoreBoard.o: scoreBoard.cpp scoreBoard.h
	g++ -c scoreBoard.cpp
