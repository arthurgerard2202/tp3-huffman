#include "testprint.h"
#include "alloc.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BAR "-" // un tiret

typedef char *string;

// Type utilisé pour représenter les arbres de Huffman en utilisant
// des tableaux (plus pratique pour écrire la fonction d'affichage)
typedef struct {
  bool *array_af;
  int *array_val;
  int size;
} arraytree;

// Affichage d'un tableau d'entiers
void print_array(int *tab, int size) {
  int i;
  printf("{");
  for (i = 0; i < size - 1; i++) {
    printf("%d, ", tab[i]);
  }
  printf("%d}\n", tab[size - 1]);
}

// Affichage d'un tableau de pointeurs sur des entiers
void print_point_array(int **tab, int size) {
  int i;
  printf("{");
  for (i = 0; i < size - 1; i++) {
    printf("%d, ", *tab[i]);
  }
  printf("%d}\n", *tab[size - 1]);
}

// Génération d'un tableau d'entiers aléatoire
int *random_array(int size, int max) {
  int *array;
  MALLOC(array, size);
  int i;
  for (i = 0; i < size; i++) {
    array[i] = random() % (max + 1);
  }
  return array;
}

// Génération d'un tas à partir d'un tableau d'entiers
binheap *array_to_binheap(int *array, int size) {
  binheap *heap = create_binheap(&fcmp_int);
  int i;
  for (i = 0; i < size; i++) {
    push_binheap(heap, (void *)(array + i));
  }
  return heap;
}

// Affiche n fois le même la chaîne s
static void rule(int n, string s) {
  for (int i = 0; i < n; i++)
    printf("%s", s);
}

// Affichage d'un tas binaire
void print_binheap(binheap *p) {
  rule(10, BAR);
  printf("\n");

  if (p == NULL) {
    printf("Trying to print a NULL tree\n\n");
    return;
  }

  int h = 0; // Calcul de la hauteur de l'arbre (=nombre de lignes)
  int j = p->size_heap;
  while (j > 0) {
    h++;
    j = j >> 1;
  }

  int s    = 1; // nombre de caractères avant le milieu du pattern
  int B    = 1; // B = nombre de patterns dans la ligne
  j        = 0; // j = nombre d'éléments déjà affichés
  int sons = 0;

  int y;
  for (y = h - 1; y >= 0; y--, B <<= 1) {
    // On part du haut de l'arbre

    int pm = (s + 1) * (1 << y) - 1;
    int lb = (s + 1) * (1 << (y - 1)) - 1;
    int ep = 2 * pm + 1 - 2 * s;

    // ligne avec les éléments
    rule(pm - s, " ");
    for (int b = 0; b < B && (j < p->size_heap); b++) {
      // printf(" "); // cas pair
      printf("%03i ", ((int *)p->array[j])[0]);
      j++;
      if (b < B - 1)
        rule(ep - 1, " "); // -1 pour l'espace terminal
    }
    printf("\n");
    if (y == 0)
      break; // fini si dernière ligne d'éléments

    // ligne avec les branchements
    rule(lb, " ");
    for (int b = 0; b < B; b++) {
      if (right_binheap(sons) < p->size_heap) {
        printf("┌");
        rule(lb, "─");
        printf("┴");
        rule(lb, "─");
        printf("┐");
        if (b < B - 1)
          rule(pm, " ");
      } else if (left_binheap(sons) < p->size_heap) {
        printf("┌");
        rule(lb, "─");
        printf("┘");
        if (b < B - 1)
          rule(pm + 2, " ");
      }
      sons++;
    }
    printf("\n");
  }

  rule(10, BAR);
  printf("\n\n");
}

// Affichage d'un arbre de Huffman
static int maxoftwo(int a, int b) {
  if (a < b) {
    return b;
  } else {
    return a;
  }
}

static int hufftree_maxsize(huffnode *n) {
  if (n == NULL) {
    return 0;
  } else {
    return 2 * maxoftwo(hufftree_maxsize(n->leftchild),
                        hufftree_maxsize(n->rightchild)) +
           1;
  }
}

static void hufftree_fillarray(huffnode *n, int *arrayval, bool *arraytv,
                               int pos) {
  if (n != NULL) {
    arrayval[pos] = n->byte;
    arraytv[pos]  = true;
    hufftree_fillarray(n->leftchild, arrayval, arraytv, 2 * pos + 1);
    hufftree_fillarray(n->rightchild, arrayval, arraytv, 2 * pos + 2);
  }
}

static arraytree *hufftree_to_array(huffnode *n) {
  int size = hufftree_maxsize(n);
  // printf("%d\n",size);
  arraytree *new;
  MALLOC(new, 1);
  MALLOC(new->array_af, size);
  MALLOC(new->array_val, size);
  new->size = size;
  int i;
  for (i = 0; i < size; i++) {
    new->array_af[i] = false;
  }
  hufftree_fillarray(n, new->array_val, new->array_af, 0);
  return new;
}

void print_hufftree(huffnode *n) {
  arraytree *p = hufftree_to_array(n);

  rule(10, BAR);
  printf("\n");

  if (p == NULL) {
    WARNING("Essai d'affichage d'un arbre de Huffman NULL\n\n");
    return;
  }

  if (p->size == 0) {
    WARNING("Essai d'affichage d'un arbre de Huffman vide\n\n");
    return;
  }

  if (p->size == 1) {
    printf(" %c\n", n->byte);
    rule(10, BAR);
    printf("\n\n");
    return;
  }

  int h = 0; // Calcul de la hauteur de l'arbre (=nombre de lignes)
  int j = p->size;
  while (j > 0) {
    h++;
    j = j >> 1;
  }

  int s     = 0; // nombre de caractères avant le milieu du pattern
  int B     = 1; // B = nombre de patterns dans la ligne
  j         = 1; // j = nombre d'éléments déjà affichés
  int mine1 = 1;
  int sons  = 0;

  int y;
  for (y = h - 1; y >= 0; y--, B <<= 1) {
    // On part du haut de l'arbre

    int pm = (s + 1) * (1 << y) - 1;
    int lb = (s + 1) * (1 << (y - 1)) - 1;
    int ep = 2 * pm + 1 - 2 * s;

    // ligne avec les éléments
    if (y != h - 1) {
      rule(pm - s, " ");
      for (int b = 0; b < B && (mine1 < p->size); b++) {
        // printf(" "); // cas pair
        if (p->array_af[mine1] && mine1 % 2 == 1) {
          printf("│0");
        } else if (p->array_af[mine1] && mine1 % 2 == 0) {
          printf("│1");
        } else {
          printf("  ");
        }
        mine1++;
        if (b < B - 1)
          rule(ep - 1, " "); // -1 pour l'espace terminal
      }
      printf("\n");

      rule(pm - s, " ");
      for (int b = 0; b < B && (j < p->size); b++) {
        // printf(" "); // cas pair
        if (p->array_af[j] && !p->array_af[2 * j + 1] &&
            !p->array_af[2 * j + 2]) {
          char thechar = (char)p->array_val[j];
          if (thechar == '\n') {
            printf("⏎ ");
          } else if (thechar == ' ') {
            printf("␠ ");
          } else {
            printf("%c ", (char)p->array_val[j]);
          }
        } else if (p->array_af[j]) {
          printf("│ ");
        } else {
          printf("  ");
        }
        j++;
        if (b < B - 1)
          rule(ep - 1, " "); // -1 pour l'espace terminal
      }
      printf("\n");

      if (y == 0)
        break; // fini si dernière ligne d'éléments
    }

    // ligne avec les branchements
    rule(lb, " ");
    for (int b = 0; b < B; b++) {
      if (p->array_af[2 * sons + 1] && p->array_af[2 * sons + 2]) {
        printf("┌");
        rule(lb, "─");
        printf("┴");
        rule(lb, "─");
        printf("┐");
        if (b < B - 1)
          rule(pm, " ");
      } else if (p->array_af[2 * sons + 1]) {
        printf("┌");
        rule(lb, "─");
        printf("┘");
        rule(lb + 1, " ");
        if (b < B - 1)
          rule(pm, " ");
      } else if (p->array_af[2 * sons + 2]) {
        rule(lb + 1, " ");
        printf("└");
        rule(lb, "─");
        printf("┐");
        if (b < B - 1)
          rule(pm, " ");

      } else {
        rule(2 * lb + 3, " ");
        if (b < B - 1)
          rule(pm, " ");
      }
      sons++;
    }
    printf("\n");
  }

  rule(10, BAR);
  printf("\n\n");
}

/* Affichage d'un code de Huffman */
void print_code(huffcode *e) {
  CHECK_NULL(2, e, "The code entry", e->code, "The array in the code entry");
  int i;
  for (i = 0; i < e->size; i++) {
    printf("%d", e->code[i]);
  }
  printf("\n");
}

/* Affichage d'un tableau de codes de Huffman */
void print_huffdict(huffcode **codes) {
  int i;
  for (i = 0; i < 256; i++) {
    if (codes[i] != NULL) {
      printf("Valeur: %3d ", i);
      if (i == '\n') {
        printf("ASCII: ⏎ Code: ");
      } else if (i == ' ') {
        printf("ASCII: ␠ Code: ");
      } else {
        printf("ASCII: %c Code: ", i);
      }
      print_code(codes[i]);
      printf("\n");
    }
  }
}
