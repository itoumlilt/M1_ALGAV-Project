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
  
  printf(" BRDinitTreeFromFile\n");
  clock_t begin, end;
  double time_spent;

  begin = clock();
  BRDtree* tree = BRDinitTreeFromShakespeareFiles();
  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Init Time Spent : %f sec\n", time_spent);

  printf(" BRDexportSVG\n");
  BRDexportToSvgFile(tree, "./svg/BRD.svg");
  
  printf(" BRDfreeTree.\n");
  BRDfreeTree(tree);

  printf(" 4.\n");
  return EXIT_SUCCESS;
}
