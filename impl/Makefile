
main: adaline.o shapes.o
	g++ main.cpp adaline.o shapes.o

adaline.o:
	g++ -c -o $@ adaline.cpp

shapes.o:
	g++ -c -o $@ shapes.cpp

all: main

clean:
	rm -f *.o *.out
