#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "liste.h"
#include "exit.h"
#include "debug.h"

chemin *generer_chemin(char* noeuds) {
    chemin *chem = malloc(sizeof(chemin));
    if (chem == NULL) exit_malloc();
    chem->noeuds = decoupe_chemin(noeuds, &chem->est_absolu, &chem->profondeur);
    return chem;
}

noeud* creer_arbre() {
	flog("initialisation de l'arbre");
	noeud* racine = malloc(sizeof(noeud));

	if (racine == NULL) exit_malloc();

	char n[100] = {'\0'};
	racine->est_dossier = true;
	racine->racine = racine;
	racine->fils=creer_liste();
	memcpy(racine->nom, n, sizeof(n));

	return racine;
}

noeud* creer_fichier(noeud* racine, char nom[100]) {
	flogf("création du fichier %s\n", nom);

	noeud* fichier = malloc(sizeof(noeud));

	if (fichier == NULL) exit_malloc();

	fichier->est_dossier = false;
	fichier->racine = racine;
	memcpy(fichier->nom, nom, sizeof(char)*100);

	return fichier;
}

noeud* creer_dossier(noeud* racine, char nom[100], liste_noeud* fils) {
	flogf("création du dossier %s\n", nom);

	noeud* dossier = malloc(sizeof(noeud));

	if (dossier == NULL) exit_malloc();

	dossier->est_dossier = true;
	dossier->racine = racine;
	dossier->fils = fils;
	memcpy(dossier->nom, nom, sizeof(char)*100);

	return dossier;
}

noeud *ajouter_noeud(noeud *racine, chemin* chem, noeud *noeud) {
	return racine;
}

char** decoupe_chemin(char *chemin, bool *est_absolu, size_t *taille) {
	assert(chemin != NULL);
	assert(*chemin != '\0');

	if (*chemin == '/') {
		*est_absolu = true;
		*chemin = *(chemin + 1);
	} else {
		*est_absolu = false;
	}

	size_t nb_noeuds = 1;
	size_t plus_long_noeud = 0;
	size_t longueur_actuelle = 0;
	size_t len = strlen(chemin);

	for (size_t i = 0; i < len; ++i) {
		if (*(chemin + i) == '/') {
			plus_long_noeud = (longueur_actuelle > plus_long_noeud) ?
				longueur_actuelle : plus_long_noeud;
			++nb_noeuds;
			longueur_actuelle = 0;
		} else {
			++longueur_actuelle;
		}
	}

	*taille = nb_noeuds;

	plus_long_noeud = (longueur_actuelle > plus_long_noeud) ?
		longueur_actuelle : plus_long_noeud;

	char **chemin_decoupe = malloc(nb_noeuds * sizeof(char*));
	*chemin_decoupe = malloc(plus_long_noeud * sizeof(char)+1);
	strcpy(*chemin_decoupe, strtok(chemin, "/"));

	for (size_t i = 1; i < nb_noeuds; ++i) {
		*(chemin_decoupe+i) = malloc(plus_long_noeud * sizeof(char));
		strcpy(*(chemin_decoupe+i), strtok(NULL, "/"));
	}

	return chemin_decoupe;
}

noeud *aller_a(noeud *n, chemin *chem) {
    assert(chem != NULL);
    assert(n != NULL);
	char q[3] = {'.', '.', '\0'};
    if (chem->est_absolu) {
        chem->est_absolu = false;
        flog("déplacement à la racine");
        return aller_a(n->racine, chem);
    }

    if (chem->profondeur == 0) {
        return n;
    }

    char *nom = *(chem->noeuds);
    chem->profondeur -= 1;
    chem->noeuds = chem->noeuds + 1;
	printf("%s\n",nom);
	printf("%d\n",strcmp(nom, ".."));
    if ((strcmp(nom, "..")==0) && n->pere != NULL) {
	   flogf("déplacement vers le pere de %s\n", nom);
	   printf("mega prooooooooooooouuuuuuuuuuuuuuut");
       return aller_a(n->pere, chem);
	}

	if (strcmp(nom, ".")==0) {
       return aller_a(n,chem);
	}
    noeud *suivant = get_elt(n->fils, nom);

    // creer une erreur plus précise
    if (suivant == NULL) exit_argument_null(suivant->nom);
    if (!suivant->est_dossier) exit_argument_invalide(suivant->nom);
    flogf("déplacement vers %s\n", nom);
    return aller_a(suivant, chem);
}
