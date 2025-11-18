#include "hufftree.h"

/************************************/
/* Primitives des arbres de Huffman */
/************************************/

/* Création d'une feuille */
huffnode *create_huffleaf(int byte, int freq) {
  huffnode *leftchild = malloc(sizeof(huffnode*));
  huffnode *rightchild = malloc(sizeof(huffnode*));
  huffnode * p = malloc(sizeof(huffnode*));
  p->leftchild = leftchild;
  p->rightchild = rightchild;
  p->byte = byte;
  p->freq = freq;
  
  return p;
}

/* Fusion de deux arbres avec un nouveau noeud racine */
huffnode *merge_hufftree(huffnode *pl, huffnode *pr) {
  huffnode*p = create_huffleaf(0,pl->freq+pr->freq);
  p->leftchild = pl;
  p->rightchild = pr;
  return p;
}

/* Teste si un noeud est une feuille */
bool isleaf_huffnode(huffnode *p) {
  return ((p->leftchild == NULL) && (p->rightchild == NULL));
}

/* Retourne la valeur de l'octet correspondant à un noeud */
int getbyte_huffnode(huffnode *p) {
  // À écrire
  return 0;
}

/* Retournent les fils d'un noeud */

huffnode *getleft_huffnode(huffnode *p) {
  // À écrire
  return NULL;
}
huffnode *getright_huffnode(huffnode *p) {
  // À écrire
  return NULL;
}

/* Libération d'un arbre */

void free_hufftree(huffnode *p) {
  // À écrire
}

/**********************************************/
/* Fonctions manipulant les arbres de Huffman */
/**********************************************/

/* Comparaison de deux arbres */
bool compare_hufftree(void *p1, void *p2) {
  // À écrire
  return true;
}

/* Création de l'arbre de Huffman à partir du fichier à compresser */
huffnode *datafile_to_hufftree(FILE *input) {
  /* Phase 1: création du tableau de fréquences */

  // À écrire

  /* Phase 2: intialisation de la file de priorité à partir du tableau de
   * fréquences */

  // À écrire

  /* Phase 3: création de l'arbre de Huffman à partir de la file de priorités */

  // À écrire

  return NULL;
}

/* Écriture de l'arbre de Huffman dans le futur fichier compressé */
void save_hufftree(huffnode *p, FILE *f) {
  // À écrire
}

/* Lecture de l'arbre de Huffman dans le fichier compressé */
huffnode *read_hufftree(FILE *f) {
  // À écrire
  return NULL;
}
