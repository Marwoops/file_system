#include <stdlib.h>
#include <stdio.h>

#include "arbre.h"
#include "liste.h"
#include "instruction.h"

int main(void) {
	char exp1[] = "ls";
	char exp2[] = "cd proj";
	char exp3[] = "rm proj proj";

	noeud *n=creer_arbre();
	liste_noeud *liste1=creer_liste();
	noeud *fils1=creer_fichier(n,"prout"); 
	noeud *fils2=creer_fichier(n,"crampte"); 
	noeud *fils3=creer_dossier(n,"stylo", liste1); 

	ajouter_elt(n->fils, fils1);
	ajouter_elt(n->fils, fils2);
	ajouter_elt(n->fils, fils3);
	
	instruction *i=generer_instruction("ls");

	ls(n,i);

	printf("%d\n", get_commande(exp1)); 
	instruction* instr1 = generer_instruction(exp1); 
	afficher_instruction(instr1);

	printf("%d\n", get_commande(exp2));
	instruction* instr2 = generer_instruction(exp2);
	afficher_instruction(instr2);

	printf("%d\n", get_commande(exp3));
	instruction* instr3 = generer_instruction(exp3);
	afficher_instruction(instr3);

	return EXIT_SUCCESS;
}
