/**
 * ALGAV Project
 * BRDtree component Header
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @copyright (c) 2014, AFFES
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include <TRHtree.h>


/******************************************************************************
 * Fonctions de gestion de la structure BRDtree
 * ( ou primitives en langage STL ... )
 *****************************************************************************/


int TRHsetTopOfTree(TRHtree* tree, TRHnode* node)
{
  tree->topOfTree = node;
  return 0;
}


TRHnode* TRHgetTopOfTree(TRHtree* tree)
{
  return tree->topOfTree;
}


TRHnode** TRHgetTopOfTreeAddr(TRHtree* tree)
{
  return &(tree->topOfTree);
}


/******************************************************************************
 * Fonctions de check
 *****************************************************************************/


int TRHisEmptyTree(TRHtree* tree)
{
  if(tree == NULL)
    return 1;
  return 0;
}


int TRHisTopOfTree(TRHtree* tree, TRHnode* node)
{
  if(TRHgetTopOfTree(tree) == node)
    return 1;
  return 0;
}


/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/


TRHtree* TRHinitTreeWithNode(TRHnode* node)
{
  TRHtree* tree = (TRHtree*)malloc(sizeof(TRHtree));
  TRHsetTopOfTree(tree,node);
  return tree;
}


TRHtree* TRHinitEmptyTree()
{
  return TRHinitTreeWithNode(NULL);
}


/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

int TRHfreeTree(TRHtree* tree)
{
  if(!TRHisEmptyTree(tree)){
    TRHfreeNodeRecursive(TRHgetTopOfTree(tree));
    free(tree);
    return 0;
  }
  return -1;
}


/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/

int TRHaddWord(TRHtree* tree, char* word, int size, int value)
{
  TRHaddWordRecursive(TRHgetTopOfTreeAddr(tree),word,size,value);
  return 0;
}

int TRHaddWordRecursive(TRHnode** node, char* word, int size, int value)
{
  if (TRHisEmptyNode(*node) && strlen(word) == 1){
    *node = TRHaddWordBuildHypster(*node,word,value);
    return 0;
  }
  else {
    if (word[0] < TRHgetContent(*node))
      TRHaddWordRecursive(TRHgetLowChildAddr(*node),word,size,value);
    else if (word[0] > TRHgetContent(*node))
      TRHaddWordRecursive(TRHgetHighChildAddr(*node),word,size,value);
    else if( strlen(word) == 1)
      TRHsetValue(*node,value);
    else
      TRHaddWordRecursive(TRHgetEqualChildAddr(*node),&word[1],size,value);
    return 0;
  }
  return -1;
}

TRHnode* TRHaddWordBuildHypster(TRHnode *node, char* word, int value)
{
  TRHnode* n = NULL;
  if (strlen(word) == 1)
    return TRHinitNodeWithContentAndValue(word[0],value);
  else{
    n = TRHinitNodeWithContentAndValue(word[0],value);
    TRHsetEqualChild(n,TRHaddWordBuildHypster(n,&word[1],value));
    return TRHgetEqualChild(node);
  }
}



