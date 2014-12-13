/**
 * ALGAV Project - Brandais API
 * The controler
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */
/* @TODO refaire les headers parties BRD */

#ifndef __BRD_API_H__
#define __BRD_API_H__

#include <libASCII.h>
#include <BRDerrno.h>
#include <BRDnode.h>
#include <BRDtree.h>
#include <ListWord.h>
#include <AverageDepth.h>

/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/
BRDtree* BRDinitTreeFromFile(char* file);
BRDtree* BRDinitTreeFromShakespeareFiles();
BRDtree* BRDmergeTwoTrees(BRDtree* tree1, BRDtree* tree2);

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/
int BRDsearchWord(BRDtree* tree, char* word, int size);
ListWord* BRDgetListWordFromTree(BRDtree* tree);

/******************************************************************************
 * Fonctions de calcul
 *****************************************************************************/
int BRDcountTreeWords(BRDtree* tree);
int BRDcountTreeNullNodes(BRDtree* tree);
int BRDcountTreeHeight(BRDtree* tree);
int BRDcountAverageDepth(BRDtree* tree);
int BRDcountTreePrefixeOccurrence(BRDtree* tree, char* word, int size);

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
int BRDremoveWordFromTree(BRDtree* tree, char* word, int size);

/******************************************************************************
 * Fonctions de free memory :
 *****************************************************************************/

#endif
