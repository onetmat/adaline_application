
main: adaline.o shapes.o deck.o tablestate.o game.o
	g++ main.cpp adaline.o shapes.o deck.o tablestate.o game.o

adaline.o:
	g++ -c -o $@ adaline.cpp

shapes.o:
	g++ -c -o $@ shapes.cpp

deck.o:
	g++ -c -o $@ carddeck/deck.cpp

tablestate.o:
	g++ -c -o $@ blackjack/tablestate.cpp

game.o:
	g++ -c -o $@ blackjack/game.cpp

all: main

rebuild: clean main

clean:
	rm -f *.o *.out
