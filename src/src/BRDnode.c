/**
 * ALGAV Project
 * BRDnode component implementation
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#include <stdio.h>
#include <stdlib.h>

#include <BRDerrno.h>
#include <BRDnode.h>
#include <libASCII.h>

/******************************************************************************
 * Fonctions de gestion de la structure BRDnode ( primitives )
 *****************************************************************************/

/* BRDnode's content */

/**
 * BRDnode's content getter
 * @param node
 * @return char content's value
 */
char BRDgetContent(BRDnode* node)
{
  return node->content;
}

/**
 * BRDnode's content setter
 * @param node
 * @param content 
 */
void BRDsetContent(BRDnode* node, char content)
{
  if( content < (char)ASCII_MIN || content >= (char)ASCII_MAX ){
    fprintf(stderr, "Error : BRDnode : BRDsetContent NULL pointer\n");
    return; /* @TODO clean exit flag */
  }
  
  node->content = content;
}

/* BRDnode's firstChild */

/**
 * BRDnode's firstChild getter
 * @param node
 * @return BRDnode* node's first child
 */
BRDnode* BRDgetFirstChild(BRDnode* node)
{
  return node->firstChild;
}

BRDnode** BRDgetFirstChildAddr(BRDnode* node)
{
  return &(node->firstChild);
}

/**
 * Check if a BRDnode has a firstChild
 * @param node
 * @return 1 if node has a child, 0 else.
 */
int BRDhasFirstChild(BRDnode* node)
{
  if( BRDgetFirstChild(node) )
    return 1;
  return 0;
}

/**
 * BRDnode's firstChild setter
 * @param node
 * @param firstChild
 */
void BRDsetFirstChild(BRDnode* node, BRDnode* firstChild)
{
  node->firstChild = firstChild;
}

/* BRDnode's nextSibling */

/**
 * Getter du frère.
 * @param node
 * @return BRDnode* Le frère du noeud en param, NULL si pas de frère.
 */
BRDnode* BRDgetNextSibling(BRDnode* node)
{
  return node->nextSibling;
}

/**
 * A-t-il un frère ?
 * @param node
 * @return int 1 s'il a un frère, 0 sinon.
 */
int BRDhasNextSibling(BRDnode* node)
{
  if( BRDgetNextSibling(node) )
    return 1;
  return 0;
}

/**
 * BRDnode's nextSibling setter
 * @param node
 * @param nextSibling
 */
void BRDsetNextSibling(BRDnode* node, BRDnode* nextSibling)
{
  node->nextSibling = nextSibling;
}

/******************************************************************************
 * Fonctions de tests sur la structure BRDnode
 *****************************************************************************/

/**
 * BRDnode's checker
 * @param node
 * @return int 1 si le noeud est vide, 0 sinon.
 */
int BRDisEmptyNode(BRDnode* node)
{
  if( BRDgetContent(node) == (char)ASCII_EOW )
    return 1;
  return 0;
}

/**
 * BRDnode's checker
 * @param node
 * @return int 1 si le noeud est vide, 0 sinon.
 */
int BRDisEOWNode(BRDnode* node)
{
  if( BRDgetContent(node) == (char)ASCII_EOW )
    return 1;
  return 0;
}

int BRDisEmptyNextSibling(BRDnode* node)
{
  if( BRDgetNextSibling(node) )
    return 0;
  return 1;
}

int BRDisEmptyFirstChild(BRDnode* node)
{
  if( BRDgetFirstChild(node) )
    return 0;
  return 1;
}


int BRDisFirstChildOf(BRDnode* node, BRDnode* child)
{
  if( BRDgetFirstChild(node) == child )
    return 1;
  return 0;
}

/******************************************************************************
 * Fonctions d'initialisation
 *****************************************************************************/

/* @TODO comme c'est le même à chaque fois et qu'on a pas besoin de faire de traitement dessus on pourrait allouer un seul BRDemptyNode et l'utiliser partout, à méditer */

/**
 * BRDnode's alloc
 * @param value content of the new BRDnode
 * @return BRDnode* le nouveau noeud créé
 */
BRDnode* BRDinitNodeWithValue(char value)
{
  if( value < (char)ASCII_MIN || value >= (char)ASCII_MAX ){
    fprintf(stderr, "value de merde : %c %d", value, value);
    perror("Error BRDNode : in BRDinitNodeWithValue :value out of bounds\n");
    /* @TODO clean exit flag */
    exit(1);
  }

  BRDnode* node = (BRDnode*)malloc(sizeof(BRDnode));

  BRDsetContent(node, value);
  BRDsetFirstChild(node, NULL);
  BRDsetNextSibling(node, NULL);

  return node;
}

/**
 * BRDnode's alloc
 * @return BRDnode* un noeud end of word vide.
 */
BRDnode* BRDinitEmptyNode()
{
  return BRDinitNodeWithValue(ASCII_EOW);
}

/******************************************************************************
 * Fonctions de free memory
 *****************************************************************************/

/* @TODO est-ce que je mets les free récursifs ici ? ou je fais l'abstraction au niveau des BRDtree ? hmmm */

/**
 * BRDnode's free.
 * Libère l'espace alloué à un noeud.
 * @param node
 */
void BRDfreeNode(BRDnode* node)
{
  free(node);
}

/* @TODO for the moment this is still a private API function */
void BRDfreeNodeRecursive(BRDnode* node)
{
  if( BRDhasNextSibling(node)){
    BRDfreeNodeRecursive(BRDgetNextSibling(node));
    BRDsetNextSibling(node, NULL);
  }
  if( BRDhasFirstChild(node) ){
    BRDfreeNodeRecursive(BRDgetFirstChild(node));
  }
  BRDfreeNode(node);
}

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/

/**
 * Char insertion on a node's level
 * @todo fonction optimisable, largement.
 * @param firstChild adresse du premier fils du niveau, modifié s'il le faut
 * ( modifié en cas d'insertion en début du niveau ... )
 * @param c the char to insert
 * @param the inserted node
 */
BRDnode* BRDinsertCharInNodeLevel(BRDnode** firstChild, char c)
{
  BRDnode* previousNode = NULL;
  BRDnode* insNode = *firstChild;

  /* if firstChild */
  if( BRDgetContent(insNode) > c){
    insNode = BRDinsertNodeBetweenNodes(BRDinitNodeWithValue(c),
					NULL,
					insNode);
    *firstChild = insNode;
    return insNode;
  }

  do{
    if( BRDgetContent(insNode) == c){
      return insNode;
    }
  
    if( BRDgetContent(insNode) > c)
      return BRDinsertNodeBetweenNodes(BRDinitNodeWithValue(c),
				       previousNode,
				       insNode);
  
    previousNode = insNode;
    insNode = BRDgetNextSibling(insNode);
  } while( !BRDisEmptyNextSibling(previousNode) );

  return BRDinsertNodeBetweenNodes(BRDinitNodeWithValue(c),
				   previousNode,
				   NULL);
}

/**
 * Node insertion in siblings
 * ListHead insert : leftSibling is NULL
 * ListQueue insert : rightSibling is NULL 
 * @param node the node to insert
 * @param leftSibling 
 * @param rightSibling 
 * @return the new inserted node
 */
BRDnode* BRDinsertNodeBetweenNodes(BRDnode* node,
				   BRDnode* leftSibling,
				   BRDnode* rightSibling)
{   
  if( leftSibling )
    BRDsetNextSibling(leftSibling, node);
  BRDsetNextSibling(node, rightSibling);

  return node;
}

/**
 *
 * @return -1 en cas d'erreur, 0 si tout s'est bien passé
 */
int BRDremoveChildFromNode(BRDnode* node, BRDnode* child)
{
  BRDnode* previous = BRDgetFirstChild(node);

  if( previous == child ){
    BRDsetFirstChild(node, BRDgetNextSibling(child));
    BRDfreeNode(child);
    return 0;
  }

  while( BRDgetNextSibling(previous) != child ){
    if( !previous )
      return -1;
    previous = BRDgetNextSibling(previous);
  }

  BRDsetNextSibling(previous, BRDgetNextSibling(child));
  if( BRDhasFirstChild(child) )
    BRDfreeNodeRecursive(BRDgetFirstChild(child));
  BRDfreeNode(child);

  return 0;
}
