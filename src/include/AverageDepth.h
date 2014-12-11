/**
 * ALGAV Project
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#ifndef __AVERAGEDEPTH_H__
#define __AVERAGEDEPTH_H__

typedef struct _AverageDepth {
  int nbNodes;
  int sumHeights;
} AverageDepth;

/******************************************************************************
 * Getters / Setters
 *****************************************************************************/
int ADgetNbNodes(AverageDepth* ad);
void ADsetNbNodes(AverageDepth* ad, int nbNodes);

int ADgetSumHeights(AverageDepth* ad);
void ADsetSumHeights(AverageDepth* ad, int sumHeights);

/******************************************************************************
 * Traitement
 *****************************************************************************/
void ADincrementNbNodes(AverageDepth* ad);
void ADaddHeight(AverageDepth* ad, int height);

/******************************************************************************
 * Calcul
 *****************************************************************************/
int ADcount(AverageDepth* ad);

/******************************************************************************
 * Init
 *****************************************************************************/
AverageDepth* ADinit();

/******************************************************************************
 * Free
 *****************************************************************************/
void ADfree(AverageDepth* ad);

#endif
