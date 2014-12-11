#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <BRD_API.h>
#include <BRD_SVGView.h>

int main(int argc, char** argv)
{
  
  if( argc != 2 ){
    fprintf(stderr, "Error : Incorrect number of args\n");
    fprintf(stderr, "Usage : unit_test_1.c <testFile>\n");
    exit(1);
  }
  
  printf(" BRDinitTreeFromFile\n");

  clock_t begin, end;
  double time_spent;

  begin = clock();
  BRDtree* tree = BRDinitTreeFromFile(argv[1]);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf(" Init Time Spent : %f sec\n\n", time_spent);

  printf("2. J'insère le mot : bonjour\n");
  begin = clock();
  BRDaddWord(tree, "bonjour", 7);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Temps d'insertion : %f sec\n\n", time_spent);

  printf("3. Je recherche le mot : bonjour\n");
  begin = clock();
  if( BRDsearchWord(tree, "bonjour", 7) )
    printf("mot trouvé !\n");
  else
    printf("mot non trouvé !\n");
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Temps de recherche : %f sec\n\n", time_spent);

  printf("4. Je compte les mots de l'arbre :\n");
  begin = clock();
  int nbMots = BRDcountTreeWords(tree);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Nombre total de mots = %d\n", nbMots);
  printf(" Temps d'exec : %f sec\n\n", time_spent);

  printf("5. comptage nil:\n");
  begin = clock();
  nbMots = BRDcountTreeNullNodes(tree);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Nombre total de null = %d\n", nbMots);
  printf(" Temps d'exec : %f sec\n\n", time_spent);

  printf("6. Hauteur de l'arbre:\n");
  begin = clock();
  nbMots = BRDcountTreeHeight(tree);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Hauteur de l'arbre = %d\n", nbMots);
  printf(" Temps d'exec : %f sec\n\n", time_spent);

  printf("7. profondeur moyenne:\n");
  begin = clock();
  nbMots = BRDcountAverageDepth(tree);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" profondeur moyenne = %d\n", nbMots);
  printf(" Temps d'exec : %f sec\n\n", time_spent);

  printf("8. Nb prefixe 'ac' :\n");
  begin = clock();
  nbMots = BRDcountTreePrefixeOccurrence(tree, "ac", 2);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Nb prefixe = %d\n", nbMots);
  printf(" Temps d'exec : %f sec\n\n", time_spent);


  printf(" BRDexportSVG\n");
  BRDexportToSvgFile(tree, "./svg/BRD.svg");
  
  printf(" BRDfreeTree.\n");
  BRDfreeTree(tree);

  printf(" 4.\n");
  return EXIT_SUCCESS;
}
