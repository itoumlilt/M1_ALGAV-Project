/**
 * ALGAV Project
 * Errno
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

#include <BRDerrno.h>

/******************************************************************************
 * Getter / Setter
 *****************************************************************************/
void BRDsetErrorMsg(int errno)
{
  switch(errno){
  case BRDERRNO_NUL_POINTER :
    strcpy(BRDerrorMsg, "Nul pointer error");
    break;
  default :
    strcpy(BRDerrorMsg, "Unknown error");
  }
}

char* BRDgetErrorMsg(){
  return BRDerrorMsg;
}

char* BRDsetAndGetErrorMsg(int errno)
{
  BRDsetErrorMsg(errno);
  return BRDgetErrorMsg();
}
