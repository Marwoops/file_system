#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "arbre.h"
#include "liste.h"
#include "instruction.h"

FILE *SORTIE_DEBUG;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		puts("Le programme attend exactement un fichier d'instruction en argument.");
		printf("(%d donné(s)).\n", argc);
		exit(1);
	}

	SORTIE_DEBUG = fopen("log", "w");

	if (SORTIE_DEBUG == NULL) {
		puts("Impossible d'écrire les log");
		exit(1);
	}

	fputs("ouverture du fichier d'instructions", SORTIE_DEBUG);
	FILE* fichier_instructions = fopen(argv[1], "r");

	if (fichier_instructions == NULL) {
		puts("Impossible de lire le fichier passé en argument.");
		exit(1);
	}

	fputs("création de l'arbre de fichiers", SORTIE_DEBUG);
	noeud* arbre = creer_arbre(SORTIE_DEBUG);

	size_t t = 1024;
	char* ligne = malloc(t*sizeof(char));
	instruction* instr = NULL;

	while ((getline(&ligne, &t, fichier_instructions)) != -1) {

		getline(&ligne, &t, fichier_instructions);
		generer_instruction(ligne);
		instr = generer_instruction(ligne);
		arbre = traiter_instruction(arbre, instr);
	}

	fclose(fichier_instructions);

	return EXIT_SUCCESS;
}
