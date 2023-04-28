#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

noeud* creer_arbre() {
	flog("initialisation de l'arbre");
	noeud* racine = malloc(sizeof(noeud));

	if (racine == NULL) exit_malloc();

	char n[100] = {'\0'};
	racine->est_dossier = true;
	racine->racine = racine;
	racine->fils=creer_liste();
	memcpy(racine->nom, n, sizeof(n));

	return racine;
}

noeud* creer_fichier(noeud* racine, char nom[100]) {
	flogf("création du fichier %s\n", nom);

	noeud* fichier = malloc(sizeof(noeud));

	if (fichier == NULL) exit_malloc();

	fichier->est_dossier = false;
	fichier->racine = racine;
	memcpy(fichier->nom, nom, sizeof(char)*100);

	return fichier;
}

noeud* creer_dossier(noeud* racine, char nom[100], liste_noeud* fils) {
	flogf("création du dossier %s\n", nom);

	noeud* dossier = malloc(sizeof(noeud));

	if (dossier == NULL) exit_malloc();

	dossier->est_dossier = true;
	dossier->racine = racine;
	dossier->fils = fils;
	memcpy(dossier->nom, nom, sizeof(char)*100);

	return dossier;
}
