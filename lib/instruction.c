#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instruction.h"

instruction* generer_instruction(char* input) {
	char* input_copy = NULL;
	strcpy(input_copy, input);

	instruction* instr = malloc(sizeof(instruction));
	if (instr == NULL) {
		exit(1);
	}

	instr->cmd = get_commande(strtok(input_copy, " "));

	if (instr->cmd == INVALIDE) {
		puts("Commande non-reconnue");
		exit(1);
	}

	instr->arg1 = strtok(input_copy, " ");
	instr->arg2 = strtok(input_copy, " ");

	instr->nombre_arguments = (instr->arg1 != NULL) + (instr->arg2 != NULL);

	if (input_copy != NULL) {
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

