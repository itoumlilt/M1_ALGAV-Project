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

#ifndef __BRDTREE_H__
#define __BRDTREE_H__

#include <BRDnode.h>

/* Structure d'un composant BRDtree
 * BRDtree = Arbre Brandais
 * Contient simplement un pointeur vers le sommet de l'arbre
 */
typedef struct _BRDtree {
  BRDnode* topOfTree; /* Sommet de l'arbre */
} BRDtree;

/******************************************************************************
 * Fonctions de gestion de la structure BRDtree
 * ( ou primitives en langage STL ... )
 *****************************************************************************/
void BRDsetTopOfTree(BRDtree* tree, BRDnode* node);
BRDnode* BRDgetTopOfTree(BRDtree* tree);
BRDnode** BRDgetTopOfTreeAddr(BRDtree* tree);

/******************************************************************************
 * Fonctions de check
 *****************************************************************************/
int BRDisTopOfTree(BRDtree* tree, BRDnode* node);

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/
BRDtree* BRDinitTreeWithNode(BRDnode* node);
BRDtree* BRDinitEmptyTree();

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/
void BRDfreeTree(BRDtree* tree);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
int BRDaddWord(BRDtree* tree, char* word, int size);

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/
BRDnode* BRDsearchNodeWithValueInLevel(BRDnode* firstChild, char c);

#endif
