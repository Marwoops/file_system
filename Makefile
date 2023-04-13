CC=gcc
CFLAGS=-Wall
DEPS=lib/arbre.h lib/liste.h lib/instruction.h
EXEC=main

all : build run clean

build : ${EXEC}

run :
	./${EXEC}

clean :
	rm -rf $(EXEC) *.o

%.o: lib/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

main : main.o arbre.o liste.o instruction.o
	$(CC) $(CFLAGS) -o $@ $^
