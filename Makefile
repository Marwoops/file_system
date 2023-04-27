CC=gcc
CFLAGS=-Wall
DEPS=lib/arbre.h lib/liste.h lib/instruction.h lib/debug.h
EXEC=treedir

all : build
	./$(EXEC) tests/base.txt --debug

build : ${EXEC}

clean :
	rm -rf $(EXEC) *.o main treedir log

%.o: lib/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

main : main.o arbre.o liste.o instruction.o debug.o
	$(CC) $(CFLAGS) -o $@ $^

treedir : treedir.o arbre.o liste.o instruction.o debug.o
	$(CC) $(CFLAGS) -o $@ $^
