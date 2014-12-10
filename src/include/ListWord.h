/**
 * ALGAV Project
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

typedef struct _ListWord {
  char* word;
  struct _BRDlistWord* nextWord;
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
 * Free memory
 *****************************************************************************/
int LWfree(ListWord* listWord);
int LWfreeRecursive(ListWord* listWord);
