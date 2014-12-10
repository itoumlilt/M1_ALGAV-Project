#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <BRD_API.h>
#include <BRD_TermView.h>
#include <BRD_SVGView.h>

int main(int argc, char** argv)
{
  
  if( argc != 2 ){
    fprintf(stderr, "Error : Incorrect number of args\n");
    fprintf(stderr, "Usage : unit_test_1.c <testFile>\n");
    exit(1);
  }
  
  printf(" BRDinitTreeFromFile\n");
  BRDtree* tree = BRDinitTreeFromFile(argv[1]);

  printf(" BRDexportSVG\n");
  BRDexportToSvgFile(tree, "./svg/BRD.svg");
  
  printf(" BRDfreeTree.\n");
  BRDfreeTree(tree);

  printf(" 4.\n");
  return EXIT_SUCCESS;
}
