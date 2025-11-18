/**************************************/
/** Codage de Huffman: Décompression **/
/**************************************/

#ifndef HUFFDECOMP_H_
#define HUFFDECOMP_H_

#include "alloc.h"
#include "dequeue.h"
#include "hufftree.h"
#include <stdbool.h>
#include <stdio.h>

// Lecture de la taille du fichier décompressé dans le fichier compressé.
// Le fichier doit être ouvert en lecture.
// La taille est codée sur les 4 premiers octets.
unsigned int read_size(FILE *in);

// Lecture d'un code de Huffman à partir du buffer et du fichier compressé.
// Le fichier doit être ouvert en lecture.
//
// Lit un code entier et retourne la valeur qui lui est associée par l'arbre de
// Huffman.
//
// Tant que le buffer est non-vide, c'est dans celui-ci qu'on lit.
//
// Si le buffer est vide, on lit un octet dans le fichier pour insérer ses 8
// bits dans le buffer.
//
// Le buffer est potentiellement non-vide à la fin de la lecture d'un code. Les
// bits qui restent dans le buffer font partie du prochain code à lire.
int read_huffcode(FILE *in, dequeue *deq, huffnode *thetree);

// Procédure de décompression.
// Le flux in doit être ouvert en lecture.
// Le flux out doit être ouvert en écriture.
// Décompresse le fichier in et écrit la version décompressée dans out.
void decompress_file(FILE *in, FILE *out);

#endif
