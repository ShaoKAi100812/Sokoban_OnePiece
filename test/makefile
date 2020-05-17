main: main.o Sokoban.o
	g++ -o main main.o Sokoban.o

main.o: main.cpp Sokoban.h
	g++ -c main.cpp

Sokoban.o: Sokoban.cpp Sokoban.h
	g++ -c Sokoban.cpp

clean:
	rm main *.o
