/******************************************************/
/** Implémentation des tuyaux étendus par un tableau **/
/******************************************************/

// Ce module permet de manipuler un type de donnée appelé "tuyau" (dequeue en
// anglais).
//
// Informellement, un tuyau est un type de données rassemblant les
// fonctionnalités des piles et des files : on peut supprimer et ajouter des
// éléments à chaque extrémité du tuyau.

// Les fonctions ci-dessous implémentent en fait une extension de ce type : en
// plus de pouvoir ajouter ou retirer un élément à gauche ou à droite du tuyau,
// on peut aussi lire la i-ème valeur à partir de la gauche ou de la droite (en
// revanche, on ne peut pas écrire "au milieu" d'un tuyau). Voir les fonctions
// leftread et rightread.
//
// L'implémentation est faite par un tableau dynamique. Les fonctions
// auxiliaires grow_dequeue et shrink_dequeue permettent de modifier la taille
// du tableau en conséquence. La fonction print_dequeue permet d'afficher le
// contenu du tuyau.
//
// Une version compilée Linux de ce module vous est fournie : dequeue.o.

#ifndef DEQUEUE_H_
#define DEQUEUE_H_

#include <stdbool.h>

/**********************/
/* Définition du type */
/**********************/

typedef struct {
    int *array;     // Tableau des valeurs
    int size_array; // Taille du tableau des valeurs
    int left;       // Indice de la valeur à gauche du tuyau (si non-vide).
    int right;      // Indice qui suit celui de la valeur à droite du tuyau (si
                    // non-vide).
    bool empty;     // Booléen indiquant si le tuyau est vide.
} dequeue;

/*************************/
/* Fonctions auxiliaires */
/*************************/

// Double la taille du tableau utilisé dans la représentation.
void grow_dequeue(dequeue *);

// Divise par deux la taille du tableau utilisé dans la représentation
// (on supposera que seulement la moitié des cases sont utilisées dans
// la représentation).
void shrink_dequeue(dequeue *);

/************************/
/* Fonctions primitives */
/************************/

// Création
dequeue *create_dequeue(void);

// Suppression
void delete_dequeue(dequeue *);

// Taille
int getsize_dequeue(dequeue *p);

// Test du vide
bool isempty_dequeue(dequeue *);

//  Insertion
void leftinsert(int, dequeue *);
void rightinsert(int, dequeue *);

// Lecture

// Les deux fonctions suivantes étendent le type abstrait tuyau vu en TD.
// En effet, elles permettent de lire la i-ème valeur à partir de la gauche ou
// de la droite, ce qui n'était pas possible avec le type abstrait tuyau.

// Lit la ième valeur en partant de la gauche (la première à gauche a pour
// indice 0).
int leftread(dequeue *, int i);

// Lit la ième valeur en partant de la droite (la première à droite a pour
// indice 0).
int rightread(dequeue *, int i);

// Suppression

int leftpull(dequeue *);

int rightpull(dequeue *);

// Affichage d'un tuyau
// Cette primitive est déjà écrite. Utilisez-la pour vos tests.
void print_dequeue(dequeue *p);

#endif // DEQUEUE_H_
