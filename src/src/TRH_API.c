/**
 * ALGAV Project
 * TRH_API private implementation
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
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <TRH_API.h>

/******************************************************************************
 * Déclaration des fonctions privées
 *****************************************************************************/
int TRHsearchwordFromNodeRecursive(TRHnode* node, char* word, int size);
int TRHcountWordsFromNodeRecursive(TRHnode* node);
int TRHcountNilFromNodeRecursive(TRHnode* node);
int TRHcountHeightFromNodeRecursive(TRHnode* node);
int TRHcountPrefixFromNodeRecursive(TRHnode* node, char* word, int size);
ListWord* TRHinitListWordFromNode(TRHnode* node, ListWord** end, char* word, int size);
/*****************************************************************************/

/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/
TRHtree* TRHinitTreeFromFile(char* filename)
{
  /* ouverture du fichier */
  int fd;
  if( (fd=open(filename, O_RDONLY)) == -1 ){
    fprintf(stderr, "Error: BRD_API: open()\n");
    exit(1);
  }

  /* init */
  TRHtree* tree = TRHinitEmptyTree();
  char word[WORD_MAX_SIZE];
  memset(word, '\0', WORD_MAX_SIZE);
  char lu;
  int i = 0;
  int nbWords=0;

  /* read and build */
  while( read(fd, &lu, 1) ){
    if(isSeparator(lu)){
      word[i] = '\0';
      if(i){
	TRHaddWord(tree, word, i);
	nbWords++;
      }
      i=0;
    } else {
      word[i] = lu;
      i++;
    }
  }

  /* on rajoute le dernier mot s'il y'a pas eu de séparateur après */
  if(i){
    word[i] = '\0';
    TRHaddWord(tree, word, i);
    nbWords++;
  }

  /* fermeture du fichier */
  close(fd);
  
  return tree;
}

/******************************************************************************
 * Fonctions de search :
 *****************************************************************************/
int TRHsearchWord(TRHtree* tree, char* word, int size)
{
  return TRHsearchwordFromNodeRecursive(TRHgetTopOfTree(tree),word,size);
}

int TRHsearchwordFromNodeRecursive(TRHnode* node, char* word, int size)
{
  if( TRHgetContent(node) == word[0] ){
    if( size == 1 ){
      if( TRHisEOWNode(node) )
	return 1;
      else
	return 0;
    }
    if( TRHhasEqualChild(node) )
      return TRHsearchwordFromNodeRecursive(TRHgetEqualChild(node),word+1,size-1);
  }

  if( TRHgetContent(node) > word[0] && TRHhasLowChild(node) )
    return TRHsearchwordFromNodeRecursive(TRHgetLowChild(node),word,size);

  if( TRHgetContent(node) < word[0] && TRHhasHighChild(node) )
    return TRHsearchwordFromNodeRecursive(TRHgetHighChild(node),word,size);

  return 0;
}

int TRHcountWords(TRHtree* tree)
{
  return TRHcountWordsFromNodeRecursive(TRHgetTopOfTree(tree));
}

int TRHcountWordsFromNodeRecursive(TRHnode* node)
{
  int count = 0;

  if( TRHisEOWNode(node) )
    count++;

  if( TRHhasLowChild(node) )
    count += TRHcountWordsFromNodeRecursive(TRHgetLowChild(node));

  if( TRHhasEqualChild(node) )
    count += TRHcountWordsFromNodeRecursive(TRHgetEqualChild(node));

  if( TRHhasHighChild(node) )
    count += TRHcountWordsFromNodeRecursive(TRHgetHighChild(node));

  return count;
}

int TRHcountNil(TRHtree* tree)
{
  if( TRHisEmptyTree(tree) )
    return 1;
  else
    return TRHcountNilFromNodeRecursive(TRHgetTopOfTree(tree));
}

int TRHcountNilFromNodeRecursive(TRHnode* node)
{
  int count = 0;

  if( TRHhasLowChild(node) )
    count+= TRHcountNilFromNodeRecursive(TRHgetLowChild(node));
  else
    count++;

  if( TRHhasEqualChild(node) )
    count += TRHcountNilFromNodeRecursive(TRHgetEqualChild(node));
  else
    count++;

  if( TRHhasHighChild(node) )
    count += TRHcountNilFromNodeRecursive(TRHgetHighChild(node));
  else
    count++;

  return count;
}

int TRHcountHeight(TRHtree* tree)
{
  if( TRHisEmptyTree(tree) )
    return 0;
  else
    return TRHcountHeightFromNodeRecursive(TRHgetTopOfTree(tree));
}

int TRHcountHeightFromNodeRecursive(TRHnode* node)
{
  int height = 0;
  int tmp;
  
  if( TRHhasLowChild(node) ){
    tmp = TRHcountHeightFromNodeRecursive(TRHgetLowChild(node));
    height = ( tmp > height ) ? tmp : height;
  }

  if( TRHhasEqualChild(node) ){
    tmp = TRHcountHeightFromNodeRecursive(TRHgetEqualChild(node));
    height = ( tmp > height ) ? tmp : height;
  }

  if( TRHhasHighChild(node) ){
    tmp = TRHcountHeightFromNodeRecursive(TRHgetHighChild(node));
    height = ( tmp > height ) ? tmp : height;
  }

  return height;
}

int TRHcountPrefix(TRHtree* tree, char* word, int size)
{
  if( TRHisEmptyTree(tree) )
    return 0;
  else
    return TRHcountPrefixFromNodeRecursive(TRHgetTopOfTree(tree),word,size);
}

int TRHcountPrefixFromNodeRecursive(TRHnode* node, char* word, int size)
{
  if( TRHgetContent(node) == word[0] ){
    if( size == 1 ){
      return TRHcountWordsFromNodeRecursive(node);
    }
    if( TRHhasEqualChild(node) )
      return TRHcountPrefixFromNodeRecursive(TRHgetEqualChild(node),word+1,size-1);
  }

  if( TRHgetContent(node) > word[0] && TRHhasLowChild(node) )
    return TRHcountPrefixFromNodeRecursive(TRHgetLowChild(node),word,size);

  if( TRHgetContent(node) < word[0] && TRHhasHighChild(node) )
    return TRHcountPrefixFromNodeRecursive(TRHgetHighChild(node),word,size);

  return 0;
}

/******************************************************************************
 * Fonctions de génération :
 *****************************************************************************/
ListWord* TRHinitListWordFromTree(TRHtree* tree)
{
  if( TRHisEmptyTree(tree) )
    return NULL;

  char word[WORD_MAX_SIZE];
  memset(word, '\0', WORD_MAX_SIZE);
  return TRHinitListWordFromNode(TRHgetTopOfTree(tree), NULL, word, 0);
}

ListWord* TRHinitListWordFromNode(TRHnode* node, ListWord** end, char* word, int size)
{
  ListWord* deb = NULL;
  ListWord* fin = NULL;
  ListWord* insNode;

  if( TRHhasLowChild(node) ){
    deb = TRHinitListWordFromNode(TRHgetLowChild(node), &fin, word, size);
  }

  word[size] = TRHgetContent(node);
  size++;

  if( TRHisEOWNode(node) ){
    insNode = LWinitWithWord(word, size);
    if( !fin )
      fin = insNode;
    else {
      LWsetNextWord(fin, insNode);
      fin = insNode;
    }
    if( !deb )
      deb = insNode;
  }

  if( TRHhasEqualChild(node) ){
    insNode = TRHinitListWordFromNode(TRHgetEqualChild(node),end,word,size);
    if(fin)
      LWsetNextWord(fin, insNode);
    fin = *end;
    if( !deb )
      deb = insNode;
  }
  
  word[size] = '\0';
  size--;

  if( TRHhasHighChild(node) ){
    insNode = TRHinitListWordFromNode(TRHgetHighChild(node),end,word,size);
    if(fin)
      LWsetNextWord(fin, insNode);
    fin = *end;
    if( !deb )
      deb = insNode;
  }

  end = &fin;
  return insNode;
}

/******************************************************************************
 * Fonctions de libération de mémoire :
 *****************************************************************************/
void TRHfree(TRHtree* tree)
{
  TRHfreeTree(tree);
}
