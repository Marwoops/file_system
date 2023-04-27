#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>

#include "arbre.h"
#include "debug.h"

struct instruction;

enum commande {LS, CD, PWD, MKDIR, TOUCH, RM, CP, MV, PRINT, INVALIDE};
typedef enum commande commande;

struct instruction {
	commande cmd;
	unsigned nombre_arguments;
	char* arg1;
	char* arg2;
};

typedef struct instruction instruction;

extern instruction* generer_instruction(char*);
extern noeud* traiter_instruction(noeud*, instruction*);
extern commande get_commande(char *);
extern void afficher_instruction(instruction*);
extern char** get_chemin(char*);

extern noeud* ls(noeud*, instruction*);
extern noeud* cd(noeud*, instruction*);
extern noeud* pwd(noeud*, instruction*);
extern noeud* mkdir(noeud*, instruction*);
extern noeud* touch(noeud*, instruction*);
extern noeud* rm(noeud*, instruction*);
extern noeud* cp(noeud*, instruction*);
extern noeud* mv(noeud*, instruction*);
extern noeud* print(noeud*, instruction*);

#endif
