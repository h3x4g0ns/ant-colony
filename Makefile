.PHONY: install test  

install:
	brew install gsl

test:
	gcc -Wall -I/usr/local/Cellar/gsl/2.7.1/include -fexceptions -o test.out -c test.cpp
	./test.out

