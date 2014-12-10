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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <TRHnode.h>


/******************************************************************************
 * Fonctions de gestion de la structure TRHnode
 * ( ou primitives en langage STL ... )
 *****************************************************************************/


char TRHgetContent(TRHnode* node)
{
  return node->content;
}


int TRHsetContent(TRHnode* node, char content)
{
  node->content = content;
  return 0;
}


int TRHgetValue(TRHnode* node)
{
  return node->value;
}


int TRHsetValue(TRHnode* node, int value)
{
  node->value = value;
  return 0;
}


int TRHgetId(TRHnode* node)
{
  return node->id;
}


int TRHsetId(TRHnode* node, int id)
{
  node->id = id;
  return 0;
}


TRHnode* TRHgetLowChild(TRHnode* node)
{
  return node->lowChild;
}


TRHnode** TRHgetLowChildAddr(TRHnode* node)
{
  return &(node->lowChild);
}


TRHnode* TRHgetEqualChild(TRHnode* node)
{
  return node ->equalChild;
}


TRHnode** TRHgetEqualChildAddr(TRHnode* node)
{
  return &(node->equalChild);
}

TRHnode* TRHgetHighChild(TRHnode* node)
{
  return node ->highChild;
}


TRHnode** TRHgetHighChildAddr(TRHnode* node)
{
  return &(node->highChild);
}


int TRHhasLowChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetLowChild(node)))
    return 1;
  return 0;
}


int TRHsetLowChild(TRHnode* node, TRHnode* lowChild)
{
  TRHsetLowChild(node,lowChild);
  return 0;
}


int TRHhasEqualChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetEqualChild(node)))
    return 1;
  return 0;
}


int TRHsetEqualChild(TRHnode* node, TRHnode* equalChild)
{
  TRHsetEqualChild(node,equalChild);
  return 0;
}


int TRHhasHighChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetHighChild(node)))
    return 1;
  return 0;
}


int TRHsetHighChild(TRHnode* node, TRHnode* highChild)
{
  TRHsetHighChild(node,highChild);;
  return 0;
}


/******************************************************************************
 * Fonctions de tests sur la structure TRHnode
 *****************************************************************************/


int TRHisEmptyNode(TRHnode* node)
{
  if(node == NULL)
    return 1;
  return 0;
}


int TRHisEOWNode(TRHnode* node)
{
  if(TRHgetValue(node) != -1)
    return 1;
  return 0;
}


int TRHisEndOfTrie(TRHnode* node)
{
  if(!TRHhasLowChild(node) && !TRHhasEqualChild(node) && !TRHhasHighChild(node))
    return 1;
  return 0;
}


/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/


TRHnode* TRHinitNodeWithContent(char content)
{
  TRHnode* node = (TRHnode*) malloc(sizeof(TRHnode));

  TRHsetContent(node,content);
  TRHsetValue(node,-1);
  TRHsetId(node,global_id);

  TRHsetLowChild(node,NULL);
  TRHsetEqualChild(node,NULL);
  TRHsetHighChild(node,NULL);

  global_id++;

  return node;
}


TRHnode* TRHinitNodeWithContentAndValue(char content, int value)
{
  TRHnode* node = TRHinitNodeWithContent(content);
  TRHsetValue(node,value);
  return node;
}


/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/


int TRHfreeNode(TRHnode* node)
{
  free(node);
  return 0;
}


/* Je te laisse verifier au cas ou y'a une meilleur façon de faire ça */

int TRHfreeNodeRecursive(TRHnode* node)
{
  if(TRHisEndOfTrie(node))
    return TRHfreeNode(node);

  if( TRHfreeNodeRecursive(TRHgetLowChild(node)) != -1
      && TRHfreeNodeRecursive(TRHgetEqualChild(node)) != -1
      && TRHfreeNodeRecursive(TRHgetHighChild(node)) != -1)
    return TRHfreeNode(node);

  return -1;
}
