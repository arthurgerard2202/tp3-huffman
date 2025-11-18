/************************************/
/** Codage de Huffman: Compression **/
/************************************/

#ifndef HUFFCOMP_H_
#define HUFFCOMP_H_

#include "alloc.h"
#include "dequeue.h"
#include "hufftree.h"
#include <stdbool.h>
#include <stdio.h>

/************************************************/
/* Type utilisé pour stocker un code de Huffman */
/************************************************/

// Type pour représenter un seul code
typedef struct {
  // Le nombre de bits dans le code (un code n'aura jamais plus de 256 bits).
  unsigned char size;

  // Le tableau qui stocke le code : les valeurs sont toutes 0 ou 1.
  unsigned char *code;
} huffcode;

// Le dictionnaire contiendra tous les codes.
// Il sera de type huffcode **, et pointera vers 256 cases.
// Chacun de ses éléments sera donc de type huffcode *.
// Pour les valeurs i ayant un code, la ième case contient ce code
// Pour les valeurs i n'ayant pas de code (de fréquence nulle), la ième case
// contient NULL.

/********************************************/
/* Fonction de construction du dictionnaire */
/********************************************/

// Construction du dictionnaire à partir de l'arbre de Huffman.
huffcode **create_huffdict(huffnode *tree);

// Suppression du dictionnaire
void delete_huffdict(huffcode **dict);

/***********************************************/
/** Fonction pour la compression d'un fichier **/
/***********************************************/

// Écriture d'un unsigned int sur 4 octets dans un fichier.
// output doit être ouvert en écriture.
void write_size(FILE *output, unsigned int size);

// Insertion de tous les bits d'un code à droite d'un tuyau tampon.
// Le tuyau est supposé contenir une séquence de 0 et de 1.
void insert_code_in_buffer(dequeue *buffer, huffcode *code);

// Calcule l'octet correspondant aux 8 premiers bits à gauche d'un tuyau tampon.

// Le tuyau est supposé contenir une séquence de bits (0 ou 1) de longueur au
// moins 8 Les 8 bits lus doivent être supprimés du tuyau.
int buffer_to_byte(dequeue *buffer);

// Fonction de compression du fichier input dans output.
// input doit être ouvert en lecture.
// output doit être ouvert en écriture.
// Le fichier output devra contenir dans l'ordre :
// 1) La taille de input codée sur 4 octets
// 2) La sauvegarde de l'arbre de Huffman obtenu à partir de input.
// 3) Le codage de input.
void compress_file(FILE *input, FILE *output);

#endif
