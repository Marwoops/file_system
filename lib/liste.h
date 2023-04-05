#ifndef LISTE_H
#define LISTE_H

#include "arbre.h"

struct liste_noeud;

struct liste_noeud {
	struct noeud* no;
	struct liste_noeud* succ;
};

typedef struct liste_noeud liste_noeud;

#endif
