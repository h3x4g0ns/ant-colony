.PHONY: clean test debug

clean:
	rm -f *.o
	rm -f *.run

test: clean
	g++ -Wall -I/home/hexagon/gsl/include -c -fexceptions -g test.cpp
	g++ -L/home/hexagon/gsl/lib test.o -o test.run -lgsl -lgslcblas -lm
	./test.run

debug: clean
	g++ -Wall -I/home/hexagon/gsl/include -c -fexceptions -g test.cpp
	g++ -L/home/hexagon/gsl/lib test.o -o test.run -lgsl -lgslcblas -lm
	cgdb test.run
