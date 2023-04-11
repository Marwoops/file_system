#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "arbre.h"
#include "liste.h"

liste_noeud *creer_liste()
{
    noeud *n=malloc(sizeof(noeud));
    if (n==NULL)
    {
        return NULL;
    }
    liste_noeud *l=malloc(sizeof(liste_noeud));
    l->no=n;
    l->succ=NULL;
    return l;
}

liste_noeud *creer_liste_bis(liste_noeud *l, noeud *n)
{
    if (n==NULL)
    {
        return NULL;
    }
    liste_noeud *l1=malloc(sizeof(liste_noeud));
    l1->no=n;
    l1->succ=l;
    return l1;
}


noeud *get_elt(liste_noeud* l, char *mot) 
{
    if(strcmp(mot,l->no->nom)==0)
    {
        return l->no;
    }
    if(l->succ==NULL)
    {
        return NULL;
    }
    return get_elt(l->succ, mot);
}

noeud *ajouter_elt (liste_noeud* l, noeud* n)
{
    if (n==NULL)
    {
        return NULL;
    }
    liste_noeud  *l1= creer_liste_bis(l,n);
    return l1->no;
}

void affiche_liste(liste_noeud *l)
{
    printf("[");
    liste_noeud *l1=l;
    while(l1->succ !=NULL)
    {
        printf("%s, ", l->no->nom);
        l1=l1->succ;
    }
    printf("%s ]", l->no->nom);
}

noeud *supprimer_elt(liste_noeud* l, noeud* n)
{
    if  (n==l->no)
    {
        l->no=l->succ->no;
        l->succ=l->succ->succ;
        return n;
    }
    if(n==NULL || l->succ==NULL)
    {
        return NULL;
    }
    return supprimer_elt(l->succ, n);

}