
main: adaline.o shapes.o deck.o
	g++ main.cpp adaline.o shapes.o deck.o

adaline.o:
	g++ -c -o $@ adaline.cpp

shapes.o:
	g++ -c -o $@ shapes.cpp

deck.o:
	g++ -c -o $@ carddeck/deck.cpp

all: main

rebuild: clean main

clean:
	rm -f *.o *.out
