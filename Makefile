.PHONY: install-mac test-mac 

install-mac:
	brew install gsl

test-mac:
	clang++ -Wall -I/usr/local/Cellar/gsl/2.7.1/include -fexceptions -c -g test.cpp
	clang++ -L/usr/local/Cellar/gsl/2.7.1/lib test.o -o test -lgsl -lgslcblas -lm
	./test
