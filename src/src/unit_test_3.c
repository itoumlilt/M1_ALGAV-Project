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
    fprintf(stderr, "Usage : unit_test_3.c <testFile>\n");
    exit(1);
  }
  
  clock_t begin, end;
  double time_spent;

  printf("1.BRDinitTreeFromFile\n");
  begin = clock();
  BRDtree* tree = BRDinitTreeFromFile(argv[1]);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf(" Init Time Spent : %f sec\n\n", time_spent);

  printf("%c -- \n", BRDgetContent(BRDgetTopOfTree(tree)));
  
  printf("2. Je crée la liste des mots\n");
  begin = clock();
  ListWord* lw = BRDgetListWordFromTree(tree);
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  LWprintAllWords(lw);
  LWfreeRecursive(lw);
  printf(" Temps de création de la liste : %f sec\n\n", time_spent);
  
  printf(" BRDexportSVG\n");
  BRDexportToSvgFile(tree, "./svg/BRD.svg");
  
  printf(" BRDfreeTree.\n");
  BRDfreeTree(tree);

  printf(" 4.\n");
  return EXIT_SUCCESS;
}
