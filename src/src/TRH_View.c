/**
 * ALGAV Project
 * TRH View implementation
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com> ( v2.0 )
 *
 * @copyright (c) 2014, toumlilt
 *
 * @version 2.0
 * @package toumlilt/M1/ALGAV
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <TRH_View.h>

/* @TODO j'ai pas pris le temps de tout arranger ... */

const char* TRHdotFilename = "./svg/TRH.dot";

/******************************************************************************
 * Private declarations :
 *****************************************************************************/
void TRHexportFromNodeRecursive(TRHnode* node, FILE* dotFile);
/*****************************************************************************/

void TRHexportToDOTFile(TRHtree* tree)
{
  FILE* dotFile;
  TRHnode *node = TRHgetTopOfTree(tree);

  if( !TRHisEmptyTree(tree) ){
    if(!(dotFile = fopen(TRHdotFilename, "w"))){
      perror("Error: TRH_View: open()\n");
      exit(2);
    }

    fprintf(dotFile, "graph TRH_View {\n");
    fprintf(dotFile, "\t{%d [label=\"%c\"];}\n",TRHgetId(node),TRHgetContent(node));

    TRHexportFromNodeRecursive(node, dotFile);

    fprintf(dotFile, "}\n");

    fclose(dotFile);
  }
}


void TRHexportFromNodeRecursive(TRHnode* node, FILE* dotFile)
{
  TRHnode* n = NULL;

  if(TRHhasLowChild(node)){
    n = TRHgetLowChild(node);
    if(!TRHisEOWNode(n))
      fprintf(dotFile, "\t%d -- {%d [label=\"%c\"];} [label=\"<\"];\n",
	     TRHgetId(node), TRHgetId(n), TRHgetContent(n));
    else{
      fprintf(dotFile, "\t%d -- {%d [label=\"%c : %d\", color=lightblue2, style=filled];}",TRHgetId(node), TRHgetId(n), TRHgetContent(n), TRHgetKeyValue(n));
      fprintf(dotFile, "[label=\"<\"];\n");
    }
    TRHexportFromNodeRecursive(n, dotFile);
  }

  if(TRHhasEqualChild(node)){
    n = TRHgetEqualChild(node);
    if(!TRHisEOWNode(n))
      fprintf(dotFile, "\t%d -- {%d [label=\"%c\"];} [label=\"=\"];\n",
	     TRHgetId(node), TRHgetId(n), TRHgetContent(n));
    else{
      fprintf(dotFile, "\t%d -- {%d [label=\"%c : %d\", color=lightblue2, style=filled];}\n", TRHgetId(node), TRHgetId(n), TRHgetContent(n), TRHgetKeyValue(n));
      fprintf(dotFile, "[label=\"=\"];\n");
    }
    TRHexportFromNodeRecursive(n, dotFile);
  }

  if(TRHhasHighChild(node)){
    n = TRHgetHighChild(node);
    if(!TRHisEOWNode(n))
      fprintf(dotFile, "\t%d -- {%d [label=\"%c\"];} [label=\">\"];\n",
	     TRHgetId(node), TRHgetId(n), TRHgetContent(n));
    else{
      fprintf(dotFile, "\t%d -- {%d [label=\"%c : %d\", color=lightblue2, style=filled];}\n", TRHgetId(node), TRHgetId(n), TRHgetContent(n), TRHgetKeyValue(n));
      fprintf(dotFile, "[label=\">\"];\n");
    }
    TRHexportFromNodeRecursive(n, dotFile);
  }
}
