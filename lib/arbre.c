#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

struct chemin {
	bool est_absolu;
	size_t profondeur;
	char** noeuds;
};

chemin *generer_chemin(char *noeuds) {
    chemin *chem = malloc(sizeof(chemin));
    if (chem == NULL) exit_malloc();
    chem->noeuds = decoupe_chemin(noeuds, &chem->est_absolu, &chem->profondeur);
    return chem;
}

noeud  *creer_arbre() {
	flog("initialisation de l'arbre");
	noeud* racine = malloc(sizeof(noeud));

	if (racine == NULL) exit_malloc();

	racine->est_dossier = true;
	racine->racine = racine;
	racine->fils = creer_liste();
	racine->pere = racine;
	racine->nom = strdup("");

	return racine;
}

noeud *creer_fichier(noeud *pere, char *nom) {
	assert(pere != NULL);

	flogf("création du fichier %s dans %s\n", nom, pere->nom);

	noeud *fichier = malloc(sizeof(noeud));

	if (fichier == NULL) exit_malloc();

	fichier->est_dossier = false;
	fichier->racine = pere->racine;
	fichier->pere = pere;
	fichier->nom = strdup(nom);
	ajouter_elt(pere->fils, fichier);

	return fichier;
}

noeud *creer_dossier(noeud *pere, char *nom, liste_noeud *fils) {
	assert(pere  != NULL);

	flogf("création du dossier %s dans %s\n", nom, pere->nom);

	noeud *dossier = malloc(sizeof(noeud));

	if (dossier == NULL) exit_malloc();

	dossier->est_dossier = true;
	dossier->racine = pere->racine;
	dossier->fils = fils;
	dossier->pere = pere;
	dossier->nom = strdup(nom);
	ajouter_elt(pere->fils, dossier);

	return dossier;
}

noeud *copier_noeud(noeud* pere, noeud *n) {
	assert(pere != NULL);
	if (n == NULL) return NULL;

	if(n->est_dossier) {
		noeud *copie = creer_dossier(pere, n->nom, creer_liste());
		copier_liste(copie, n->fils);
		return copie;
	}

	return creer_fichier(pere, n->nom);
}

void afficher_chemin(noeud *n) {
	assert(n != NULL);

	if (n->pere != n->racine) afficher_chemin(n->pere);
	printf("/%s", n->nom);
}

void liberer_noeud(noeud *n) {
	if (n == NULL) return;

	flogf("libération de %s\n", n->nom);

	if (n->est_dossier) {
		liberer_liste(n->fils);
	}

	free(n->nom);
	free(n);
}

void ajouter_noeud(noeud *racine, noeud *n) {
	assert(racine != NULL);

	ajouter_elt(racine->fils, n);
}

char **decoupe_chemin(char *chemin, bool *est_absolu, size_t *taille) {
    assert(chemin != NULL);
    assert(*chemin != '\0');

    if (*chemin == '/') {
        *est_absolu = true;
        chemin = (chemin+1);
    } else {
        *est_absolu = false;
    }

    size_t nb_noeuds = 1;
    size_t len = strlen(chemin);
    for (size_t i = 0; i < len; ++i) {
        if (*(chemin + i) == '/') ++nb_noeuds;
    }

    *taille = nb_noeuds;

    char **chemin_decoupe = malloc((nb_noeuds+1) * sizeof(char*));
    *chemin_decoupe = strdup(strtok(chemin, "/"));
    for (size_t i = 1; i < nb_noeuds; ++i)
        *(chemin_decoupe + i) = strdup(strtok(NULL, "/"));

    return chemin_decoupe;
}

char *sans_dernier_noeud(chemin *chem) {
	assert(chem != NULL && chem->profondeur > 0);

	return chem->noeuds[--chem->profondeur];
}

noeud *aller_a(noeud *n, chemin *chem) {
	assert(chem != NULL);
    assert(n != NULL);
    if (chem->est_absolu) {
        chem->est_absolu = false;
        flog("déplacement à la racine");
        return aller_a(n->racine, chem);
    }
	//printf("%d\n", chem->profondeur);
    if (chem->profondeur == 0) return n;
    char *nom = *(chem->noeuds);
    chem->profondeur -= 1;
	chem->noeuds = chem->noeuds + 1;

    if ((strcmp(nom, "..") == 0) && n->pere != NULL) {
	   flogf("déplacement vers le pere de %s\n", nom);
       return aller_a(n->pere, chem);
	}

	if (strcmp(nom, ".") == 0) return aller_a(n,chem);
    noeud *suivant = get_elt(n->fils, nom);
    // creer une erreur plus précise
    if (suivant == NULL){exit_argument_invalide(nom);}
    if (!suivant->est_dossier) {
		if (chem->profondeur == 0) return suivant;
		else exit_argument_invalide(suivant->nom);
	}

    flogf("déplacement vers %s\n", nom);
    return aller_a(suivant, chem);
}

bool est_parent(noeud *src, noeud *dst) {
   if (dst == src) return true;
   if (dst == dst->racine) return false;
   return est_parent(src, dst->pere);
}

void print_noeud(noeud *n) {
	assert(n != NULL);

	if (!n->est_dossier) {
		printf("Noeud %s (F), pere : %s, 0 fils\n", n->nom, n->pere->nom);
		return;
	}

	size_t taille = taille_liste(n->fils);
	if (n == n->racine) printf("Noeud / (D)");
	else printf("Noeud %s (D), pere : %s", n->nom, n->pere->nom);

	printf(", %lu fils : ", taille);
	affiche_liste(n->fils);

	if (taille > 0) print_liste(n->fils);
}
