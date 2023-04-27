#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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


liste_noeud *creer_liste_avec_noeud(noeud* n)
{
    if (n==NULL)
    {
        return creer_liste ();
    }
    liste_noeud *l=malloc(sizeof(liste_noeud));
    l->no=n;
    l->succ=NULL;
    return l;
}


noeud *get_elt(liste_noeud* l, char nom[100])
{
    if(strcmp(nom,l->no->nom)==0)
    {
        return l->no;
    }
    if(l->succ==NULL)
    {
        return NULL;
    }
    return get_elt(l->succ, nom);
}

noeud *ajouter_elt (liste_noeud* l, noeud* n)
{
    if (l==NULL || n==NULL)
    {
        return NULL;
    }
    liste_noeud *l1=l;
    while(l1->succ!=NULL && l1!=NULL)
    {
        l1=l1->succ;
    }
    l1->succ=creer_liste_avec_noeud(n);
    return n;
}

void affiche_liste(liste_noeud *l)
{
    if(l==NULL){
        return;
    }
    printf("%s\n", l->no->nom);
    return affiche_liste(l->succ);
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
