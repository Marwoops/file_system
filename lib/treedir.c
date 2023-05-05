#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "debug.h"
#include "arbre.h"
#include "liste.h"
#include "instruction.h"


int main(int argc, char* argv[]) {
	if (argc == 3 && strcmp("--debug", argv[2]) == 0) {
		FILE *sortie = fopen("log", "w");
		set_sortie_debug(sortie);
	} else if (argc != 2) {
		puts("Le programme attend exactement un fichier d'instruction en argument.");
		printf("(%d donné(s)).\n", argc);
		exit(1);
	}

	flog("ouverture du fichier instruction");
	FILE* fichier_instructions = fopen(argv[1], "r");

	if (fichier_instructions == NULL) {
		puts("Impossible de lire le fichier passé en argument.");
		exit(1);
	}

	noeud* arbre = creer_arbre();

	size_t t = 1024;
	char* ligne = malloc(t*sizeof(char));
	instruction* instr = NULL;
	int numero_ligne = 0;

	while ((getline(&ligne, &t, fichier_instructions)) != -1) {
		flogf("lecture de l'instruction ligne %d\n", numero_ligne);
		afficher_prompt(arbre);
		printf("%s", ligne);
		instr = generer_instruction(ligne);
		arbre = traiter_instruction(arbre, instr);
		numero_ligne++;
	}

	fermer_sortie_debug();
	fclose(fichier_instructions);

	return EXIT_SUCCESS;
}
