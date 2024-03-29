/**
 * ALGAV Project
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#ifndef __LISTWORD_H__
#define __LISTWORD_H__

typedef struct _ListWord {
  char* word;
  struct _ListWord* nextWord;
} ListWord;

/******************************************************************************
 * Init functions
 *****************************************************************************/
ListWord* LWinitWithWord(char* word, int size);

/******************************************************************************
 * Getter / Setter
 *****************************************************************************/
char* LWgetWord(ListWord* listWord);
void LWsetWord(ListWord* listWord, char* word, int size);

ListWord* LWgetNextWord(ListWord* listWord);
void LWsetNextWord(ListWord* listWord,
		   ListWord* nextWord);

/******************************************************************************
 * fonctions de check
 *****************************************************************************/
int LWisEmptyNextWord(ListWord* listWord);

/******************************************************************************
 * fonctions d'affichage
 *****************************************************************************/
void LWprintAllWords(ListWord* listWord);

/******************************************************************************
 * Free memory
 *****************************************************************************/
int LWfree(ListWord* listWord);
int LWfreeRecursive(ListWord* listWord);

#endif
