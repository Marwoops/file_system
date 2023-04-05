#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "liste.h"

noeud* creer_arbre() {
	noeud* racine = malloc(sizeof(noeud));

	if (racine == NULL) {
		return NULL;
	}

	char n[100] = {'\0'};
	racine->est_dossier = true;
	racine->racine = racine;
	memcpy(racine->nom, n, sizeof(n));

	return racine;
}

noeud* creer_fichier(noeud* racine, char nom[100]) {
	noeud* fichier = malloc(sizeof(noeud));

	if (fichier == NULL) {
		return NULL;
	}

	fichier->est_dossier = false;
	fichier->racine = racine;
	memcpy(fichier->nom, nom, sizeof(char)*100);

	return fichier;
}

noeud* creer_dossier(noeud* racine, char nom[100], liste_noeud* fils) {
	noeud* dossier = malloc(sizeof(noeud));

	if (dossier == NULL) {
		return NULL;
	}

	dossier->est_dossier = true;
	dossier->racine = racine;
	dossier->fils = fils;
	memcpy(dossier->nom, nom, sizeof(char)*100);

	return dossier;
}

bool est_nom_valide(char nom[100]) {
	for (size_t t = 0; t < 100; ++t) {
		if (!isalnum(nom[t])) {
			return false;
		}
	}
	return true;
}
