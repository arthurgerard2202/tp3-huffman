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
  return p->byte;
}

/* Retournent les fils d'un noeud */

huffnode *getleft_huffnode(huffnode *p) {
  return p->leftchild;
}

huffnode *getright_huffnode(huffnode *p) {
  return p->rightchild;
}

/* Libération d'un arbre */

void free_hufftree(huffnode *p) {
  if (p->leftchild != NULL){
    free_hufftree(p->leftchild);
  }
  if (p->rightchild != NULL){
    free_hufftree(p->rightchild);
  }
  free(p);
}

/**********************************************/
/* Fonctions manipulant les arbres de Huffman */
/**********************************************/

/* Comparaison de deux arbres */
bool compare_hufftree(void *p1, void *p2) {
  huffnode *huffnode1 = (huffnode *)p1;
  huffnode *huffnode2 = (huffnode *)p2;
  return huffnode1->freq < huffnode2->freq;
}

/* Création de l'arbre de Huffman à partir du fichier à compresser */
huffnode *datafile_to_hufftree(FILE *input) {

  /* Phase 1: création du tableau de fréquences */

  /*
  fgetc(FILE *stream) :
    - lit 1 caractère dans un fichier 
    - avance le curseur 
    - retourne -1 si la lecture a échoué 
  */

  int freq[256];
  for (int i=0;i<255;i++){
    freq[i] = 0;
  }
  while (fgetc(input) != -1){
    freq[fgetc(input)]++;
  }

  /* Phase 2: intialisation de la file de priorité à partir du tableau de
   * fréquences */

  binheap *priority_queue = create_binheap(&compare_hufftree);

  /* Phase 3: création de l'arbre de Huffman à partir de la file de priorités */

  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
    huffnode *leaf = create_huffleaf(i, freq[i]);
    push_binheap(priority_queue, leaf);
    }
  }

  while (getsize_binheap(priority_queue) > 1) {
    huffnode *left = (huffnode *)popmin_binheap(priority_queue);
    huffnode *right = (huffnode *)popmin_binheap(priority_queue);
    huffnode *merged = merge_hufftree(left, right);
    push_binheap(priority_queue, merged);
  }
  huffnode *huffman_tree = (huffnode *)popmin_binheap(priority_queue);
  delete_binheap(priority_queue);
  return huffman_tree;
}

/* Écriture de l'arbre de Huffman dans le futur fichier compressé */
void save_hufftree(huffnode *p, FILE *f) {
  if (isleaf_huffnode(p)) {
    fputc(1, f);
    fputc(p->byte, f);
  } else {
    fputc(0, f);
    save_hufftree(p->leftchild, f);
    save_hufftree(p->rightchild, f);
  }
}


/* Lecture de l'arbre de Huffman dans le fichier compressé */
huffnode *read_hufftree(FILE *f) {
  int marker = fgetc(f);
  if (marker == -1) {
    return NULL;
  }

  if (marker == 1) {
    int byte = fgetc(f);
    if (byte == EOF) {
      return NULL;
    }
    return create_huffleaf(byte, 0);
  } else {
    huffnode *left = read_hufftree(f);
    huffnode *right = read_hufftree(f);
    return merge_hufftree(left, right);
  }
}
