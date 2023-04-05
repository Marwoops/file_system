gcc -Wall -c arbre.c
gcc -Wall -c liste.c
gcc -Wall -c main.c
gcc -Wall -o main arbre.o liste.o main.o
./main

rm *.o
rm main
