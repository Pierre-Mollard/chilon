TARGET=run

run:testlib.o libchilon.a
	gcc testlib.o -o run -L . libchilon.a

testlib.o:testlib.c
	gcc -c testlib.c -o testlib.o

libchilon.a:chilon.o chiloniter.o chiloncursor.o
	ar rs libchilon.a chilon.o chiloniter.o chiloncursor.o

chiloncursor.o:src/chiloncursor.c
	gcc -c src/chiloncursor.c -o chiloncursor.o

chiloniter.o:src/chiloniter.c
	gcc -c src/chiloniter.c -o chiloniter.o

chilon.o:src/chilon.c
	gcc -c src/chilon.c -o chilon.o

clean:
	rm *.o
	rm run

clean-lib:
	rm libchilon.a