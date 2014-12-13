/**
 * ALGAV Project
 * TRHnode component implementation
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

#include <stdlib.h>
#include <stdio.h>

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
void TRHsetContent(TRHnode* node, char content)
{
  node->content = content;
}


/**
 * TRHnode's value getter
 * @param node
 * @return int value's value
 */
int TRHgetKeyValue(TRHnode* node)
{
  return node->keyValue;
}


/**
 * TRHnode's value setter
 * @param node
 * @param value
 */
void TRHsetKeyValue(TRHnode* node, int keyValue)
{
  node->keyValue = keyValue;
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

void TRHsetId(TRHnode* node)
{
  node->id = global_id;
  global_id++;
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
 * TRHnode's lowChild setter
 * @param node
 * @param lowChild
 */
void TRHsetLowChild(TRHnode* node, TRHnode* lowChild)
{
  node->lowChild = lowChild;
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
 * TRHnode's equalChild setter
 * @param node
 * @param equalChild
 */
void TRHsetEqualChild(TRHnode* node, TRHnode* equalChild)
{
  node->equalChild = equalChild;
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
 * TRHnode's highChild setter
 * @param node
 * @param highChild
 */
void TRHsetHighChild(TRHnode* node, TRHnode* highChild)
{
  node->highChild = highChild;
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
  if(node)
    return 0;
  return 1;
}


/**
 * TRHEndOfWord's checker
 * @param node
 * @return int 1 si le noeud est la fin d'un mot, 0 sinon.
 */
int TRHisEOWNode(TRHnode* node)
{
  if(TRHgetKeyValue(node) != -1)
    return 1;
  return 0;
}


/**
 * TRHnode's checker
 * @param node
 * @return int 1 si le noeud est une feuille, 0 sinon.
 */
int TRHisEndOfTree(TRHnode* node)
{
  if(!TRHhasLowChild(node) && !TRHhasEqualChild(node) && !TRHhasHighChild(node))
    return 1;
  return 0;
}

/**
 * Check if a TRHnode has a lowChild
 * @param node
 * @return 1 if node has a low child, 0 else.
 */
int TRHhasLowChild(TRHnode* node)
{
  if(TRHisEmptyNode(TRHgetLowChild(node)))
    return 0;
  return 1;
}

/**
 * Check if a TRHnode has a equalChild
 * @param node
 * @return 1 if node has a equal child, 0 else.
 */
int TRHhasEqualChild(TRHnode* node)
{
  if(TRHisEmptyNode(TRHgetEqualChild(node)))
    return 0;
  return 1;
}

/**
 * Check if a TRHnode has a highChild
 * @param node
 * @return 1 if node has a high child, 0 else.
 */
int TRHhasHighChild(TRHnode* node)
{
  if(TRHisEmptyNode(TRHgetHighChild(node)))
    return 0;
  return 1;
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
  return TRHinitNodeWithContentAndKeyValue(content, -1);
}


/**
 * TRHnode's alloc
 * @param content of the new TRHnode
 * @param value of the new TRHnode
 * @return TRHnode* le nouveau noeud créé
 */
TRHnode* TRHinitNodeWithContentAndKeyValue(char content, int keyValue)
{
  TRHnode* node = (TRHnode*)malloc(sizeof(TRHnode));

  TRHsetContent(node, content);
  TRHsetKeyValue(node, keyValue);
  TRHsetId(node);
  TRHsetLowChild(node,NULL);
  TRHsetEqualChild(node,NULL);
  TRHsetHighChild(node,NULL);

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
void TRHfreeNode(TRHnode* node)
{
  free(node);
}


/**
 * TRHnode's recursive free.
 * @param node adresse du noeud a partir duquel on veux commencer le parcours
 */
void TRHfreeNodeRecursive(TRHnode* node)
{
  if( TRHhasLowChild(node) )
    TRHfreeNodeRecursive(TRHgetLowChild(node));

  if( TRHhasEqualChild(node) )
    TRHfreeNodeRecursive(TRHgetEqualChild(node));

  if( TRHhasHighChild(node) )
    TRHfreeNodeRecursive(TRHgetHighChild(node));

  TRHfreeNode(node);
}
