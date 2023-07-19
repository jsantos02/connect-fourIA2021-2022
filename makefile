
output: main.o board.o
	g++ main.o board.o -o game

main.o: main.cpp
	g++ -c main.cpp

board.o: board.cpp board.h
	g++ -c board.cpp

clean:
	rm *.o game