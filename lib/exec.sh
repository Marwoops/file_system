gcc -Wall -c arbre.c
gcc -Wall -c liste.c
gcc -Wall -c instruction.c
gcc -Wall -c main.c
gcc -Wall -o main arbre.o liste.o main.o instruction.o
./main

rm *.o
rm main
