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

/**
 * TRHtree's topOfTree setter
 * @param tree
 * @param node
 */
int TRHsetTopOfTree(TRHtree* tree, TRHnode* node)
{
  tree->topOfTree = node;
  return 0;
}


/**
 * TRHtree's topOfTree getter
 * @param tree
 * @return TRHnode* topOfTree's value
 */
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


/**
 * TRHtree's checker
 * @param tree
 * @return int 1 si l'abre est null, 0 sinon.
 */
int TRHisEmptyTree(TRHtree* tree)
{
  if(tree == NULL)
    return 1;
  return 0;
}


/**
 * TRHtopOfTree's checker
 * @param tree
 * @param node
 * @return int 1 si l'abre est vide, 0 sinon.
 */
int TRHisTopOfTree(TRHtree* tree, TRHnode* node)
{
  if(TRHgetTopOfTree(tree) == node)
    return 1;
  return 0;
}


/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/


/**
 * TRHtree's alloc
 * @param node content of the new TRHTree
 * @return TRHtree* le nouvel arbre créé
 */
TRHtree* TRHinitTreeWithNode(TRHnode* node)
{
  TRHtree* tree = (TRHtree*)malloc(sizeof(TRHtree));
  TRHsetTopOfTree(tree,node);
  return tree;
}


/**
 * TRHtree's empty alloc
 * @return TRHtree* le nouvel arbre créé
 */
TRHtree* TRHinitEmptyTree()
{
  return TRHinitTreeWithNode(NULL);
}


/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

/**
 * TRHtree's free.
 * Libère l'espace alloué à un arbre.
 * @param tree
 */
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

/**
 * TRHtree's add word.
 * Insere un mot dans l'abre.
 * @param tree
 * @param word the word to add
 * @param size size of word
 * @param value
 */
int TRHaddWord(TRHtree* tree, char* word, int size, int value)
{
  TRHaddWordRecursive(TRHgetTopOfTreeAddr(tree),word,size,value);
  return 0;
}

/**
 * TRHtree's add word recursive.
 * Insere un mot dans l'abre en parcourant l'un des noeuds fils a chaque fois.
 * @param node
 * @param word the word to add
 * @param size size of word
 * @param value
 */
int TRHaddWordRecursive(TRHnode** node, char* word, int size, int value)
{
  if (TRHisEmptyNode(*node) && size == 1){
    *node = TRHaddWordBuildHypster(*node,word,size,value);
    return 0;
  }
  else {
    if (word[0] < TRHgetContent(*node))
      TRHaddWordRecursive(TRHgetLowChildAddr(*node),word,size,value);
    else if (word[0] > TRHgetContent(*node))
      TRHaddWordRecursive(TRHgetHighChildAddr(*node),word,size,value);
    else if( size == 1)
      TRHsetValue(*node,value);
    else
      TRHaddWordRecursive(TRHgetEqualChildAddr(*node),&word[1],size-1,value);
    return 0;
  }
  return -1;
}

/**
 * TRHtree's add word build hypster.
 * Construit une branche de l'arbre en inserant le mot word.
 * @param node
 * @param word the word to add
 * @param size size of word
 * @param value
 * @return TRHnode* la branche du mot construite
 */
TRHnode* TRHaddWordBuildHypster(TRHnode *node, char* word,int size, int value)
{
  TRHnode* n = NULL;
  if (size == 1)
    return TRHinitNodeWithContentAndValue(word[0],value);
  else{
    n = TRHinitNodeWithContentAndValue(word[0],value);
    TRHsetEqualChild(n,TRHaddWordBuildHypster(n,&word[1],size-1,value));
    return TRHgetEqualChild(node);
  }
}
