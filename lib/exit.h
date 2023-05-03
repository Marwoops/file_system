#ifndef ERREUR_H
#define ERREUR_H

#define EXIT_MALLOC 1
#define EXIT_NOM_INVALIDE 2
#define EXIT_COMMANDE_INVALIDE 3
#define EXIT_TROP_D_ARGUMENTS 4
#define EXIT_ARGUMENT_INVALIDE 5
#define EXIT_ARGUMENT_NULL 6

#include <stdio.h>

extern void exit_malloc(void);
extern void exit_nom_invalide(char *);
extern void exit_commande_invalide(void);
extern void exit_trop_d_arguments();
extern void exit_argument_invalide(char *);
extern void exit_argument_null(char*);

#endif
