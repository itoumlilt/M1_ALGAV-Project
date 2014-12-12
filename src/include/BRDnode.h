/**
 * ALGAV Project
 * BRDnode component Header
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */


#ifndef __BRDNODE_H__
#define __BRDNODE_H__

/* Structure d'un noeud Brandais
 * Contient le char du noeud
 * Un pointeur vers le fils
 * Un pointeur vers le noeud suivant
 */
typedef struct _BRDnode {
  char content;                /* contenu du noeud */
  struct _BRDnode* firstChild;  /* branche vers fils */
  struct _BRDnode* nextSibling; /* branche vers le frère */ 
} BRDnode;

/******************************************************************************
 * Fonctions de gestion de la structure BRDnode ( primitives )
 *****************************************************************************/
char BRDgetContent(BRDnode* node);
void BRDsetContent(BRDnode* node, char content);

BRDnode* BRDgetFirstChild(BRDnode* node);
BRDnode** BRDgetFirstChildAddr(BRDnode* node);
int BRDhasFirstChild(BRDnode* node);
void BRDsetFirstChild(BRDnode* node, BRDnode* firstChild);

BRDnode* BRDgetNextSibling(BRDnode* node);
int BRDhasNextSibling(BRDnode* node);
void BRDsetNextSibling(BRDnode* node, BRDnode* nextSibling);

/******************************************************************************
 * Fonctions de tests sur la structure BRDnode
 *****************************************************************************/
int BRDisEmptyNode(BRDnode* node);
int BRDisEOWNode(BRDnode* node);
int BRDisEmptyNextSibling(BRDnode* node);
int BRDisEmptyFirstChild(BRDnode* node);
int BRDisFirstChildOf(BRDnode* node, BRDnode* child);

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/
BRDnode* BRDinitNodeWithValue(char value);
BRDnode* BRDinitEmptyNode();

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/
void BRDfreeNode(BRDnode* node);
void BRDfreeNodeRecursive(BRDnode* node);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
BRDnode* BRDinsertCharInNodeLevel(BRDnode** firstChild, char c);
BRDnode* BRDinsertNodeBetweenNodes(BRDnode* node,
				   BRDnode* leftSibling,
				   BRDnode* rightSibling);
int BRDremoveChildFromNode(BRDnode* node, BRDnode* child);

#endif
