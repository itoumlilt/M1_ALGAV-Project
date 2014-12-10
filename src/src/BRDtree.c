/**
 * ALGAV Project
 * BRDtree component Header
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
#include <sys/wait.h>
#include <sys/types.h>

#include <libASCII.h>
#include <BRDerrno.h>
#include <BRDtree.h>

/******************************************************************************
 * Private declarations
 *****************************************************************************/
int BRDaddDirectChildWord(BRDnode* node, char* word, int size);

/******************************************************************************
 * Fonctions de gestion de la structure BRDtree
 * ( ou primitives en langage STL ... )
 *****************************************************************************/

void BRDsetTopOfTree(BRDtree* tree, BRDnode* node)
{
  if( !node ){
    fprintf(stderr, "Warning: BRDtree: BRDsetTopOfTree: NULL pointer\n");
    /* @TODO clean exit flag */
    return;
  }

  tree->topOfTree = node;
}


BRDnode* BRDgetTopOfTree(BRDtree* tree)
{
  return tree->topOfTree;
}

BRDnode** BRDgetTopOfTreeAddr(BRDtree* tree)
{
  return &(tree->topOfTree);
}

/******************************************************************************
 * Fonctions de check
 *****************************************************************************/
int BRDisTopOfTree(BRDtree* tree, BRDnode* node)
{
  if( BRDgetTopOfTree(tree) == node )
    return 1;
  return 0;
}

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/

BRDtree* BRDinitTreeWithNode(BRDnode* node)
{
  BRDtree* tree = (BRDtree*)malloc(sizeof(BRDtree));

  BRDsetTopOfTree(tree, node);

  return tree;
}

BRDtree* BRDinitEmptyTree()
{
  return BRDinitTreeWithNode(BRDinitEmptyNode());
}

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

void BRDfreeTree(BRDtree* tree)
{
  BRDfreeNodeRecursive(BRDgetTopOfTree(tree));
}

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
/* word doit être valide et non vide ici */
/* avoir le size du word permet de pas le strlen à chaque fois */
int BRDaddWord(BRDtree* tree, char* word, int size)
{

  /* cette var stock toujours le firstChild du level courant */
  BRDnode** currentFirstChildAddr = BRDgetTopOfTreeAddr(tree);
  /* pour gagner du temps je récup le node d'insertion à chaque fois */
  BRDnode* insNode;
  
  /* si l'arbre est vide initialement
   * j'insère directement tout le mot
   * cas d'init de départ ...
   */
  if( BRDisEOWNode(*currentFirstChildAddr) ){
    BRDsetContent(*currentFirstChildAddr, word[0]);
    return BRDaddDirectChildWord(*currentFirstChildAddr, word+1, size-1);
  }

  int i;
  for(i=0; i<size; i++){
    /* on insère d'abord la lettre dans sa place au niveau */
    insNode = BRDinsertCharInNodeLevel(currentFirstChildAddr, word[i]);
    /* puis on initialise son fils */
    /* s'il est vide on fait une insertion direct du reste des mots */
    if( BRDisEmptyFirstChild(insNode)){
      return BRDaddDirectChildWord(insNode, word+i+1, size-i-1);
    }
    /* sinon on inserera sur le niveau du firstChild à l'itératon suivante */
    currentFirstChildAddr = BRDgetFirstChildAddr(insNode);
  }

  /* on insère le noeud EOW */
  BRDinsertCharInNodeLevel(currentFirstChildAddr, ASCII_EOW);
  
  return 0;
}

/**
 * Ajoute directement le mot fils par fils
 * rapide dans le cas d'une insertion dans un noeud == NULL
 */
int BRDaddDirectChildWord(BRDnode* node, char* word, int size)
{
 
  BRDnode* previous = node;
  BRDnode* child;
  int i;
  
  for(i=0; i<size; i++){
    child = BRDinitNodeWithValue(word[i]);
    BRDsetFirstChild(previous, child);
    previous = child;
  }

  child = BRDinitEmptyNode();
  BRDsetFirstChild(previous, child);

  return 0;
}

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/
BRDnode* BRDsearchNodeWithValueInLevel(BRDnode* level, char c)
{
  BRDnode* node = level;

  while(node){
    if(BRDgetContent(node) == c)
      return node;
    node = BRDgetNextSibling(node);
  }

  return NULL;
}
