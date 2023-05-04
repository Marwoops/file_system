#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

liste_noeud *creer_liste() {
	flog("création d'une liste");
    liste_noeud *l=malloc(sizeof(liste_noeud));

    if (l == NULL) exit_malloc();

    return l;
}

liste_noeud *creer_liste_avec_noeud(noeud* n) {
	flog("création d'une liste avec un noeud");
    if (n == NULL) return creer_liste ();

    liste_noeud *l = malloc(sizeof(liste_noeud));

	if (l == NULL) exit_malloc();

    l->no = n;
    l->succ = NULL;

    return l;
}

liste_noeud *copier_liste(noeud *pere, liste_noeud *l) {
	if (l == NULL) return NULL;

	liste_noeud *copie = creer_liste();
	//printf("sous noeud : %s\n", l->no->nom);
	copie->no = copier_noeud(pere, l->no);
	copie->succ = copier_liste(pere, l->succ);

	return copie;
}

noeud *get_elt(liste_noeud* l, char *nom) {
	assert(l != NULL);
	if (l->no == NULL) return NULL;
    if(strcmp(nom,l->no->nom) == 0) return l->no;
    if(l->succ == NULL) return NULL;
    return get_elt(l->succ, nom);
}

void ajouter_elt (liste_noeud* l, noeud* n) {
	assert(l != NULL);
	assert(n != NULL);

	flogf("ajout de %s élément à la liste\n", n->nom);

	if (l->no == NULL) {
		l->no = n;
		return;
	}

    liste_noeud *l1 = l;

    while(l1->succ != NULL && l1 != NULL) {
        l1 = l1->succ;
    }
    l1->succ=creer_liste_avec_noeud(n);
}

void affiche_liste(liste_noeud *l) {
    if(l == NULL){
		puts("");
		return;
	}

    printf("%s ", l->no->nom);
    return affiche_liste(l->succ);
}


noeud *supprimer_elt(liste_noeud* l, noeud* n) {
    if  (n == l->no) {
        l->no = l->succ->no;
        l->succ = l->succ->succ;
        return n;
    }

    if(n == NULL || l->succ == NULL) {
        return NULL;
    }

    return supprimer_elt(l->succ, n);
}
