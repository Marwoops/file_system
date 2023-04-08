#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "arbre.h"

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
extern commande get_commande(char *);
extern void afficher_instruction();
extern char** get_chemin(char*);

extern void ls(noeud*, instruction*);
extern noeud* cd(noeud*, instruction*);
extern void pwd(noeud*, instruction*);
extern void mkdir(noeud*, instruction*);
extern void touch(noeud*, instruction*);
extern void rm(noeud*, instruction*);
extern void cp(noeud*, instruction*);
extern void mv(noeud*, instruction*);
extern void print(noeud*, instruction*);

#endif
