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

typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;
typedef struct chemin chemin;

extern chemin *generer_chemin(char*);
extern noeud *creer_arbre();
extern noeud *creer_fichier(noeud*, char*);
extern noeud *creer_dossier(noeud*, char*, liste_noeud*);
extern noeud *copier_noeud(noeud*, noeud*);
extern void afficher_chemin(noeud*);

extern void ajouter_noeud(noeud*, noeud*);
extern void supprimer_noeud(noeud*, chemin*, noeud*);
extern void supprimer_noeud_par_nom(noeud*, chemin*, char*);

extern bool est_dossier(noeud*);
extern char **decoupe_chemin(char *, bool *, size_t *);
extern char *sans_dernier_noeud(chemin*);
extern noeud *aller_a(noeud *, chemin*);
#endif
