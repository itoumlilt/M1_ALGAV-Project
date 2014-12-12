/**
 * ALGAV Project
 * TRHnode component header
 *
 * Amin's version edited by toumlilt
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com> ( v2.0 )
 *
 * @copyright (c) 2014, toumlilt
 *
 * @version 2.0
 * @package toumlilt/M1/ALGAV
 */

#ifndef __TRHNODE_H__
#define __TRHNODE_H__

extern int global_id;

typedef struct _TRHnode {
  char content; /* caractère représenté par le noeud */
  int keyValue; /* non vide ( != -1 ) lorsque le noeud est une clé */
  int id; /* unique par noeud, pour la représentation graphique */
  struct _TRHnode *lowChild;
  struct _TRHnode *equalChild;
  struct _TRHnode *highChild;
} TRHnode;

/******************************************************************************
 * Getters / Setters ( primitives )
 *****************************************************************************/
char TRHgetContent(TRHnode* node);
void TRHsetContent(TRHnode* node, char content);

int TRHgetKeyValue(TRHnode* node);
void TRHsetKeyValue(TRHnode* node, int keyValue);

int TRHgetId(TRHnode* node);
void TRHsetId(TRHnode* node);

TRHnode* TRHgetLowChild(TRHnode* node);
TRHnode** TRHgetLowChildAddr(TRHnode* node);
void TRHsetLowChild(TRHnode* node, TRHnode* lowChild);

TRHnode* TRHgetEqualChild(TRHnode* node);
TRHnode** TRHgetEqualChildAddr(TRHnode* node);
void TRHsetEqualChild(TRHnode* node, TRHnode* equalChild);

TRHnode* TRHgetHighChild(TRHnode* node);
TRHnode** TRHgetHighChildAddr(TRHnode* node);
void TRHsetHighChild(TRHnode* node, TRHnode* highChild);

/******************************************************************************
 * Fonctions de tests, checkers
 *****************************************************************************/
int TRHisEmptyNode(TRHnode* node);
int TRHisEOWNode(TRHnode* node); /* EOW = End Of Word */
int TRHisEndOfTree(TRHnode* node);

int TRHhasLowChild(TRHnode* node);
int TRHhasEqualChild(TRHnode* node);
int TRHhasHighChild(TRHnode* node);

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/
TRHnode* TRHinitNodeWithContent(char content);
TRHnode* TRHinitNodeWithContentAndKeyValue(char content, int keyValue);

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

int TRHfreeNode(TRHnode* node);
int TRHfreeNodeRecursive(TRHnode* node);

#endif
