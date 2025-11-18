/************************************/
/** Codage de Huffman: Compression **/
/************************************/

#include "huffcomp.h"

/**********************************/
/* Fonctions manipulant les codes */
/**********************************/

/* Construction du tableau des codes à partir de l'arbre de Huffman */
huffcode **create_huffdict(huffnode *tree) {
  // À écrire
  return NULL;
}

/* Suppression du tableau de code */
void delete_huffdict(huffcode **dict) {
  // À écrire
}

/***********************************************/
/** Fonction pour la compression d'un fichier **/
/***********************************************/

/* Écriture d'un unsigned int sur 4 octets dans un fichier */
void write_size(FILE *output, unsigned int size) {
  // À écrire
}

/* Insertion d'un code à droite d'un tuyau servant de tampon */
void insert_code_in_buffer(dequeue *buffer, huffcode *code) {
  // À écrire
}

/* Calcule l'octet correspondant aux 8 derniers éléments d'un tuyau servant de
 * tampon */
int buffer_to_byte(dequeue *buffer) {
  // À écrire
  return 0;
}

/* Procédure de compression */
void compress_file(FILE *in, FILE *out) {
  /* Phase 1: calcul de la taille de l'arbre et du dictionnaire à partir du
   * fichier source */

  // À écrire

  /* Phase 2: écriture de la taille du fichier original */

  // À écrire

  /* Phase 3: écriture de l'arbre en représentation préfixe */

  // À écrire

  /* Phase 4: écriture du codage */
}
