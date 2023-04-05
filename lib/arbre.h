#ifndef ARBRE_H
#define ARBRE_H

#include <stdbool.h>

struct noeud {
	bool est_dossier;
	char nom[100];
	struct noeud* pere;
	struct noeud* racine;
	struct liste_noeud *fils;
};

typedef struct noeud noeud;

extern noeud* creer_arbre();
extern noeud* creer_fichier(noeud* , char [100]);
extern noeud* creer_dossier(noeud* , char [100]);
extern bool est_nom_valide(char [100]);
#endif
