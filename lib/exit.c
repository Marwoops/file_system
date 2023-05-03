#include <stdio.h>
#include <stdlib.h>

#include "exit.h"

void exit_malloc() {
	puts("échec de malloc: impossible d'allouer de la mémoire");
	exit(EXIT_MALLOC);
}

void exit_nom_invalide(char *nom) {
	puts("nom invalide: un nom de fichier / dossier doit faire moins de 100 caractères alphanumériques");
	printf("nom donné: %s\n", nom);
	exit(EXIT_NOM_INVALIDE);
}

void exit_commande_invalide() {
	puts("commande invalide");
	exit(EXIT_COMMANDE_INVALIDE);
}

void exit_trop_d_arguments() {
	puts("trop d'arguments");
	exit(EXIT_TROP_D_ARGUMENTS);
}

void exit_argument_invalide(char *nom) {
	puts("argument invalide, un dossier est attendu a la place d'un fichier ou l'inverse :");
	printf("%s\n",nom);
	exit(EXIT_ARGUMENT_INVALIDE);
}

void exit_argument_null(char *nom){
	puts("arguments inexistants dans  l'arborescence :");
	printf("%s\n",nom);
	exit(EXIT_ARGUMENT_NULL);
}
