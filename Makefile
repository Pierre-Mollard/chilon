CC = gcc
CFLAGS = -g -Wall
LIB = -Iinclude -Lbin -lchilon
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TEST_SRC = test/testlib.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TARGET=run

all:run

run:$(TEST_OBJ) bin/libchilon.a
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $@ $(LIB)

bin/libchilon.a: $(OBJ)
	ar rs $@ $(OBJ)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB)

show_lib:libchilon.a
	ar -t libchilon.a

clean:
	rm $(OBJ) $(TEST_OBJ) run

clean-lib:clean
	rm bin/libchilon.a

mrproper:clean-lib