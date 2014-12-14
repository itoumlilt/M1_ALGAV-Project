/**
 * ALGAV Project
 * TRHtree component header
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com> ( v2.0 )
 *
 * @copyright (c) 2014, toumlilt
 *
 * @version 2.0
 * @package toumlilt/M1/ALGAV
 */

#include <TRHnode.h>

#ifndef __TRHTREE_H__
#define __TRHTREE_H__

extern int global_keyValue;

typedef struct _TRHtree {
  TRHnode* topOfTree;
} TRHtree;

/******************************************************************************
 * Getters / Setters ( primitives )
 *****************************************************************************/
void TRHsetTopOfTree(TRHtree* tree, TRHnode* node);
TRHnode* TRHgetTopOfTree(TRHtree* tree);
TRHnode** TRHgetTopOfTreeAddr(TRHtree* tree);

int TRHgetNewKeyValue();

/******************************************************************************
 * Fonctions de check
 *****************************************************************************/
int TRHisEmptyTree(TRHtree* tree);
int TRHisTopOfTree(TRHtree* tree, TRHnode* node);

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/
TRHtree* TRHinitTreeWithNode(TRHnode* node);
TRHtree* TRHinitEmptyTree();
TRHnode* TRHinitBranchWithWord(char* word, int size);

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/
void TRHfreeTree(TRHtree* tree);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
void TRHaddWord(TRHtree* tree, char* word, int size);
void TRHaddWordToNodeRecursive(TRHnode** node, char* word, int size);

#endif
