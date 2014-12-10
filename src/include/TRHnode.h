/**
 * ALGAV Project
 * BRDnode component Header
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @copyright (c) 2014, AFFES
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#ifndef __TRHNODE_H__
#define __TRHNODE_H__

extern int global_id = 0;

typedef struct _TRHnode {
  char content;
  int value;
  int id;
  struct _TRHnode *lowChild;
  struct _TRHnode *equalChild;
  struct _TRHnode *highChild;
} TRHnode;

/******************************************************************************
 * Fonctions de gestion de la structure TRHnode
 * ( ou primitives en langage STL ... )
 *****************************************************************************/

char TRHgetContent(TRHnode* node);
int TRHsetContent(TRHnode* node, char content);

int TRHgetValue(TRHnode* node);
int TRHsetValue(TRHnode* node, int value);

int TRHgetId(TRHnode* node);
int TRHsetId(TRHnode* node, int id);

TRHnode* TRHgetLowChild(TRHnode* node);
TRHnode** TRHgetLowChildAddr(TRHnode* node);

TRHnode* TRHgetEqualChild(TRHnode* node);
TRHnode** TRHgetEqualChildAddr(TRHnode* node);

TRHnode* TRHgetHighChild(TRHnode* node);
TRHnode** TRHgetHighChildAddr(TRHnode* node);

int TRHhasLowChild(TRHnode* node);
int TRHsetLowChild(TRHnode* node, TRHnode* lowChild);

int TRHhasEqualChild(TRHnode* node);
int TRHsetEqualChild(TRHnode* node, TRHnode* equalChild);

int TRHhasHighChild(TRHnode* node);
int TRHsetHighChild(TRHnode* node, TRHnode* highChild);

/******************************************************************************
 * Fonctions de tests sur la structure TRHnode
 *****************************************************************************/

int TRHisEmptyNode(TRHnode* node);
int TRHisEOWNode(TRHnode* node);
int TRHisEndOfTrie(TRHnode* node);

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/

TRHnode* TRHinitNodeWithContent(char content);
TRHnode* TRHinitNodeWithContentAndValue(char content, int value);

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

int TRHfreeNode(TRHnode* node);
int TRHfreeNodeRecursive(TRHnode* node);

#endif
