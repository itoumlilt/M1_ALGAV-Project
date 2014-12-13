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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <BRD_API.h>

/******************************************************************************
 * Définitions des fonctions privées
 *****************************************************************************/
int BRDcountWordsFromNode(BRDnode* node);
int BRDcountNullNodesFromNode(BRDnode* node);
int BRDcountHeightFromNode(BRDnode* node);
ListWord* BRDinitListWordFromNode(BRDnode* node, ListWord** end, char* word, int size);
void BRDcountAverageDepthFromNode(BRDnode* node, AverageDepth** ad, int h);
BRDnode* BRDmergeTwoNodesRecursive(BRDnode* n1, BRDnode* n2);
/*****************************************************************************/


/******************************************************************************
 * Fonctions de construction :
 *****************************************************************************/
BRDtree* BRDinitTreeFromFile(char* file)
{
  /* ouverture du fichier */
  int fd;
  if( (fd = open(file, O_RDONLY)) == -1){
    fprintf(stderr, "Error: BRD_API: __LINE__\n");
    exit(1);
  }

  /* init */
  BRDtree* tree = BRDinitEmptyTree();
  char lu;
  char word[WORD_MAX_SIZE];
  memset(word, '\0', WORD_MAX_SIZE);
  int i=0;
  int nbWords=0;

  /* read and build */
  while( read(fd, &lu, 1) ){
    if(isSeparator(lu)){
      word[i] = '\0';
      if(i){
	BRDaddWord(tree, word, i); 
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
    BRDaddWord(tree, word, i);
    nbWords++;
  }

  /* fermeture du fichier */
  close(fd);

  return tree;
}

BRDtree* BRDinitTreeFromShakespeareFiles()
{
  /* init */
  BRDtree* tree = BRDinitEmptyTree();
  char lu;
  char word[WORD_MAX_SIZE];
  memset(word, '\0', WORD_MAX_SIZE);
  int i=0;
  int nbWords=0;
  DIR *dir;
  struct dirent *ent;
  int fd;

  char* testDir = "../testDir/shakespeare/";
  char file[128];


  /* parcours */
  if ((dir = opendir(testDir)) != NULL) {
    while((ent = readdir (dir)) != NULL) {
      if(ent->d_name[0] != '.'){
	memset(file, '\0', 128);
	strcat(file, testDir);
	strcat(file, ent->d_name);
	if( (fd = open(file, O_RDONLY)) == -1){
	  fprintf(stderr, "Error: open file %s\n", file);
	  exit(1);
	}
	/* read and construct */
	while( read(fd, &lu, 1) ){
	  if(isSeparator(lu)){
	    word[i] = '\0';
	    if(i){
	      BRDaddWord(tree, word, i); /* @TODO sera fait par un autre thread */
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
	  BRDaddWord(tree, word, i);
	  nbWords++;
	}
	/* fermeture du fichier */
	close(fd);
      }
    }
    closedir (dir);
  }
  return tree;
}

BRDtree* BRDmergeTwoTrees(BRDtree* tree1, BRDtree* tree2)
{
  return BRDinitTreeWithNode(BRDmergeTwoNodesRecursive(BRDgetTopOfTree(tree1),
						       BRDgetTopOfTree(tree2)
						       )
			     );
}

BRDnode* BRDmergeTwoNodesRecursive(BRDnode* n1, BRDnode* n2)
{
  BRDnode* node;

  if( !n1 ) {
    node = BRDinitNodeWithValue(BRDgetContent(n2));
    if( BRDhasNextSibling(n2) )
      BRDsetNextSibling(node,
			BRDmergeTwoNodesRecursive(NULL,
						  BRDgetNextSibling(n2)
						  )
			);
    if( !BRDisEOWNode(n2) ){
      BRDsetFirstChild(node,
		       BRDmergeTwoNodesRecursive(BRDgetFirstChild(n2),
						 NULL)
		       );
    }
    return node;
  }

  if( !n2 ) {
    node = BRDinitNodeWithValue(BRDgetContent(n1));
    if( BRDhasNextSibling(n1) )
      BRDsetNextSibling(node,
			BRDmergeTwoNodesRecursive(NULL,
						  BRDgetNextSibling(n1)
						  )
			);
    if( !BRDisEOWNode(n1) ){
      BRDsetFirstChild(node,
		       BRDmergeTwoNodesRecursive(BRDgetFirstChild(n1),
						 NULL)
		       );
    }
    return node;
  }
  
  if( BRDgetContent(n1) == BRDgetContent(n2) ){
    node = BRDinitNodeWithValue(BRDgetContent(n1));
    if( BRDhasNextSibling(n1) || BRDhasNextSibling(n2) )
      BRDsetNextSibling(node,
			BRDmergeTwoNodesRecursive(BRDgetNextSibling(n1),
						  BRDgetNextSibling(n2))
			);
    if( !BRDisEOWNode(n1) )
      BRDsetFirstChild(node,
		       BRDmergeTwoNodesRecursive(BRDgetFirstChild(n1),
						 BRDgetFirstChild(n2))
		       );
  }
  else if( BRDgetContent(n1) < BRDgetContent(n2)){
    node = BRDinitNodeWithValue(BRDgetContent(n1));
    BRDsetNextSibling(node,
		      BRDmergeTwoNodesRecursive(BRDgetNextSibling(n1),
						n2));
    BRDsetFirstChild(node, BRDmergeTwoNodesRecursive(BRDgetFirstChild(n1), NULL));
  }
  else {
    node = BRDinitNodeWithValue(BRDgetContent(n2));
    BRDsetNextSibling(node,
		      BRDmergeTwoNodesRecursive(n1,BRDgetNextSibling(n2))
		      );
    BRDsetFirstChild(node, BRDmergeTwoNodesRecursive(BRDgetFirstChild(n2), NULL));
  }

  return node;
}

/******************************************************************************
 * Fonctions de recherche
 *****************************************************************************/
int BRDsearchWord(BRDtree* tree, char* word, int size)
{
  BRDnode* node = BRDgetTopOfTree(tree);
  int i;

  for(i=0; i<size; i++){
    node = BRDsearchNodeWithValueInLevel(node, word[i]);
    if( !node )
      return 0;
    node = BRDgetFirstChild(node);
  }
  
  if(BRDisEOWNode(node))
    return 1;

  return 0;
}


ListWord* BRDgetListWordFromTree(BRDtree* tree)
{
  ListWord* listWord;
  ListWord* listEnd;
  char word[WORD_MAX_SIZE];
  
  memset(word, '\0', WORD_MAX_SIZE);

  BRDnode* node = BRDgetTopOfTree(tree);

  listWord = BRDinitListWordFromNode(node, &listEnd, word, 0);

  return listWord;
}

ListWord* BRDinitListWordFromNode(BRDnode* node, ListWord** end, char* word, int size)
{
  ListWord* next = NULL;
  ListWord* listWord = NULL;
  ListWord* childEnd = NULL;

  printf("Node %c\n", BRDgetContent(node));
  
  if( !BRDisEmptyNextSibling(node) )
    next = BRDinitListWordFromNode(BRDgetNextSibling(node), end,  word, size);

  if( BRDisEOWNode(node) ){
    listWord = LWinitWithWord(word, size);
    childEnd = listWord;
    LWsetNextWord(listWord, next);
  } else {
    word[size] = BRDgetContent(node);
    listWord = BRDinitListWordFromNode(BRDgetFirstChild(node), &childEnd, word, size+1);
    word[size] = '\0'; /* faut remettre les choses comme elles étaient ;) */
  }

  if( next ){
    LWsetNextWord(childEnd, next);
  } else {
    end = &childEnd;
  }

  if( !childEnd )
    printf("Ret Node %c childEnd NULL\n", BRDgetContent(node));
  else
    printf("Ret Node %c childEnd notNULL\n", BRDgetContent(node));


  return listWord;
}

/******************************************************************************
 * Fonctions de calcul
 *****************************************************************************/
int BRDcountTreeWords(BRDtree* tree)
{
  return BRDcountWordsFromNode(BRDgetTopOfTree(tree));
}

int BRDcountWordsFromNode(BRDnode* node)
{
  int count = 0;

  if( !BRDisEmptyNextSibling(node) )
    count += BRDcountWordsFromNode(BRDgetNextSibling(node));

  if( BRDisEOWNode(node) )
    return count+1;

  return (count + BRDcountWordsFromNode(BRDgetFirstChild(node)));
}

int BRDcountTreeNullNodes(BRDtree* tree)
{
  return BRDcountNullNodesFromNode(BRDgetTopOfTree(tree));
}

int BRDcountNullNodesFromNode(BRDnode* node)
{
  int count = 0;

  if( BRDisEmptyNextSibling(node) )
    count++;
  else
    count += BRDcountNullNodesFromNode(BRDgetNextSibling(node));

  if( BRDisEmptyFirstChild(node) )
    return count+1;
  else
    return count + BRDcountNullNodesFromNode(BRDgetFirstChild(node));
}

int BRDcountTreeHeight(BRDtree* tree)
{
  return BRDcountHeightFromNode(BRDgetTopOfTree(tree));
}

int BRDcountHeightFromNode(BRDnode* node)
{
  int myHigh = 1;
  int brothersHigh = 0;

  if( !BRDisEmptyNextSibling(node) )
    brothersHigh = BRDcountHeightFromNode(BRDgetNextSibling(node));

  if( !BRDisEOWNode(node) )
    myHigh += BRDcountHeightFromNode(BRDgetFirstChild(node));

  return (myHigh > brothersHigh) ? myHigh : brothersHigh;
}

int BRDcountAverageDepth(BRDtree* tree)
{
  AverageDepth* ad = ADinit();

  BRDcountAverageDepthFromNode(BRDgetTopOfTree(tree), &ad, 0);

  int averageDepth = ADcount(ad);
  
  ADfree(ad);

  return averageDepth;
}

void BRDcountAverageDepthFromNode(BRDnode* node, AverageDepth** ad, int h)
{
  if( BRDhasNextSibling(node) )
    BRDcountAverageDepthFromNode(BRDgetNextSibling(node), ad, h);

  ADincrementNbNodes(*ad);
  
  if( BRDisEOWNode(node) )
    ADaddHeight(*ad, h);
  else
    BRDcountAverageDepthFromNode(BRDgetFirstChild(node), ad, h+1);
}

int BRDcountTreePrefixeOccurrence(BRDtree* tree, char* word, int size)
{
  BRDnode* node = BRDgetTopOfTree(tree);
  int i;

  for(i=0; i<size; i++){
    node = BRDsearchNodeWithValueInLevel(node, word[i]);
    if( !node )
      return 0;
    node = BRDgetFirstChild(node);
  }
  
  return BRDcountWordsFromNode(node);
}

/******************************************************************************
 * Fonctions de traitement
 *****************************************************************************/
/* @TODO une doublement chainée aurait tellement optimisé la suppression */
int BRDremoveWordFromTree(BRDtree* tree, char* word, int size)
{
  /* @TODO fonction largement optimisable en dissociant d'abord l'abr puis freeRecursif d'un coup, ou avec un super BRDfreeChildWithValue qui fait tout */
  /* je construis d'abord un tableau de pointeurs sur les noeuds du mot */
  BRDnode** nodesToRemove = NULL;
  
  BRDnode* node = BRDgetTopOfTree(tree);
  int i;
  
  for(i=0; i<size; i++){
    node = BRDsearchNodeWithValueInLevel(node, word[i]);
    
    if( !node )
      break;

    nodesToRemove = (BRDnode**)realloc(nodesToRemove, (i+1)*sizeof(BRDnode*));
    nodesToRemove[i] = node;
  }
  
  /* suppression des noeuds en remontée */
  int j;
  for( j=i-1; j>=0; j-- ){
    if( j ){
      if( !BRDisEmptyNextSibling(nodesToRemove[j]) ) {
	if( BRDisFirstChildOf(nodesToRemove[j-1], nodesToRemove[j]) ) {
	  BRDsetFirstChild(nodesToRemove[j-1],
			   BRDgetNextSibling(nodesToRemove[j]));
	  BRDfreeNode(nodesToRemove[j]);
	}
	else
	  BRDremoveChildFromNode(nodesToRemove[j-1],
				 nodesToRemove[j]);
      } else {
	BRDfreeNode(nodesToRemove[j]);
	BRDsetFirstChild(nodesToRemove[j-1], NULL);
      }
    } else {
      if( BRDisTopOfTree(tree, nodesToRemove[j]) ){
	if( BRDhasNextSibling(nodesToRemove[j]) ){
	  BRDsetTopOfTree(tree, BRDgetNextSibling(nodesToRemove[j]));
	} else {
	  BRDsetTopOfTree(tree, BRDinitEmptyNode());
	}
	BRDfreeNode(nodesToRemove[j]);
      } else {
	BRDnode* prev = BRDgetTopOfTree(tree);
	while( BRDgetNextSibling(prev) != nodesToRemove[j] ){
	  prev = BRDgetNextSibling(prev);
	}
	BRDsetNextSibling(prev, BRDgetNextSibling(nodesToRemove[j]));
	BRDfreeNode(nodesToRemove[j]);
      }
    }
  }
  
  /* je free la mem allouée pour le tab de pointeurs */
  free(nodesToRemove);
  
  return 0;
}
