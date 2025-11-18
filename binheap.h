/************************************************************************/
/** Files de priorité: implémentation d'une tas binaire par un tableau **/
/************************************************************************/

#ifndef BINHEAP_H_
#define BINHEAP_H_

#include "alloc.h"
#include <stdbool.h>
#include <stdio.h>

// On travaille avec des tas génériques: le type des valeurs n'est pas fixé
// Pour ce faire, les éléments du tas seront des pointeurs génériques (void *).
// Le tas ne contiendra donc pas directement les valeurs mais des pointeurs
// sur celles-ci.
//
// Puisque le type des valeurs n'est pas fixé, la fonction de comparaison qui
// sert à ordonner les éléments du tas est un paramètre de ce tas. On utilise
// pour cela des pointeurs de fonctions: un des champs du type sera un pointeur
// sur une fonction qui associe un Booléen à deux éléments de type void * (qui
// indique si le premier est considéré comme "plus petit" que le deuxième).

typedef struct {
  // Tableau stockant des pointeurs vers chaque valeur du tas
  void **array;
  // Taille totale du tableau
  int size_array;
  // Taille du tas (nombres de case utilisées dans le tableau)
  int size_heap;
  // Pointeur sur la fonction de comparaison utilisée par le tas
  bool (*fc)(void *, void *);
} binheap;

/* Fonctions intermédiaires */

/* Retourne la taille du tas */
int getsize_binheap(binheap *p);

/* Retourne la taille du tableau */
int getsize_array(binheap *p);

/* Echange la place de deux éléments dans le tas */
static void switch_elements_binheap(binheap *p, int i, int j);

/*************************/
/* Fonctions auxiliaires */
/*************************/

/* La fonction de comparaison pour les tas d'entiers */
bool fcmp_int(void *x, void *y);
// Déjà écrite dans binheap.c

/* Fonctions de navigation dans un arbre représenté par un tableau */
int left_binheap(int i);
// Retourne l'indice du fils gauche du noeud à l'indice i
int right_binheap(int i); // Fils droit
// Retourne l'indice du fils droit du noeud à l'indice i
int parent_binheap(int i); // Parent
// Retourne l'indice du parent du noeud à l'indice i
bool isvalid_binheap(binheap *p, int i);
// Teste si l'indice i correspond à un noeud est valide dans le tas p

/************************/
/* Fonctions primitives */
/************************/

/* Création d'un tas vide */
binheap *create_binheap(bool (*)(void *, void *));
// Le paramètre est un pointeur de fonction
// Il faut lui donner l'adresse de la fonction de comparaison à utiliser
// Par exemple, pour créer un tas d'entier on appellera la primitive avec
// l'adresse de la fonction fcmp_int ci-dessus:
// p = create_binheap(&fcmp_int);

/* Suppression */
void delete_binheap(binheap *);

/* Test du vide */
bool isempty_binheap(binheap *);

/* Taille */
int getsize_binheap(binheap *);

/* Insertion d'une valeur */
void push_binheap(binheap *, void *);

/* Récupération du minimum sans le retirer */
void *peekmin_binheap(binheap *);

/* Récupération du minimum en le retirant */
void *popmin_binheap(binheap *);

#endif
