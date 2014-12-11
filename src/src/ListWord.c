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
#include <string.h>

#include <ListWord.h>

/******************************************************************************
 * Init functions
 *****************************************************************************/
ListWord* LWinitWithWord(char* word, int size)
{
  ListWord* listWord = (ListWord*)malloc(sizeof(ListWord));

  LWsetWord(listWord, word, size);
  LWsetNextWord(listWord, NULL);

  return listWord;
}


/******************************************************************************
 * Getter / Setter
 *****************************************************************************/
char* LWgetWord(ListWord* listWord)
{
  return listWord->word;
}

void LWsetWord(ListWord* listWord, char* word, int size)
{
  char *myWord = (char*)malloc(size*sizeof(char));
  strncpy(myWord, word, size);

  listWord->word = myWord;
}

ListWord* LWgetNextWord(ListWord* listWord)
{
  return listWord->nextWord;
}

void LWsetNextWord(ListWord* listWord,
		   ListWord* nextWord)
{
  listWord->nextWord = nextWord;
}

/******************************************************************************
 * fonctions de check
 *****************************************************************************/
int LWisEmptyNextWord(ListWord* listWord)
{
  if( LWgetNextWord(listWord) )
    return 1;
  return 0;
}

/******************************************************************************
 * fonctions d'affichage
 *****************************************************************************/
void LWprintAllWords(ListWord* listWord)
{
  ListWord* lw = listWord;

  while( lw ){
    printf("%s\n", LWgetWord(lw));
    lw = LWgetNextWord(lw);
  }
  
}

/******************************************************************************
 * Free memory
 *****************************************************************************/
int LWfree(ListWord* listWord)
{
  free(LWgetWord(listWord));
  free(listWord);

  return 0;
}

int LWfreeRecursive(ListWord* listWord)
{
  if( !LWisEmptyNextWord(listWord) )
    LWfreeRecursive(listWord);
  LWfree(listWord);

  return 0;
}
