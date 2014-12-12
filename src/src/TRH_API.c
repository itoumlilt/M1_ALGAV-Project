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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libASCII.h>

#include <TRH_API.h>

/* Declaration des fonctions privee */

ListWord* TRHinitListWordFromNode(TRHnode* node);
void TRHinitListWordFromNodeRecursive(TRHnode* node,  ListWord** listeM, char* word, int size);
int TRHsearchWordFromNode(TRHnode* node, char* word, int size);
int TRHcountTreeWordsFromNode(TRHnode* node);
int TRHcountTreeNullNodesFromNode(TRHnode* node);
int TRHcountTreeNullNodesFromNode(TRHnode* node);
int TRHcountTreeHeightFromNode(TRHnode* node);
int TRHcountAverageDepthFromNode(TRHnode* node);
void TRHcountAverageDepthFromNodeRecursive(TRHnode* node, int* cmp, int* somme, int profondeur);
int TRHcountTreePrefixeOccurrenceFromNode(TRHnode* node, char* word, int size);
int TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHnode* node, char* word, int size);
int TRHremoveWordFromNode(TRHnode* node, char* word, int size);
TRHnode* TRHremoveWordFromNodeRecursive(TRHnode* node, char* word, int size);
/* Inserer les mots de th2 dans th1 */
void TRH_Fusion(TRHnode** node1, TRHnode* node2, char* word);
BRDtree* TRHtoBriandaisFromNode(TRHnode *node);
void TRHtoBriandaisFromNodeRecursive(TRHnode *node, BRDnode** brnode);

/**************************************************************************************/

int init_api()
{
  return 0;
}

char *strdup(const char *str){
  int n = strlen(str) + 1;
  char *dup = malloc(n);
  if(dup)
    {
      strcpy(dup, str);
    }
  return dup;
}

/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/

TRHtree* TRHinitTreeFromFile(char* file)
{
  /* ouverture du fichier */
  int fd, v=0;
  if( (fd = open(file, O_RDONLY)) == -1){
    fprintf(stderr, "Error: BRD_API: __LINE__\n");
    /* @TODO clean exit */
    exit(1);
  }

  /* init */
  TRHtree* tree = TRHinitEmptyTree();
  char lu;
  char word[WORD_MAX_SIZE];
  memset(word, '\0', WORD_MAX_SIZE);
  int i=0;
  int nbWords=0;

  /* read and construct */
  while( read(fd, &lu, 1) ){
    if(isSeparator(lu)){
      word[i] = '\0';
      if(i){
        TRHaddWord(tree, word, strlen(word), v); /* @TODO sera fait par un autre thread */
        v++;
	nbWords++;
      }
      i=0;
    } else {
      word[i] = lu;
      i++;
    }
  }
  /* on rajoute le dernier mot s'il faut */
  if(i){
    word[i] = '\0';
    TRHaddWord(tree, word, strlen(word), v);
    v++;
    nbWords++;
  }

  /* fermeture du fichier */
  close(fd);

  return tree;
}


ListWord* TRHgetListWordFromTree(TRHtree* tree)
{
  if(TRHisEmptyTree(tree))
    return NULL;

  return TRHinitListWordFromNode(TRHgetTopOfTree(tree));
}


ListWord* TRHinitListWordFromNode(TRHnode* node)
{
  ListWord **listeM = NULL;

  if(TRHisEmptyNode(node))
    return NULL;

  listeM = (ListWord**) malloc(TRHcountTreeWordsFromNode(node) * sizeof(ListWord*));
  TRHinitListWordFromNodeRecursive(node, listeM, NULL, 0);
  return *listeM;
}


void TRHinitListWordFromNodeRecursive(TRHnode* node,  ListWord** listeM, char* word, int size)
{
  char *m1 = NULL, *m2 = NULL, *m3 = NULL, *m4 = NULL;

  if(!TRHisEmptyNode(node)){
    if(word == NULL){
      word = (char*) malloc(sizeof(char));
      *word = TRHgetContent(node);
      m1 = strdup(word);

      if( TRHgetValue(node) != -1 ) /* ajout du mot */
        *listeM = LWinitWithWord(word, size);

      TRHinitListWordFromNodeRecursive(TRHgetLowChild(node), listeM, NULL , size);
      TRHinitListWordFromNodeRecursive(TRHgetEqualChild(node), listeM, m1 , size+1);
      TRHinitListWordFromNodeRecursive(TRHgetHighChild(node), listeM, NULL , size);

      /* free(m1); */
    }
    else {
      /* m1 chaine contenant la chaine mot + le caractere du noeud courant */

      m1 = strdup(word);
      m2 = strdup(word);
      m3 = strdup(word);

      /* on ajoute le caractere courant a m1 */
      m1 = realloc(word, (size + 1) * sizeof(char));
      m1[size] = TRHgetContent(node);

      m4 = strdup(m1);

      if( TRHgetValue(node) != -1 ) /* ajout du mot */
        LWsetNextWord(*listeM, LWinitWithWord(m1, size+1));

      TRHinitListWordFromNodeRecursive(TRHgetLowChild(node), listeM, m2 , size);
      TRHinitListWordFromNodeRecursive(TRHgetEqualChild(node), listeM, m4 , size+1);
      TRHinitListWordFromNodeRecursive(TRHgetHighChild(node), listeM, m3 , size);

      /*free(m1);
        free(m2);
        free(m3);
        free(m4);*/
    }
  }
}

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/

int TRHsearchWord(TRHtree* tree, char* word, int size)
{
  if(word != NULL && (!TRHisEmptyTree(tree)))
    return TRHsearchWordFromNode(TRHgetTopOfTree(tree), word, size);
  return 0;
}

int TRHsearchWordFromNode(TRHnode* node, char* word, int size)
{
  if (word != NULL && (!TRHisEmptyNode(node))) {
    if (size == 1 && TRHgetValue(node) != -1)
      return 1;
    else if (word[0] < TRHgetContent(node))
      return TRHsearchWordFromNode(TRHgetLowChild(node),word,size);
    else if (word[0] == TRHgetContent(node))
      return TRHsearchWordFromNode(TRHgetEqualChild(node),&word[1],size);
    else
      return TRHsearchWordFromNode(TRHgetHighChild(node),word,size);
  }
  return 0;
}


/******************************************************************************
 * Fonctions de calcul
 *****************************************************************************/

int TRHcountTreeWords(TRHtree* tree)
{
  if (TRHisEmptyTree(tree))
    return 0;

  return TRHcountTreeWordsFromNode(TRHgetTopOfTree(tree));
}

int TRHcountTreeWordsFromNode(TRHnode* node)
{
  if (TRHisEmptyNode(node))
    return 0;

  if (TRHgetValue(node) != -1)
    return ( 1 + TRHcountTreeWordsFromNode(TRHgetLowChild(node))
	     + TRHcountTreeWordsFromNode(TRHgetEqualChild(node))
	     + TRHcountTreeWordsFromNode(TRHgetHighChild(node))
	     );
  else
    return ( TRHcountTreeWordsFromNode(TRHgetLowChild(node)) +
	     TRHcountTreeWordsFromNode(TRHgetEqualChild(node)) +
	     TRHcountTreeWordsFromNode(TRHgetHighChild(node))
	     );
}


int TRHcountTreeNullNodes(TRHtree* tree)
{
  if(TRHisEmptyTree(tree))
    return 0;

  return TRHcountTreeNullNodesFromNode(TRHgetTopOfTree(tree));
}

int TRHcountTreeNullNodesFromNode(TRHnode* node)
{
  if(TRHisEmptyNode(node))
    return 1;

  return ( TRHcountTreeNullNodesFromNode(TRHgetLowChild(node)) +
           TRHcountTreeNullNodesFromNode(TRHgetEqualChild(node)) +
           TRHcountTreeNullNodesFromNode(TRHgetHighChild(node))
	   );
}


int TRHcountTreeHeight(TRHtree* tree)
{
  if(TRHisEmptyTree(tree))
    return 0;

  return TRHcountTreeHeightFromNode(TRHgetTopOfTree(tree));
}

int TRHcountTreeHeightFromNode(TRHnode* node)
{
  int i,e,s;

  if (TRHisEmptyNode(node) || TRHisEndOfTrie(node))
    return 0;

  i = TRHcountTreeHeightFromNode(TRHgetLowChild(node));
  e = TRHcountTreeHeightFromNode(TRHgetEqualChild(node));
  s = TRHcountTreeHeightFromNode(TRHgetHighChild(node));

  if (i > e && i > s)
    return (1 + i);
  else if (e > i && e > s)
    return (1 + e);
  else if (s > i && s > e)
    return (1 + s);
  else
    /* i = e = s */
    return (1 + i);
}


int TRHcountAverageDepth(TRHtree* tree)
{
  if(TRHisEmptyTree(tree))
    return 0;

  return TRHcountAverageDepthFromNode(TRHgetTopOfTree(tree));
}


int TRHcountAverageDepthFromNode(TRHnode* node)
{
  int cmp=0, somme=0;

  if (TRHisEmptyNode(node))
    return 0;
  if (TRHisEndOfTrie(node))
    return 1;

  TRHcountAverageDepthFromNodeRecursive(TRHgetLowChild(node), &cmp, &somme, 1);
  TRHcountAverageDepthFromNodeRecursive(TRHgetEqualChild(node), &cmp, &somme, 1);
  TRHcountAverageDepthFromNodeRecursive(TRHgetHighChild(node), &cmp, &somme, 1);

  return (somme/cmp);
}


void TRHcountAverageDepthFromNodeRecursive(TRHnode* node, int *cmp, int *somme, int profondeur)
{
  if (!TRHisEmptyNode(node)) {
    if (TRHisEndOfTrie(node)) {
      (*cmp)++;
      *somme += (++profondeur);
    }
    else {
      TRHcountAverageDepthFromNodeRecursive(TRHgetLowChild(node), cmp, somme, profondeur++);
      TRHcountAverageDepthFromNodeRecursive(TRHgetEqualChild(node), cmp, somme, profondeur++);
      TRHcountAverageDepthFromNodeRecursive(TRHgetHighChild(node), cmp, somme, profondeur++);
    }
  }
}


int TRHcountTreePrefixeOccurrence(TRHtree* tree, char* word, int size){
  if(TRHisEmptyTree(tree))
    return 0;

  return TRHcountTreePrefixeOccurrenceFromNode(TRHgetTopOfTree(tree),word,size);
}


int TRHcountTreePrefixeOccurrenceFromNode(TRHnode* node, char* word, int size)
{
  int nbPrefixes = 0;

  if(TRHisEmptyNode(node))
    return nbPrefixes;

  nbPrefixes += TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetLowChild(node), word, size);
  nbPrefixes += TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetEqualChild(node), word, size);
  nbPrefixes += TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetHighChild(node), word, size);

  return nbPrefixes;
}


int TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHnode* node, char* word, int size)
{
  if (word != NULL && (!TRHisEmptyNode(node))) {
    /* fin de chaine donc prefixe de tous les mots qui suivent */
    if (size == 1){
      if (TRHgetValue(node) == -1)
        return TRHcountTreeWordsFromNode(TRHgetEqualChild(node));
      else
        return (1 + TRHcountTreeWordsFromNode(TRHgetEqualChild(node)));
    }
    else {
      if (word[0] < TRHgetContent(node))
        return TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetLowChild(node), word, size);
      else if (word[0] == TRHgetContent(node))
        return TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetEqualChild(node), &word[1], size-1);
      else
        return TRHcountTreePrefixeOccurrenceFromNodeRecursive(TRHgetHighChild(node), word, size);
    }
  }

  return 0;
}


/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/

int TRHremoveWordFromTree(TRHtree* tree, char* word, int size)
{
  if(TRHisEmptyTree(tree))
    return 0;

  return TRHremoveWordFromNode(TRHgetTopOfTree(tree),word,size);
}


int TRHremoveWordFromNode(TRHnode* node, char* word, int size)
{
  if(TRHisEmptyNode(node))
    return 0;

  TRHremoveWordFromNodeRecursive(node, word, size);
  return 0;
}

TRHnode* TRHremoveWordFromNodeRecursive(TRHnode* node, char* word, int size)
{
  if (!TRHisEmptyNode(node)) {
    if (size == 1)
      TRHsetValue(node, -1);
    else {
      if (word[0] < TRHgetContent(node))
        TRHsetLowChild(node, TRHremoveWordFromNodeRecursive(TRHgetLowChild(node), word, size));
      else if (word[0] == TRHgetContent(node))
	TRHsetEqualChild(node, TRHremoveWordFromNodeRecursive(TRHgetEqualChild(node), &word[1], size-1));
      else
        TRHsetHighChild(node, TRHremoveWordFromNodeRecursive(TRHgetHighChild(node), word, size));
    }

    /* il faut reorganiser l'arbre */

    /* Le mot a supprimer est prefixe d'autres mots */
    if ((!TRHhasEqualChild(node)) || TRHgetValue(node) != -1)
      return node;

    /* Le noeud courant n'a pas de fils */
    if (TRHisEndOfTrie(node)){
      /*free(th);*/
      return NULL;
    }

    /* le fils equal du noeud est vide donc plus besoin de tester dessus */

    /* Le noeud courant n'a qu'un fils low */
    if (!TRHhasLowChild(node) && TRHhasHighChild(node))
      return TRHgetLowChild(node);

    /* Le noeud courant n'a qu'un fils high */
    if (TRHhasLowChild(node) && !TRHhasHighChild(node))
      return TRHgetHighChild(node);

    /* Le noeud courant a 2 fils low et high */

    TRH_Fusion(TRHgetLowChildAddr(node),TRHgetHighChild(node),NULL);

    /* free(th -> sup); */
    return TRHgetLowChild(node);
  }

  return NULL;
}

/* Inserer les mots de th2 dans th1 */
void TRH_Fusion(TRHnode** node1, TRHnode* node2, char* mot)
{
  char *m1 = NULL, *m2 = NULL, *m3 = NULL, *m4 = NULL;
  int n;

  if(!TRHisEmptyNode(node2)){
    if(mot == NULL){
      mot = (char*) malloc(sizeof(char));
      *mot = TRHgetContent(node2);
      m1 = strdup(mot);

      if( TRHgetValue(node2) != -1 ) /* ajout du mot */
	TRHaddWordRecursive(node1, m1, strlen(m1), TRHgetValue(node2));

      TRH_Fusion(node1, TRHgetLowChild(node2), NULL);
      TRH_Fusion(node1, TRHgetEqualChild(node2), m1);
      TRH_Fusion(node1, TRHgetHighChild(node2), NULL);

      /* free(m1); */
    }
    else {
      /* m1 chaine contenant la chaine mot + le caractere du noeud courant */

      m1 = strdup(mot);
      m2 = strdup(mot);
      m3 = strdup(mot);

      n = strlen(mot);

      /* on ajoute le caractere courant a m1 */
      m1 = realloc(mot, (n + 1) * sizeof(char));
      m1[n] = TRHgetContent(node2);

      m4 = strdup(m1);

      if( TRHgetValue(node2) != -1 )
	TRHaddWordRecursive(node1, m1, strlen(m1), TRHgetValue(node2));

      TRH_Fusion(node1, TRHgetLowChild(node2), m2);
      TRH_Fusion(node1, TRHgetEqualChild(node2), m4);
      TRH_Fusion(node1, TRHgetHighChild(node2), m3);

      /* free(m1); */
      /* free(m2); */
      /* free(m3); */
      /* free(m4); */
    }
  }
}


BRDtree* TRHtoBriandaisFromTree(TRHtree *tree)
{
  if(TRHisEmptyTree(tree))
    return NULL;

  return TRHtoBriandaisFromNode(TRHgetTopOfTree(tree));
}


BRDtree* TRHtoBriandaisFromNode(TRHnode *node)
{
  BRDtree* brd = NULL;
  BRDnode* brnode = NULL;

  TRHtoBriandaisFromNodeRecursive(node, &brnode);
  brd = BRDinitTreeWithNode(brnode);

  return brd;
}


/* Donc la je parcours toutes les premieres lettres par ordre alphabetiques */
/* Permet donc d'ajouter une ligne a l'arbre de briandais */
void TRHtoBriandaisFromNodeRecursive(TRHnode *node, BRDnode** brnode)
{
  if(!TRHhasLowChild(node))
    TRHtoBriandaisFromNodeRecursive(TRHgetLowChild(node), brnode);

  /* Ajouter le noeud courant avant d'aller a droite car inferieur */
  if(!TRHhasHighChild(node)){
    BRDsetNextSibling(*brnode,BRDinitNodeWithValue(TRHgetContent(node)));
    TRHtoBriandaisFromNodeRecursive(TRHgetHighChild(node), brnode);
  }
  else{
    /* Ajouter le noeud courant car plus de fils gauche ni droit */
    BRDsetNextSibling(*brnode,BRDinitNodeWithValue(TRHgetContent(node)));
  }

  /* On repart sur le fils eq s'il existe pour construire une nouvelle
     ligne fils du noued courant */
  if(!TRHhasEqualChild(node)){
    BRDsetFirstChild(*brnode,BRDinitEmptyNode());
    TRHtoBriandaisFromNodeRecursive(TRHgetEqualChild(node),BRDgetFirstChildAddr(*brnode));
  }

  if(TRHgetValue(node) != -1)
    BRDsetFirstChild(*brnode,BRDinitNodeWithValue(ASCII_EOW));
}
