/**
 * ALGAV Project
 * Terminal View
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <BRDnode.h>
#include <BRDtree.h>
#include <BRD_API.h>
#include <BRD_TermView.h>

/* @TODO c'est quoi cet MVC tout pourri, je veux du vrai MVC après ! */

/******************************************************************************
 * Private declarations
 *****************************************************************************/
void BRDprintNodeRecursive(BRDnode* node, int lvl);
void BRDprintNode(BRDnode* node, int lvl);

/******************************************************************************
 * Fonctions d'affichage
 *****************************************************************************/

void BRDprintTree(BRDtree* tree)
{
  BRDprintNodeRecursive(BRDgetTopOfTree(tree), 0);
}

void BRDprintNodeRecursive(BRDnode* node, int lvl)
{
  int nextSiblingFlag = 0;

  BRDprintNode(node, lvl);

  if( BRDhasNextSibling(node) ){
    nextSiblingFlag = 1;
    if( !fork() ){
      BRDprintNodeRecursive(BRDgetNextSibling(node), lvl);
      exit(0);
    }
  }

  if( BRDhasFirstChild(node) ){
    BRDprintNodeRecursive(BRDgetFirstChild(node), lvl+1);
  }

  if( nextSiblingFlag )
    wait(NULL);
  
}

void BRDprintNode(BRDnode* node, int lvl)
{
  char n[3];
  
  n[0] = BRDgetContent(node);
  n[1] = ( BRDisEmptyFirstChild(node) ) ? 'x' : '.';
  n[2] = ( BRDisEmptyNextSibling(node) ) ? 'x' : '.';

  printf("%d : %c,%c,%c\n",lvl, n[0], n[1], n[2]);
}
