/**
 * ALGAV Project - ASCII Library
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */

#ifndef __LIBASCII_H__
#define __LIBASCII_H__

/* Parmi les 128 du code ASCII, on a choisi \0 (0) */
#define ASCII_EOW 0 /* \0 */

/* @TODO ON GARDE LES CARACTÈRES D'ÉCHAPPEMENT DANS L'ASCII ?? */
#define ASCII_MIN 0
#define ASCII_MAX 127

/* taille max d'un mot du dictionnaire */
#define WORD_MAX_SIZE 128

/******************************************************************************
 * Fonctions de vérification
 *****************************************************************************/
int isSeparator(int c);

#endif
