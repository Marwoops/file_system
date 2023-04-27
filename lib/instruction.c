#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "instruction.h"
#include "liste.h"

instruction *generer_instruction(char *input) {
	flog("génération de l'instruction");

	instruction *instr = malloc(sizeof(instruction));
	if (instr == NULL) {
		puts("probleme malloc lors de la génération d'une instruction");
		exit(1);
	}

	instr->cmd = get_commande(strtok(input, " \n"));

	if (instr->cmd == INVALIDE) {
		puts("Commande non-reconnue");
		exit(1);
	}

	instr->arg1 = strtok(NULL, " ");
	instr->arg2 = strtok(NULL, " ");

	instr->nombre_arguments = (instr->arg1 != NULL) + (instr->arg2 != NULL);

	if (strtok(NULL, " ") != NULL) {
		printf("%s\n", input);
		puts("Trop d'arguments.");
		exit(1);
	}

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

noeud *ls (noeud *n, instruction *instr)
{
	if(instr->nombre_arguments>0)
	{
		printf("ls n'attend aucun argument.");
		exit(1);
	}
	flog("exécution de ls");
	affiche_liste(n->fils);
	return n;
}

noeud *cd (noeud *n, instruction *instr) {
	return n;
}

noeud *pwd (noeud *n, instruction *instr) {
	return n;
}

noeud *mkdir(noeud *n, instruction *instr)
{
	if (instr->nombre_arguments!=1)
	{
		printf("mkdir attend exactement un fichier en argument.");
		exit(1);
	}
	liste_noeud *l=creer_liste();
	noeud *dossier= creer_dossier(n->racine, instr->arg1, l);
	dossier->pere=n;	
	ajouter_elt(n->fils, dossier);
	return n;
}

noeud *touch(noeud *n, instruction *instr)
{
	if (instr->nombre_arguments!=1)
	{
		printf("touch attend exactement un fichier en argument.");
		exit(1);
	}
	noeud *fichier= creer_fichier(n->racine, instr->arg1);
	fichier->pere=n;
	ajouter_elt(n->fils, fichier);
	return n;
}

noeud *rm(noeud *n, instruction *instr) {
	return n;
}

noeud *cp(noeud *n, instruction *instr) {
	return n;
}

noeud *mv(noeud *n, instruction *instr) {
	return n;
}

noeud *print(noeud *n, instruction *instr) {
	return n;
}
