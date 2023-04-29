#include <stdlib.h>
#include <stdio.h>

#include "arbre.h"
#include "liste.h"
#include "instruction.h"

int main(int argc, char* argv[]) {
	/*char exp1[] = "ls";
	char exp2[] = "cd proj";
	char exp3[] = "rm proj proj";
	char exp4[]= "pwd";

	char crampte[]="touch crampte";
	char prout[]="touch prout";
	char stylo[]="mkdir stylo";
	char bic[]="mkdir bic";

	noeud *n=creer_arbre();

	
	instruction *i=generer_instruction(exp1);
	instruction *t1=generer_instruction(prout);
	instruction *t2=generer_instruction(crampte);
	instruction *m1=generer_instruction(stylo);
	instruction *m2=generer_instruction(bic);

	touch(n,t1); 
	touch(n,t2); 
	ls(n,i);
	mkdir(n,m1);
	ls(n,i);
	mkdir(get_elt(n->fils, "stylo"), m2);
	ls(get_elt(n->fils, "stylo"), i);

	printf("%d\n", get_commande(exp1)); 
	instruction* instr1 = generer_instruction(exp1); 
	afficher_instruction(instr1);

	printf("%d\n", get_commande(exp2));
	instruction* instr2 = generer_instruction(exp2);
	afficher_instruction(instr2);

	printf("%d\n", get_commande(exp3));
	instruction* instr3 = generer_instruction(exp3);
	afficher_instruction(instr3);
	*/

	size_t n = 0;
	bool est_abs = false;
	char test[] = "/alo/merci/au/revoir";
	char **decoupe = get_chemin(test, &est_abs, &n);

	for (size_t i = 0; i < n; ++i) {
		printf("%s\n", *(decoupe+i));
	}

	return EXIT_SUCCESS;
}
