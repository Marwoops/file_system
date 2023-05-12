#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "exit.h"
#include "debug.h"

void exit_malloc() {
	puts("échec de malloc: impossible d'allouer de la mémoire");
	fermer_sortie_debug();
	exit(MALLOC);
}

void exit_nombre_d_argument(char *cmd, int attendus, int actuels) {
  if(strcmp(cmd,"cd")==0){
		printf("\"%s\" attend au plus 1 arguments. %d donnés\n", cmd, actuels);
  }
  else {
	printf("\"%s\" attend %d arguments. %d donnés\n", cmd, attendus, actuels);
  }
  fermer_sortie_debug();
  exit(NB_ARGUMENT);
}

void exit_argument_null(char *nom){
	puts("Aucun fichier ou dossier de ce type : ");
	printf("\"%s\"\n",nom);
	fermer_sortie_debug();
	exit(ARGUMENT_INEXISTANT);
}

void exit_fichier_existant(char *nom){
	printf ("Impossile de creer le dossier/fichier \"%s\": Le fichier existe déjà", nom);
	fermer_sortie_debug();
	exit(ARGUMENT__DEJA_EXISTANT);
}

void exit_nom_invalide(char *nom) {
	puts("nom invalide: un nom de fichier / dossier doit faire moins de 100 caractères alphanumériques");
	printf("nom donné: %s\n", nom);
	fermer_sortie_debug();
	exit(NOM_INVALIDE);
}

void exit_commande_invalide(char *nom) {
	puts("commande invalide : ");
	printf("%s",nom);
	fermer_sortie_debug();
	exit(COMMANDE_INVALIDE);
}

void exit_pas_un_dossier(char *nom){
	printf("%s n'est pas un dossier", nom);
	fermer_sortie_debug();
	exit(PAS_UN_DOSSIER);
}

void exit_suppression_impossible(char* src, char* dst){
	puts("Impossible de supprimer un dossier parent.");
	printf("%s est un parent de %s\n",dst,src);
	fermer_sortie_debug();
	exit(SUPPRESSION_IMPOSSIBLE);
}

void exit_copie_impossible(char * src, char*dst){
	puts("Impossible de copier un dossier parent dans un de ses dossier fils ou l'élément de copier est déja dans le dossier ciblé");
	printf("%s est un parent de %s\n",dst,src);
	fermer_sortie_debug();
	exit(COPIE_IMPOSSIBLE);
}

void exit_deplacement_impossible(char * src, char*dst){
	puts("Impossible de déplcer un dossier parent dans un de ses dossier fils ou l'élément de déplacer est déja dans le dossier ciblé.");
	printf("%s est un parent de %s\n",dst,src);
	fermer_sortie_debug();
	exit(DEPLACEMENT_IMPOSSIBLE);
}

void exit_trop_d_arguments(char * cmd){
	printf("La commande %s a trop d'argument.", cmd);
	fermer_sortie_debug();
	exit(NB_ARGUMENT);
}
