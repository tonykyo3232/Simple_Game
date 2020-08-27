#reference: 
game: game.o player.o
	g++ game.o player.o -o game

game.o: game.cpp
	g++ -c game.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

clean:
	rm -rf *.o game 