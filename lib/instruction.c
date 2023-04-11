#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

instruction* generer_instruction(char* input) {
	instruction* instr = malloc(sizeof(instruction));
	if (instr == NULL) {
		puts("probleme malloc lors de la génération d'une instruction");
		exit(1);
	}

	instr->cmd = get_commande(strtok(input, " "));

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

commande get_commande(char* input) {
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

void afficher_instruction(instruction* instr) {
	puts("instruction :");
	printf("cmd: %d\n", instr->cmd);
	printf("nombre_arguments: %u\n", instr->nombre_arguments);
	if (instr->arg1 != NULL) printf("arg1 : %s\n", instr->arg1);
	if (instr->arg2 != NULL) printf("arg2 : %s\n", instr->arg2);
	puts("");
	/* switch(instr->cmd) { */
	/* 	case LS: puts("ls"); break; */
	/* 	case CD: puts("cd"); break; */
	/* 	case PWD: puts("pwd"); break; */
	/* 	case MKDIR: puts("mkdir"); break; */
	/* 	case TOUCH: puts("touch"); break; */
	/* 	case RM: puts("rm"); break; */
	/* 	case CP: puts("cp"); break; */
	/* 	case MV: puts("mv"); break; */
	/* 	case PRINT: puts("print"); break; */
	/* 	default: puts("INVALIDE"); */
	/* } */
}

void ls (noeud *n, instruction *i)
{
	if(i->nombre_arguments>0)
	{
		exit(1);
	}
	affiche_liste(n->fils);
}