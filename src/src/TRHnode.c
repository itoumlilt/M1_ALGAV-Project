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

/* init */
int global_id = 0;

/******************************************************************************
 * Fonctions de gestion de la structure TRHnode
 * ( ou primitives en langage STL ... )
 *****************************************************************************/

/**
 * TRHnode's content getter
 * @param node
 * @return char content's value
 */
char TRHgetContent(TRHnode* node)
{
  return node->content;
}


/**
 * TRHnode's content setter
 * @param node
 * @param content
 */
int TRHsetContent(TRHnode* node, char content)
{
  node->content = content;
  return 0;
}


/**
 * TRHnode's value getter
 * @param node
 * @return int value's value
 */
int TRHgetValue(TRHnode* node)
{
  return node->value;
}


/**
 * TRHnode's value setter
 * @param node
 * @param value
 */
int TRHsetValue(TRHnode* node, int value)
{
  node->value = value;
  return 0;
}


/**
 * TRHnode's id getter
 * @param node
 * @return int id's global_id
 */
int TRHgetId(TRHnode* node)
{
  return node->id;
}


/**
 * TRHnode's value setter
 * @param node
 * @param int id's value
 */
int TRHsetId(TRHnode* node, int id)
{
  node->id = id;
  return 0;
}


/**
 * TRHnode's lowChild getter
 * @param node
 * @return TRHnode* node's low child
 */
TRHnode* TRHgetLowChild(TRHnode* node)
{
  return node->lowChild;
}


TRHnode** TRHgetLowChildAddr(TRHnode* node)
{
  return &(node->lowChild);
}


/**
 * TRHnode's equalChild getter
 * @param node
 * @return TRHnode* node's equal child
 */
TRHnode* TRHgetEqualChild(TRHnode* node)
{
  return node ->equalChild;
}


TRHnode** TRHgetEqualChildAddr(TRHnode* node)
{
  return &(node->equalChild);
}


/**
 * TRHnode's highChild getter
 * @param node
 * @return TRHnode* node's high child
 */
TRHnode* TRHgetHighChild(TRHnode* node)
{
  return node ->highChild;
}


TRHnode** TRHgetHighChildAddr(TRHnode* node)
{
  return &(node->highChild);
}


/**
 * Check if a TRHnode has a lowChild
 * @param node
 * @return 1 if node has a low child, 0 else.
 */
int TRHhasLowChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetLowChild(node)))
    return 1;
  return 0;
}


/**
 * TRHnode's lowChild setter
 * @param node
 * @param lowChild
 */
int TRHsetLowChild(TRHnode* node, TRHnode* lowChild)
{
  TRHsetLowChild(node,lowChild);
  return 0;
}


/**
 * Check if a TRHnode has a equalChild
 * @param node
 * @return 1 if node has a equal child, 0 else.
 */
int TRHhasEqualChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetEqualChild(node)))
    return 1;
  return 0;
}


/**
 * TRHnode's equalChild setter
 * @param node
 * @param equalChild
 */
int TRHsetEqualChild(TRHnode* node, TRHnode* equalChild)
{
  TRHsetEqualChild(node,equalChild);
  return 0;
}


/**
 * Check if a TRHnode has a highChild
 * @param node
 * @return 1 if node has a high child, 0 else.
 */
int TRHhasHighChild(TRHnode* node)
{
  if(!TRHisEmptyNode(TRHgetHighChild(node)))
    return 1;
  return 0;
}


/**
 * TRHnode's highChild setter
 * @param node
 * @param highChild
 */
int TRHsetHighChild(TRHnode* node, TRHnode* highChild)
{
  TRHsetHighChild(node,highChild);;
  return 0;
}


/******************************************************************************
 * Fonctions de tests sur la structure TRHnode
 *****************************************************************************/


/**
 * TRHnode's checker
 * @param node
 * @return int 1 si le noeud est vide, 0 sinon.
 */
int TRHisEmptyNode(TRHnode* node)
{
  if(node == NULL)
    return 1;
  return 0;
}


/**
 * TRHEndOfWord's checker
 * @param node
 * @return int 1 si le noeud est la fin d'un mot, 0 sinon.
 */
int TRHisEOWNode(TRHnode* node)
{
  if(TRHgetValue(node) != -1)
    return 1;
  return 0;
}


/**
 * TRHnode's checker
 * @param node
 * @return int 1 si le noeud est une feuille, 0 sinon.
 */
int TRHisEndOfTrie(TRHnode* node)
{
  if(!TRHhasLowChild(node) && !TRHhasEqualChild(node) && !TRHhasHighChild(node))
    return 1;
  return 0;
}


/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/


/**
 * TRHnode's alloc
 * @param value content of the new TRHnode
 * @return TRHnode* le nouveau noeud créé
 */
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


/**
 * TRHnode's alloc
 * @param value content of the new TRHnode
 * @param value value of the new TRHnode
 * @return TRHnode* le nouveau noeud créé
 */
TRHnode* TRHinitNodeWithContentAndValue(char content, int value)
{
  TRHnode* node = TRHinitNodeWithContent(content);
  TRHsetValue(node,value);
  return node;
}


/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/


/**
 * TRHnode's free.
 * Libère l'espace alloué à un noeud.
 * @param node
 */
int TRHfreeNode(TRHnode* node)
{
  free(node);
  return 0;
}


/**
 * TRHnode's recursive free.
 * @param node adresse du noeud a partir duquel on veux commencer le parcours
 */
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
