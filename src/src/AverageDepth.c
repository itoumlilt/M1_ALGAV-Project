/**
 * ALGAV Project
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#include <stdio.h>
#include <stdlib.h>

#include <AverageDepth.h>

/******************************************************************************
 * Getters / Setters
 *****************************************************************************/
int ADgetNbNodes(AverageDepth* ad)
{
  return ad->nbNodes;
}

void ADsetNbNodes(AverageDepth* ad, int nbNodes)
{
  ad->nbNodes = nbNodes;
}

int ADgetSumHeights(AverageDepth* ad)
{
  return ad->sumHeights;
}
void ADsetSumHeights(AverageDepth* ad, int sumHeights)
{
  ad->sumHeights = sumHeights;
}


/******************************************************************************
 * Traitement
 *****************************************************************************/
void ADincrementNbNodes(AverageDepth* ad)
{
  ADsetNbNodes(ad, ADgetNbNodes(ad) + 1);
}

void ADaddHeight(AverageDepth* ad, int height)
{
  ADsetSumHeights(ad, ADgetSumHeights(ad) + height);
}

/******************************************************************************
 * Calcul
 *****************************************************************************/
int ADcount(AverageDepth* ad)
{
  return (ADgetSumHeights(ad)/ADgetNbNodes(ad));
}

/******************************************************************************
 * Init
 *****************************************************************************/
AverageDepth* ADinit()
{
  AverageDepth* ad = (AverageDepth*)malloc(sizeof(AverageDepth));

  ADsetNbNodes(ad, 0);
  ADsetSumHeights(ad, 0);

  return ad;
}

/******************************************************************************
 * Free
 *****************************************************************************/
void ADfree(AverageDepth* ad)
{
  free(ad);
}
