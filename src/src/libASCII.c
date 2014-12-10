/**
 * ALGAV Project - ASCII Library
 *
 * @author Ilyas Toumlilt <toumlilt.ilyas@gmail.com>
 * @copyright (c) 2014, toumlilt
 *
 * @version 1.0
 * @package waye/M1/ALGAV
 */


/******************************************************************************
 * Fonctions de vérification
 *****************************************************************************/

/**
 * check si c est un séparateur
 * est séparateur tout caractère non alphabétique
 * @param c le caractère à traiter
 * @return int 1 si séparateur, 0 sinon
 */
int isSeparator(char c)
{
  if( c > 64 && c < 91 )
    return 0;
  if( c > 96 && c < 123 )
    return 0;
  return 1;
}
