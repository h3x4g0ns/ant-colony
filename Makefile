.PHONY: test clean 

clean:
	rm -rf *.o

test:
	clean
	gcc -03 -fexceptions -o test test.c
	./test

