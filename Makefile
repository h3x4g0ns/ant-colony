.PHONY: clean build test debug

clean:
	rm -f *.o
	rm -f *.run

build: clean
	g++ -Wall -I/home/hexagon/gsl/include -c -fexceptions -g test.cpp
	g++ -L/home/hexagon/gsl/lib test.o -o test.run -lgsl -lgslcblas -lm

test: clean build
	./test.run

debug: clean build
	cgdb test.run
