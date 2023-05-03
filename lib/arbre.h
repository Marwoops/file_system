#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdbool.h>

struct noeud {
	bool est_dossier;
	char nom[100];
	struct noeud* pere;
	struct noeud* racine;
	struct liste_noeud *fils;
};

struct chemin {
	bool est_absolu;
	size_t profondeur;
	char** noeuds;
};

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;
typedef struct chemin chemin;

extern chemin *generer_chemin(char*);
extern noeud *creer_arbre();
extern noeud *creer_fichier(noeud* , char [100]);
extern noeud *creer_dossier(noeud* , char [100], liste_noeud*);

extern noeud *ajouter_noeud(noeud*, chemin*, noeud*);
extern void supprimer_noeud(noeud*, chemin*, noeud*);
extern void supprimer_noeud_par_nom(noeud*, chemin*, char[100]);

extern bool est_dossier(noeud*);
char** decoupe_chemin(char *, bool *, size_t *);
extern noeud *aller_a(noeud *, chemin*);
#endif
