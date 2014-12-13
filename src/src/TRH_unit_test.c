#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include <TRH_API.h>
#include <TRH_View.h>

int main(int argc, char** argv)
{
  if( argc != 2 ){
    fprintf(stderr, "Error : Incorrect number of args\n");
    fprintf(stderr, "Usage : TRH_unit_test <testFile>\n");
    exit(1);
  }

  TRHtree* tree = TRHinitTreeFromFile(argv[1]);

  TRHexportToDOTFile(tree);
  
  TRHfree(tree);
  
  return EXIT_SUCCESS;
}
