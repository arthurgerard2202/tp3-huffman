/******************************************/
/******************************************/
/** Fonctions d'affichage pour les tests **/
/******************************************/
/******************************************/

#ifndef TESTPRINT_H_
#define TESTPRINT_H_

#include "alloc.h"
#include "binheap.h"
#include "huffcomp.h"
#include "huffdecomp.h"
#include "hufftree.h"
#include <stdbool.h>
#include <stdio.h>

/************/
/* Tableaux */
/************/

// Affichage d'un tableau d'entiers.
void print_array(int *tab, int size);

// Affichage d'un tableau de pointeurs sur des entiers.
void print_point_array(int **tab, int size);

// Génération d'un tableau d'entiers aléatoire.
// Les entiers générés sont compris entre 0 et max.
int *random_array(int size, int max);

/****************/
/* Tas binaires */
/****************/

// Génération d'un tas à partir d'un tableau d'entiers.
//
// Attention, les éléments dans le tas seront des pointeurs vers
// les éléments du tableau pris en entrée. Il ne faut donc plus
// modifier les valeurs référencées par les pointeurs dans le
// tableau (sous peine de casser le tas).
binheap *array_to_binheap(int *array, int size);

// Affichage d'un tas binaire.
//
// Prévu pour un tas dont les éléments sont des pointeurs vers des entiers.
// On peut en construire un avec les fonctions précédentes.
// Attention à ne pas afficher des tas "trop gros". Ils sont trop larges
// pour un terminal et les retours à la ligne rendent l'affichage illisible.
void print_binheap(binheap *);

/*********************/
/* Arbres de Huffman */
/*********************/

// Affichage d'un arbre de Huffman.
//
// À nouveau, l'affichage n'est lisible que pour de "petits" arbres de Huffman.
// Faites attention à tester vos fonctions sur des fichiers qui ne contiennent
// pas beaucoup de caractères distincts (afin de minimiser la taille des
// arbres).
void print_hufftree(huffnode *);

/*******************/
/* Code de Huffman */
/*******************/

// Affichage d'un code de Huffman.
void print_code(huffcode *e);

// Affichage d'un tableau de codes de Huffman.
void print_huffdict(huffcode **dict);

#endif
