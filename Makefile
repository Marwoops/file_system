CC=gcc
CFLAGS=-Wall
DEPS=lib/arbre.h lib/liste.h lib/instruction.h
TEST=main
EXEC=treedir

all : build run clean

build : ${TEST} ${EXEC}

run :
	./${TEST}

clean :
	rm -rf $(EXEC) *.o main treedir log

%.o: lib/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

main : main.o arbre.o liste.o instruction.o
	$(CC) $(CFLAGS) -o $@ $^

treedir : treedir.o arbre.o liste.o instruction.o
	$(CC) $(CFLAGS) -o $@ $^
