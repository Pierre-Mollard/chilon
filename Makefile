TARGET=run

run:testlib.o
	gcc testlib.o -o run

testlib.o:testlib.c
	gcc -c testlib.c -o testlib.o