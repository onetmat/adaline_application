
main: adaline.o
	g++ main.cpp adaline.o

adaline.o:
	g++ -c -o $@ adaline.cpp

all: main

clean:
	rm -f *.o *.out
