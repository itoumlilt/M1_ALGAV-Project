/**
 * ALGAV Project
 * TRHtree component implementation
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com> ( v2.0 )
 *
 * @copyright (c) 2014, toumlilt
 *
 * @version 2.0
 * @package toumlilt/M1/ALGAV
 */

#include <stdlib.h>
#include <stdio.h>

#include <TRHtree.h>

int global_keyValue = 0;


/******************************************************************************
 * Getters / Setters ( primitives )
 *****************************************************************************/

/**
 * TRHtree's topOfTree setter
 * @param tree
 * @param node
 */
void TRHsetTopOfTree(TRHtree* tree, TRHnode* node)
{
  tree->topOfTree = node;
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

int TRHgetNewKeyValue()
{
  global_keyValue++;
  return global_keyValue-1;
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
  if(TRHisEmptyNode(TRHgetTopOfTree(tree)))
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
void TRHfreeTree(TRHtree* tree)
{
  if( !TRHisEmptyTree(tree) )
    TRHfreeNodeRecursive(TRHgetTopOfTree(tree));
  free(tree);
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
void TRHaddWord(TRHtree* tree, char* word, int size)
{
  TRHaddWordToNodeRecursive(TRHgetTopOfTreeAddr(tree), word, size);
}

/**
 * TRHtree's add word recursive.
 * Insere un mot dans l'abre en parcourant l'un des noeuds fils a chaque fois.
 * @param node
 * @param word the word to add
 * @param size size of word
 * @param value
 */
void TRHaddWordToNodeRecursive(TRHnode** node, char* word, int size)
{
  if( !(*node) ){
    *node = TRHinitBranchWithWord(word, size);
    return;
  }

  if( TRHgetContent(*node) < word[0] ) {
    TRHaddWordToNodeRecursive(TRHgetHighChildAddr(*node), word, size);
  }
  else if( TRHgetContent(*node) > word[0] ) {
    TRHaddWordToNodeRecursive(TRHgetLowChildAddr(*node), word, size);
  }
  else {
    if( size > 1){
      TRHaddWordToNodeRecursive(TRHgetEqualChildAddr(*node), word+1, size-1);
    } else {
      /* si c'est la dernière lettre */
      if( !TRHisEOWNode(*node) ) { /* s'il n'est pas déjà EOW */
	TRHsetKeyValue(*node, TRHgetNewKeyValue());
      }
    }
  }
}

/**
 * TRHtree's add word to node direct building
 * Construit directement une branche
 * ( utilisable dans le cas d'un noeud null à l'insertion )
 * @param node
 * @param word the word to add
 * @param size size of word
 * @param value
 * @return TRHnode* la branche du mot construite
 */
TRHnode* TRHinitBranchWithWord(char* word, int size)
{
  TRHnode* node = NULL;
  TRHnode* insNode;
  int i;

  for(i=0; i<size; i++){
    if( !i ){
      node = TRHinitNodeWithContent(word[i]);
      insNode = node;
    } else {
      TRHsetEqualChild(insNode, TRHinitNodeWithContent(word[i]));
      insNode = TRHgetEqualChild(insNode);
    }
  }

  if(i) /* si on a inséré quelque chose ... */
    TRHsetKeyValue(insNode, TRHgetNewKeyValue());

  return node;
}
