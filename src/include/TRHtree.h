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

#include <TRHnode.h>

#ifndef __TRHTREE_H__
#define __TRHTREE_H__

typedef struct _TRHtree {
  TRHnode* topOfTree;
} TRHtree;

/******************************************************************************
 * Fonctions de gestion de la structure BRDtree
 * ( ou primitives en langage STL ... )
 *****************************************************************************/

int TRHsetTopOfTree(TRHtree* tree, TRHnode* node);
TRHnode* TRHgetTopOfTree(TRHtree* tree);
TRHnode** TRHgetTopOfTreeAddr(TRHtree* tree);

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

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

int TRHfreeTree(TRHtree* tree);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/

int TRHaddWord(TRHtree* tree, char* word, int size, int value);
int TRHaddWordRecursive(TRHnode** node, char* word, int size, int value);
TRHnode* TRHaddWordBuildHypster(TRHnode *node, char* word, int size, int value);

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/

#endif
