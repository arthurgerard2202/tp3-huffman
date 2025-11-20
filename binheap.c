#include "binheap.h"

/*************************/
/* Fonctions auxiliaires */
/*************************/

/*
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
*/
/* La fonction de comparaison pour les tas d'entiers */
bool fcmp_int(void *x, void *y) {
  return *(int *)x < *(int *)y;
}

static void switch_elements_binheap(binheap *p, int i, int j){
  void *tmp = p->array[i];
  p->array[i] = p->array[j];
  p->array[j] = tmp;
}

/* Fonctions de navigation dans un arbre représenté par un tableau */
int left_binheap(int i) {
  return 2 * i + 1;
}
int right_binheap(int i) {
  return 2 * i + 2;
}
int parent_binheap(int i) {
  if (i==0) {
    return false;
  }
  if (i%2==1) {
    return (i-1)/2;
  }
  else {
    return (i-2)/2;
  }
}

bool isvalid_binheap(binheap *p, int i) {
  if (i < 0 || i >= p->size_heap) {
    return false;
  }
  return true;
}

/* Modification de la taille du tableau */
static void grow_binheap(binheap *p) {
  void ** new_array = (malloc(sizeof(void **)*p->size_array*2));
  for (int i=0; i < p->size_array; i++){
    new_array[i] = p->array[i];
  }
  p->array = new_array;
  p->size_array=p->size_array*2;
}

static void shrink_binheap(binheap *p) {
  void ** new_array = (malloc(sizeof(void **)*p->size_array/2));
  for (int i=0; i < p->size_array; i++){
    new_array[i] = p->array[i];
  }
  p->array = new_array;
  p->size_array=p->size_array/2;
}


/************************/
/* Fonctions primitives */
/************************/

/* Création d'un tas vide */
binheap *create_binheap(bool (*fc)(void *, void *)) {
  binheap *p = malloc(sizeof(binheap));
  p->array = malloc(sizeof(void*));
  p->size_array = 1;
  p->size_heap = 0;
  p->fc = fc;
  return p;
}

/* Suppression */
void delete_binheap(binheap *p) {
  free(p->array);
  free(p);
}

/* Test du vide */
bool isempty_binheap(binheap *p) {
  return p->size_heap == 0;
}

/* Récupération de la taille */
int getsize_binheap(binheap *p) {
  return p->size_heap;
}

int getsize_array(binheap *p) {
  return p->size_array;
}

/* Insertion d'une valeur */
void push_binheap(binheap *p, void *val) {
  int i = getsize_binheap(p);
  if (i == getsize_array(p)){
    grow_binheap(p);
  }
  p->array[i] = val;
  p->size_heap++;
  
  // Remonter l'élément tant que la propriété du tas n'est pas respectée
  while (i > 0 && p->fc(p->array[i], p->array[parent_binheap(i)])){
    switch_elements_binheap(p, i, parent_binheap(i));
    i = parent_binheap(i);
  }
}

/* Récupération du minimum sans le retirer */
void *peekmin_binheap(binheap *p) {
  return p->array[0];
}

/* Récupération du minimum en le retirant */
void *popmin_binheap(binheap *p) {
  if (isempty_binheap(p)) {
    return NULL;
  }
  
  void *output = p->array[0];
  p->size_heap--;
  
  if (p->size_heap > 0) {
    p->array[0] = p->array[p->size_heap];
    
    // Descendre l'élément racine pour restaurer la propriété du tas
    int i = 0;
    while (left_binheap(i) < p->size_heap) {
      int left = left_binheap(i);
      int right = right_binheap(i);
      int smallest = i;
      
      if (left < p->size_heap && p->fc(p->array[left], p->array[smallest])) {
        smallest = left;
      }
      if (right < p->size_heap && p->fc(p->array[right], p->array[smallest])) {
        smallest = right;
      }
      
      if (smallest == i) {
        break;
      }
      
      switch_elements_binheap(p, i, smallest);
      i = smallest;
    }
  }
  
  return output;
}
