#ifndef ARBRE_H
#define ARBRE_H

#include <stdbool.h>
#include "liste.h"

struct noeud;

struct noeud {
	bool est_dossier;
	char nom[100];
	struct noeud* pere;
	struct noeud* racine;
	struct liste_noeud *fils;
};

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;

extern noeud* creer_arbre();
extern noeud* creer_fichier(noeud* , char [100]);
extern noeud* creer_dossier(noeud* , char [100], liste_noeud*);

extern noeud* ajouter_noeud(noeud*, noeud*);
extern void supprimer_noeud(noeud*, noeud*);
extern void supprimer_noeud_par_nom(noeud*, char[100]);

extern bool est_dossier(noeud*);
extern bool est_nom_valide(char [100]);
#endif
