TARGET=run

run:testlib.o libchilon.a
	gcc testlib.o -o run -L . libchilon.a

testlib.o:testlib.c
	gcc -c testlib.c -o testlib.o

libchilon.a:chilon.o
	ar rs libchilon.a chilon.o

chilon.o:src/chilon.c
	gcc -c src/chilon.c -o chilon.o