.PHONY: clean install-mac test-mac debug-mac

install-mac:
	brew install gsl

clean:
	rm -f *.o
	rm -f *.run

test-mac: clean
	clang++ -Wall -I/usr/local/Cellar/gsl/2.7.1/include -fexceptions -c -g test.cpp
	clang++ -L/usr/local/Cellar/gsl/2.7.1/lib test.o -o test.run -lgsl -lgslcblas -lm
	./test.run

debug-mac: clean
	clang++ -Wall -I/usr/local/Cellar/gsl/2.7.1/include -fexceptions -c -g test.cpp
	clang++ -L/usr/local/Cellar/gsl/2.7.1/lib test.o -o test.run -lgsl -lgslcblas -lm
	lldb ./test.run
