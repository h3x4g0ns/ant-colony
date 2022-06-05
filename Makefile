.PHONY: install test  

install-mac:
	brew install gsl

test-mac:
	clang++ -Wall -I/usr/local/Cellar/gsl/2.7.1/include -fexceptions -o test.out test.cpp
	./test.out

test:
	clang++ -Wall -I/usr/include -fexceptions -o test.out test.cpp
	./test.out
