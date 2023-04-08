#include <stdlib.h>
#include <stdio.h>

#include "arbre.h"
#include "liste.h"
#include "instruction.h"

int main(void) {
	printf("%d\n", get_commande("ls"));
	printf("%d\n", get_commande("cd"));
	printf("%d\n", get_commande("ls aerigjjer"));
	return EXIT_SUCCESS;
}
