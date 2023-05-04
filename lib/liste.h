#ifndef LISTE_H
#define LISTE_H

#include "arbre.h"

struct liste_noeud;

struct liste_noeud {
	struct noeud *no;
	struct liste_noeud *succ;
};

typedef struct liste_noeud liste_noeud;
typedef struct noeud noeud;

extern liste_noeud *creer_liste();
extern liste_noeud *creer_liste_avec_noeud(noeud*);
extern noeud *get_elt(liste_noeud*, char*);
extern liste_noeud *creer_liste_bis(liste_noeud*, noeud*);
extern noeud *ajouter_elt (liste_noeud*, noeud*);
extern noeud *supprimer_elt(liste_noeud*, noeud*);
extern void affiche_liste(liste_noeud*);
#endif
