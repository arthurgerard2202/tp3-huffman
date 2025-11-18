#include "alloc.h"
#include "binheap.h"
#include "error.h"
#include "huffcomp.h"
#include "huffdecomp.h"
#include "hufftree.h"
#include "testprint.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void test_heap(int *tab, int size);

/********************************/
/* Fonction main pour les tests */
/********************************/

// clang-format off
static struct option long_options[] = {
    {"help"    , no_argument,       NULL, 'h'},
    {"tree"    , no_argument      , NULL, 'T'},
    {"dict"    , no_argument      , NULL, 'D'},
    {"decomp"  , no_argument,       NULL, 'd'},
    {"heap"    , optional_argument, NULL, 'H'},
    {"output"  , required_argument, NULL, 'o'},
    {"seed"    , required_argument, NULL, 's'},
    //
    {NULL, 0, NULL, 0}};
// clang-format on

#define DEFAULT_HEAP_SIZE 10
int size_heap        = DEFAULT_HEAP_SIZE;
int seed             = -1;
bool decompress_mode = false, test_binheap_mode = false, huffdict = false,
     hufftree     = false;
char *outfilename = NULL;

static void usage(char *progname) {
  printf("\nUsage: %s [options]\n\n", progname);
  printf("Options disponibles :\n"
         "\t--help ou -h :"
         "\n\t\tAffiche cette aide.\n"
         "\n"
         "\t--tree ou -T:"
         "\n\t\tAffiche l'arbre de Huffman en cas de compression (ce n'est pas "
         "fait par défaut).\n"
         "\n"
         "\t--dict ou -D:"
         "\n\t\tAffiche le dictionnaire en cas de compression (ce n'est pas "
         "fait par "
         "défaut).\n"
         "\n"
         "\t--heap=<entier>ou -H<entier>:"
         "\n\t\tTeste les fonctions de tas sur un tas de taille <entier> (%d "
         "par défaut).\n"
         "\n"
         "\t--output=<nom_fichier> ou -o<nom_fichier> :"
         "\n\t\tDéfinit le nom du fichier de sortie pour la décompression.\n"
         "\n"
         "\t--seed=<entier> ou -s<entier> :"
         "\n\t\tDéfinit la graine du générateur aléatoire pour générer un "
         "tableau.\n"
         "\n",
         DEFAULT_HEAP_SIZE);
}

static void parse_argv(int argc, char *argv[]) {
  for (;;) {
    int c = getopt_long(argc, argv, "hTdDs:o:H::", long_options, NULL);
    if (c == -1)
      break; // fin de lecture des options

    switch (c) {
    case 'h':
      usage(argv[0]);
      exit(EXIT_SUCCESS);

    case 'H':
      test_binheap_mode = true;
      size_heap         = (optarg == NULL) ? DEFAULT_HEAP_SIZE : atoi(optarg);
      break;

    case 's':
      seed = atoi(optarg);
      if (seed <= -1) {
        ERROR("La graine doit être positive\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
      }
      break;

    case 'd':
      decompress_mode = true;
      break;

    case 'D':
      huffdict = true;
      break;

    case 'T':
      hufftree = true;
      break;

    case 'o':
      outfilename = strdup(optarg);
      break;

    default:
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  parse_argv(argc, argv);

  // Initialisation du générateur de nombres aléatoires
  // Voir man 3 srandom.
  if (seed == -1) {
    seed = time(NULL) % 1000;
    INFO("Pour rejouer avec les mêmes tirages aléatoires: %s --seed=%d",
         argv[0], seed);
  }
  srandom(seed);

  // Vous pouvez ajouter des tests pour les tas binaires et les arbres de
  // Huffman.
  //
  // Pensez à utiliser les fonctions disponibles dans testprint.h
  // pour afficher les tas binaires et les arbres de Huffman

  // Test de binheap. Dans ce cas, on ne fait pas de compression/décompression.
  if (test_binheap_mode) {
    INFO("TEST DES TAS BINAIRES");
    INFO("---------------------\n");
    int *array = random_array(size_heap, 100);

    INFO("\nTableau avant tri:");
    print_array(array, size_heap);

    test_heap(array, size_heap);

    INFO("\nTableau après tri:");
    print_array(array, size_heap);
    free(array);
    return EXIT_SUCCESS;
  }

  // Ici, compression ou décompression.
  // La compression du fichier f est faite dans un fichier f.huff.
  // La décompression du fichier f.huff est faite dans le fichier f.

  if (!decompress_mode) {
    // Compression : tous les arguments suivants de main sont considérés comme
    // des noms de fichiers à compresser.

    for (int i = optind; i < argc; i++) {
      struct stat b;

      if (stat(argv[i], &b) != 0) {
        ERROR("Impossible de calculer la taille du fichier \"%s\"", argv[i]);
        continue;
      }

      if (b.st_size == 0) {
        WARNING("Fichier \"%s\" de taille nulle", argv[i]);
        continue;
      }

      INFO("Compression du fichier \"%s\" de taille %lld", argv[i],
           (long long)b.st_size);

      FILE *infile = fopen(argv[i], "r");
      if (infile == NULL) {
        ERROR("Impossible d'ouvrir le fichier à compresser \"%s\"", argv[i]);
        continue;
      }

      huffnode *t = datafile_to_hufftree(infile);

      // Arbre de Huffman
      if (hufftree) {
        INFO("Arbre de Huffman");
        print_hufftree(t);
      }

      huffcode **d = create_huffdict(t);
      if (huffdict) {
        INFO("Affichage du dictionnaire");
        print_huffdict(d);
      }

      // Création éventuelle du nom de fichier de sortie
      if (outfilename == NULL) {
        MALLOC(outfilename, strlen(argv[i]) + 6);
        strcpy(outfilename, argv[i]);
        strcpy(outfilename + strlen(outfilename), ".huff");
      }

      FILE *outfile = fopen(outfilename, "w");
      if (outfile == NULL) {
        ERROR("Impossible d'ouvrir le fichier de sortie \"%s\"", outfilename);
        continue;
      }

      INFO("Fichier compressé -> \"%s\"", outfilename);

      // Appel de la fonction de compression
      compress_file(infile, outfile);

      free(outfilename);

      // Fermeture des fichiers
      fclose(infile);
      fclose(outfile);
    }
  }

  if (decompress_mode) {
    // Décompression : tous les arguments suivants de main sont considérés comme
    // des noms de fichiers à décompresser.
    for (int i = optind; i < argc; i++) {
      FILE *infile = fopen(argv[i], "r");
      if (infile == NULL) {
        ERROR("Impossible d'ouvrir le fichier d'entrée à décompresser \"%s\"",
              argv[i]);
        continue;
      }

      INFO("Décompression de %s", argv[i]);

      // Création éventuelle du nom de fichier de sortie
      if (outfilename == NULL) {
        MALLOC(outfilename, strlen(argv[i]) + 8);
        strcpy(outfilename, argv[i]);
        strcpy(outfilename + strlen(outfilename), ".dehuff");
      }

      // Ouverture du fichier de sortie
      FILE *outfile = fopen(outfilename, "w");
      if (outfile == NULL) {
        ERROR("Impossible d'ouvrir le fichier de sortie \"%s\"", outfilename);
        continue;
      }

      // Appel de la fonction de décompression
      decompress_file(infile, outfile);

      free(outfilename);

      // Fermeture des fichiers
      fclose(infile);
      fclose(outfile);
    }
  }
  return EXIT_SUCCESS;
}

// Implémentation du tri par les tas
void test_heap(int *tab, int size) {
  int i;
  int temp[size];
  for (i = 0; i < size; i++) {
    temp[i] = tab[i];
  }

  binheap *p = create_binheap(&fcmp_int);

  printf("\nTest de push_binheap");
  printf("\n********************\n\n");
  for (i = 0; i < size; i++) {
    printf("Push de %d\n", temp[i]);
    push_binheap(p, temp + i);
    print_binheap(p);
  }
  printf("\n");
  printf("\nTest de pop_binheap");
  printf("\n*******************\n\n");
  if (p == NULL) {
    WARNING("Essai de pop sur un tas NULL, rien ne se passe\n");
    return;
  }
  for (i = 0; i < size; i++) {
    tab[i] = *(int *)popmin_binheap(p);
    printf("Élément supprimé: %d\n", tab[i]);
    print_binheap(p);
  }
}
