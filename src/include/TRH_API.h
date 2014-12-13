/**
 * ALGAV Project
 * TRH_API public header
 *
 * @author Mohamed Amin AFFES <mohamed.af@hotmail.fr>
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com> ( v2.0 )
 *
 * @copyright (c) 2014, toumlilt
 *
 * @version 2.0
 * @package toumlilt/M1/ALGAV
 */

#include <libASCII.h>
#include <TRHtree.h>

/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/
TRHtree* TRHinitTreeFromFile(char* filename);

/******************************************************************************
 * Fonctions de search :
 *****************************************************************************/
int TRHsearchWord(TRHtree* tree, char* word, int size);
int TRHcountWords(TRHtree* tree);
int TRHcountNil(TRHtree* tree);

/******************************************************************************
 * Fonctions de libération de mémoire :
 *****************************************************************************/
void TRHfree(TRHtree* tree);
