#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "arbre.h"
#include "instruction.h"
#include "liste.h"
#include "exit.h"

void afficher_prompt(noeud *n) {
	printf("melyo@");
	afficher_chemin(n);
	printf(" > ");
}

instruction *generer_instruction(char *_input) {
	flog("génération de l'instruction");
	char *input = strtok(_input, "\n");

	instruction *instr = malloc(sizeof(instruction));
	if (instr == NULL) exit_malloc();

	char* nom_cmd=strtok(input, " ");
	instr->cmd = get_commande(nom_cmd);

	if (instr->cmd == INVALIDE) exit_commande_invalide(nom_cmd);

	instr->arg1 = strtok(NULL, " ");
	instr->arg2 = strtok(NULL, " ");
	instr->nombre_arguments = (instr->arg1 != NULL) + (instr->arg2 != NULL);

	if (strtok(NULL, " ") != NULL) exit_trop_d_arguments(nom_cmd);

	return instr;
}

noeud *traiter_instruction(noeud *n, instruction *instr) {
	flog("traitement de l'instruction");
	assert(instr != NULL);
	flogf("CMD : %d, ARGC : %d\n", instr->cmd, instr->nombre_arguments);

	switch (instr->cmd) {
		case LS: return ls(n, instr);
		case CD: return cd(n, instr);
		case PWD: return pwd(n, instr);
		case MKDIR: return mkdir(n, instr);
		case TOUCH: return touch(n, instr);
		case RM: return rm(n, instr);
		case CP: return cp(n, instr);
		case MV: return mv(n, instr);
		case PRINT: return print(n, instr);
		default: return n;
	}
}

commande get_commande(char *input) {
	if (strcmp(input, "ls") == 0) return LS;
	if (strcmp(input, "cd") == 0) return CD;
	if (strcmp(input, "pwd") == 0) return PWD;
	if (strcmp(input, "mkdir") == 0) return MKDIR;
	if (strcmp(input, "touch") == 0) return TOUCH;
	if (strcmp(input, "rm") == 0) return RM;
	if (strcmp(input, "cp") == 0) return CP;
	if (strcmp(input, "mv") == 0) return MV;
	if (strcmp(input, "print") == 0) return PRINT;
	return INVALIDE;
}

void afficher_instruction(instruction *instr) {
	puts("instruction :");
	printf("cmd: %d\n", instr->cmd);
	printf("nombre_arguments: %u\n", instr->nombre_arguments);
	if (instr->arg1 != NULL) printf("arg1 : %s\n", instr->arg1);
	if (instr->arg2 != NULL) printf("arg2 : %s\n", instr->arg2);
	/*switch(instr->cmd) {
		case LS: puts("ls"); break;
		case CD: puts("cd"); break;
		case PWD: puts("pwd"); break;
		case MKDIR: puts("mkdir"); break;
		case TOUCH: puts("touch"); break;
		case RM: puts("rm"); break;
		case CP: puts("cp"); break;
		case MV: puts("mv"); break;
		case PRINT: puts("print"); break;
		default: puts("INVALIDE");
	} */
}


noeud *ls(noeud *n, instruction *instr) {
	if(instr->nombre_arguments>0) {
		exit_nombre_d_argument("ls", 0, instr->nombre_arguments);
	}
	flog("exécution de ls");
	affiche_liste(n->fils);
	return n;
}

noeud *cd(noeud *n, instruction *instr) {
	if (instr->nombre_arguments>1) {
		exit_nombre_d_argument("cd", 0, instr->nombre_arguments);
	}

	flog("exécution de cd");
	if(instr->nombre_arguments==0){
		return n->racine;
	}

	chemin *chem = generer_chemin(instr->arg1);
	noeud *dst = aller_a(n, chem);
	if (!dst->est_dossier) exit_pas_un_dossier(dst->nom);

	liberer_chemin(chem);
	return dst;
}

noeud *pwd (noeud *n, instruction *instr) {
	if (instr->nombre_arguments > 0) {
		exit_nombre_d_argument("pwd", 0, instr->nombre_arguments);
	}
	flog("exécution de pwd");
	afficher_chemin(n);
	puts("");
	return n;
}

noeud *mkdir(noeud *n, instruction *instr) {
	if (instr->nombre_arguments!=1) {
		exit_nombre_d_argument("mkdir", 1, instr->nombre_arguments);
	}

	flogf("exécution de mkdir %s\n", instr->arg1);
	liste_noeud *l = creer_liste();
	creer_dossier(n, instr->arg1, l);

	return n;
}

noeud *touch(noeud *n, instruction *instr) {
	if (instr->nombre_arguments!=1) {
		exit_nombre_d_argument("touch", 1, instr->nombre_arguments);
	}

	flogf("exécution de touch %s\n", instr->arg1);
	creer_fichier(n, instr->arg1);

	return n;
}

noeud *rm(noeud *n, instruction *instr) {
	if (instr->nombre_arguments != 1) {
		exit_nombre_d_argument("rm", 1, instr->nombre_arguments);
	}

	flogf("exécution de rm %s %s\n", instr->arg1);

	chemin *chem = generer_chemin(instr->arg1);
	noeud *a_suppr = aller_a(n, chem);

	if (a_suppr->est_dossier && est_parent(a_suppr, n)) {
		exit_suppression_impossible(n->nom, a_suppr->nom);
	}

	supprimer_elt(a_suppr->pere->fils, a_suppr);
	liberer_noeud(a_suppr);
	liberer_chemin(chem);

	return n;
}

noeud *cp(noeud *n, instruction *instr) {
	if (instr->nombre_arguments != 2) {
		exit_nombre_d_argument("cp", 2, instr->nombre_arguments);
	}

	flogf("exécution de cp %s %s\n", instr->arg1, instr->arg2);

	chemin *chem_src = generer_chemin(instr->arg1);
	chemin *chem_dst = generer_chemin(instr->arg2);
	char *nom_dst = sans_dernier_noeud(chem_dst);

	noeud *src = aller_a(n, chem_src);
	noeud *dst = aller_a(n, chem_dst);

	// Message d'erreur à fix
	if (src->est_dossier && est_parent(src, dst))
		exit_copie_impossible(src->nom, dst->nom);

	copier_noeud(dst, src, nom_dst);
	liberer_chemin(chem_src);
	liberer_chemin(chem_dst);
	free(nom_dst);

	return n;
}

noeud *mv(noeud *n, instruction *instr) {
	if (instr->nombre_arguments != 2) {
		exit_nombre_d_argument("mv", 2, instr->nombre_arguments);
	}

	flogf("exécution de mv %s %s\n", instr->arg1, instr->arg2);

	chemin *chem_src = generer_chemin(instr->arg1);
	chemin *chem_dst = generer_chemin(instr->arg2);
	char *nom_dst = sans_dernier_noeud(chem_dst);
	if(est_nom_valide(nom_dst))exit_nom_invalide(nom_dst);

	noeud *src = aller_a(n, chem_src);
	noeud *dst = aller_a(n, chem_dst);
	// Message d'erreur à fix
	if (src->est_dossier && est_parent(src, dst)) {
		exit_deplacement_impossible(src->nom, dst->nom);
	}
	supprimer_elt(src->pere->fils, src);
	src->pere = dst;
	strcpy(src->nom, nom_dst);
	ajouter_elt(dst->fils, src);

	liberer_chemin(chem_src);
	liberer_chemin(chem_dst);
	//free(nom_dst);

	return n;
}

noeud *print(noeud *n, instruction *instr) {
	if (instr->nombre_arguments > 0) {
		// Message d'erreur à fix
		printf("print n'attend aucun argument.");
		exit(1);
	}
	print_noeud(n->racine);
	return n;
}
