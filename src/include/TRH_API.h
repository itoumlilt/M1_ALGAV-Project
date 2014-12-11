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

#include <TRHtree.h>
#include <BRDtree.h>
#include <ListWord.h>

#define TRH_API_LVL 1

int init_api();

/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/
TRHtree* TRHinitTreeFromFile(char* file);
ListWord* TRHgetListWordFromTree(TRHtree* tree);

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/
int TRHsearchWord(TRHtree* tree, char* word, int size);

/******************************************************************************
 * Fonctions de calcul
 *****************************************************************************/
int TRHcountTreeWords(TRHtree* tree);
int TRHcountTreeNullNodes(TRHtree* tree);
int TRHcountTreeHeight(TRHtree* tree);
int TRHcountAverageDepth(TRHtree* tree);
int TRHcountTreePrefixeOccurrence(TRHtree* tree, char* word, int size);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
int TRHremoveWordFromTree(TRHtree* tree, char* word, int size);

/* Fonction de passage d'un tie Hybride a un arbre de la Briandais */
BRDtree* TRHtoBriandaisFromTree(TRHtree *tree);
