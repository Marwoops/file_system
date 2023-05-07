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

void liberer_liste(liste_noeud *l) {
	if (l == NULL) return;

	liberer_noeud(l->no);
	liberer_liste(l->succ);
	free(l->succ);
	free(l);
}

noeud *get_elt(liste_noeud* l, char *nom) {
	assert(l != NULL);
	if (l->no == NULL) return NULL;
    if(strcmp(nom,l->no->nom) == 0) return l->no;
    if(l->succ == NULL) return NULL;
    return get_elt(l->succ, nom);
}

void ajouter_elt(liste_noeud *l, noeud *n) {
	assert(l != NULL);
	assert(n != NULL);

	flogf("ajout de %s élément à la liste\n", n->nom);

	if (l->no == NULL) {
		l->no = n;
		return;
	}

	while(l->succ != NULL) l = l->succ;
	l->succ = creer_liste_avec_noeud(n);
}

void affiche_liste(liste_noeud *l) {
    if(l == NULL || l->no == NULL){
		puts("");
		return;
	}
	if(l->no->est_dossier)printf("%s (D), ", l->no->nom);
	else printf("%s (F), ", l->no->nom);
    return affiche_liste(l->succ);
}

int taille_liste(liste_noeud *l){
	if(l==NULL)return 0;
	if(l->succ==NULL)return 1;
	return 1+taille_liste(l->succ);
}

void supprimer_elt(liste_noeud* l, noeud* n) {
	assert(l != NULL);
	assert(n != NULL);


	if (l->no == NULL) return;

    if  (n == l->no) {
		if (l->succ == NULL) {
			l->no = NULL;
		} else {
			l->no = l->succ->no;
			l->succ = l->succ->succ;
		}
    }

	while(l->succ != NULL) {
		if (l->succ->no == n) {
			l->succ = l->succ->succ;
			return;
		}
		l = l->succ;
	}
}
