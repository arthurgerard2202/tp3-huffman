/**************************************/
/**       Les arbres de Huffman      **/
/** Implémentation par des pointeurs **/
/**************************************/

#ifndef HUFFTREE_H_
#define HUFFTREE_H_

#include "alloc.h"
#include "binheap.h"
#include <stdbool.h>
#include <stdio.h>

/*******************************************/
/* Type utilisé pour les arbres de Huffman */
/*******************************************/

// Chaque objet correspond à un noeud de l'arbre.
// On identifie un arbre avec un pointeur vers son noeud racine.
//
// Cela explique pourquoi les fonctions manipulant les arbres prennent en
// argument un pointeur vers un noeud, et que leur nom se termine soit par
// _huffnode, soit par _hufftree.

typedef struct huffnode {
  // Fréquence
  int freq;

  // Octet codé par le noeud (significatif seulement si le noeud est une
  // feuille)
  int byte;

  // Enfant gauche (NULL si pas de fils gauche)
  struct huffnode *leftchild;

  // Enfant droit (NULL si pas de fils droit)
  struct huffnode *rightchild;
} huffnode;

/************************************/
/* Primitives des arbres de Huffman */
/************************************/

// Création d'une feuille.
// Les paramètres servent à initialiser les champs byte et freq (dans cet
// ordre).
huffnode *create_huffleaf(int byte, int freq);

// Fusion de deux arbres non-vides en utilisant un nouveau noeud racine.
// La fréquence du nouveau noeud sera la somme de celles de ses deux enfants
// Le champ byte du nouveau noeud n'est pas significatif (car ce n'est pas une
// feuille).
huffnode *merge_hufftree(huffnode *pl, huffnode *pr);

// Teste si un arbre est réduit à une seule feuille.
// On doit tester si les deux enfants du noeud racine sont NULL
bool isleaf_huffnode(huffnode *p);

// Retourne la valeur de l'octet codé dans un noeud.
// Ne doit être utilisé que sur les feuilles.
int getbyte_huffnode(huffnode *p);

// Retourne les enfants gauche et droit d'un noeud.
huffnode *getleft_huffnode(huffnode *p);
huffnode *getright_huffnode(huffnode *p);

// Libération complète d'un arbre  de Huffman.
void free_hufftree(huffnode *p);

/**********************************************/
/* Fonctions manipulant les arbres de Huffman */
/**********************************************/

// Fonction de comparaison entre deux arbres de Huffman à utiliser pour le tas
// binaire. Les deux paramètres sont donc donnés par des void *. Il faut les
// convertir ces pointeurs de façon appropriée dans la fonction
// compare_hufftree.
//
// Le plus petit de deux arbres est celui dont la racine a la plus petite
// fréquence.
bool compare_hufftree(void *p1, void *p2);

// Création de l'arbre de Huffman à partir du fichier à compresser.
// Le fichier doit être ouvert en lecture.
// L'algorithme est basé sur les files de priorités.
huffnode *datafile_to_hufftree(FILE *input);

// Écriture de l'arbre de Huffman dans le futur fichier compressé.
// Le fichier doit être ouvert en lecture.
// On stocke l'arbre par une représentation préfixe.
void save_hufftree(huffnode *p, FILE *output);

// Lecture de l'arbre de Huffman dans un fichier.
// Le fichier doit être ouvert en lecture.
// La tête de lecture doit être positionnée au début du codage de l'arbre.
huffnode *read_hufftree(FILE *in);

#endif
