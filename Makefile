.PHONY: test clean 

clean:
	rm -rf *.o

test:
	clean
	gcc -03 -o test test.c
	./test

