/**
 * ALGAV Project
 * The SVG View
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */


#include <stdio.h>
#include <stdlib.h>

#include <BRDnode.h>
#include <BRDtree.h>

#include <BRD_SVGView.h>

#define SVG_BASE 15
#define SVG_FACTOR 45

/******************************************************************************
 * Définitions des fonctions privées
 *****************************************************************************/
int BRDexportToSVGFromNodeRecursive(BRDnode* tree, FILE* f, int height, int* offset, int* max_height);
int BRDgetNbDigits(int n);

/******************************************************************************
 * Définitions des fonctions d'export
 *****************************************************************************/
void BRDexportToSvgFile(BRDtree* tree, char* filename) 
{
  FILE* f;
  int i;
  int width = 0;
  int height = 0;
  int nb_digits;
  int sizes_pos;
  int rect_size_pos;

  if((f = fopen(filename,"w")) == NULL){
    perror("fopen\n");
    exit(EXIT_FAILURE);
  }

  /* Header of svg file */
  fprintf(f,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\
 \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n\
<svg viewBox = \"0 0 ");
  sizes_pos = (int)ftell(f);
  fprintf(f, "0123456789 0123456789\" version = \"1.1\"\n\
xmlns=\"http://www.w3.org/2000/svg\"\
 xmlns:xlink= \"http://www.w3.org/1999/xlink\">\n\n\
<rect ");
  rect_size_pos = (int)ftell(f);
  fprintf(f, "width=\"0123456789\" height=\"0123456789\" fill=\"white\"/>\n");

  /* Body */
  BRDexportToSVGFromNodeRecursive(BRDgetTopOfTree(tree), f, 0, &width, &height);

  /* End of file */
  fprintf(f,"\n</svg>\n");

  /* Modifying size of viewBox in svg */
  if(fseek(f, sizes_pos, SEEK_SET) == -1) {
    perror("fseek");
    exit(1);
  }
  width = 45*width+100;
  nb_digits = BRDgetNbDigits(width);
  for(i=10; i>nb_digits; i--)
    fprintf(f, " ");
  fprintf(f, "%d ", width);
  height = 47*height;
  nb_digits = BRDgetNbDigits(height);
  for(i=10; i>nb_digits; i--)
    fprintf(f, " ");
  fprintf(f, "%d", height);

  /* Modifying size of background rect in svg */
  if(fseek(f, rect_size_pos, SEEK_SET) == -1) {
    perror("fseek");
    exit(1);
  }
  nb_digits = BRDgetNbDigits(width) + BRDgetNbDigits(height);
  fprintf(f, "width=\"%d\" height=\"%d\" fill=\"white\"/>", width, height);
  for(i=20-nb_digits; i>0; i--)
    fprintf(f, " ");

  fclose(f);
}

int BRDexportToSVGFromNodeRecursive(BRDnode* node, FILE* f, int height, int* offset, int* max_height) {
  int my_offset = *offset;
  int bro_offset, gap;
  int x, y;
  
  if(node != NULL) {
    fprintf(f, "<text x=\"%d\" y=\"%d\" fill=\"black\" font-size=\"20\"><!-- offset=%d -->",
	    my_offset*SVG_FACTOR, SVG_BASE+height*SVG_FACTOR, my_offset);
    if(!BRDisEOWNode(node))
      fprintf(f, "%c</text>\n", BRDgetContent(node));
    else
      fprintf(f, "$</text>\n");
    if( BRDexportToSVGFromNodeRecursive(BRDgetFirstChild(node), f, height+1, offset, max_height) != -1) {
      x = my_offset*SVG_FACTOR+6;
      y = SVG_BASE+5+height*SVG_FACTOR;
      fprintf(f, "<path d=\"M%d,%d l0,18 l-2,0 l2,5 l2,-5 l-2,0\" style=\"stroke:black\"/>\n", x, y);
    }
    if(!BRDisEmptyNextSibling(node))
      (*offset)++;
    if((bro_offset = BRDexportToSVGFromNodeRecursive(BRDgetNextSibling(node), f, height, offset, max_height)) != -1) {
      x = my_offset*SVG_FACTOR+15;
      y = SVG_BASE-7+height*SVG_FACTOR;
      gap = bro_offset - my_offset;
      fprintf(f, "<path d=\"M%d,%d l%d,0 l0,-2 l5,2 l-5,2 l0,-2\" style=\"stroke:black\"/>\n", x, y, gap*22+23*(gap-1));
    }
    if(height > *max_height)
      *max_height = height;
    return my_offset;
  }
  return -1;
}

int BRDgetNbDigits(int n) {
  int d=1;
  while(n>9) {
    n = n/10;
    d++;
  }
  return d;
}
